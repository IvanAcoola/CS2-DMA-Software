#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <chrono>
#include <map>
#include "Entity.h"
#include "../utils/Format.hpp"

namespace Render
{
	void DrawFovCircle(const CEntity& LocalEntity, int type)
	{ // 0 - default, 1 - rifles, 2 - snipers, 3 - pistols, 4 - shotguns
		float tempsmooth = AimControl::AimFov;
		if (type == 1) tempsmooth = AimControl::AimFovRifles;
		else if (type == 2) tempsmooth = AimControl::AimFovSnipers;
		else if (type == 3) tempsmooth = AimControl::AimFovPistols;
		else if (type == 4) tempsmooth = AimControl::AimFovShotguns;

		Vec2 CenterPoint = Gui.Window.Size / 2;
		float Radius = tan(tempsmooth / 180.f * M_PI / 2.f) / tan(LocalEntity.Pawn.Fov / 180.f * M_PI / 2.f) * Gui.Window.Size.x;
		Gui.Circle(CenterPoint, Radius, MenuConfig::AimFovRangeColor, 1);
	}


	void LineToEnemy(ImVec4 Rect, ImColor Color, float Thickness)
	{
		Gui.Line({ Rect.x + Rect.z / 2,Rect.y }, { Gui.Window.Size.x / 2,0 }, Color, Thickness);
	}

	void DrawFov(const CEntity& LocalEntity, float Size, ImColor Color, float Thickness)
	{
		float Length;
		float radian;
		Vec2 LineEndPoint[2];
		Vec2 Pos = Gui.Window.Size / 2;

		radian = (LocalEntity.Pawn.Fov / 2) * M_PI / 180;

		LineEndPoint[0].y = Pos.y - Size;
		LineEndPoint[1].y = LineEndPoint[0].y;

		Length = Size * tan(radian);

		LineEndPoint[0].x = Pos.x - Length;
		LineEndPoint[1].x = Pos.x + Length;

		Gui.Line(Pos, LineEndPoint[0], Color, 1.5);
		Gui.Line(Pos, LineEndPoint[1], Color, 1.5);
	}

	void DrawDistance(const CEntity& LocalEntity, CEntity& Entity, ImVec4 Rect)
	{
		int distance = static_cast<int>(Entity.Pawn.Pos.DistanceTo(LocalEntity.Pawn.Pos) / 100);
		std::string dis_str = Format("%im", distance);
		Gui.StrokeText(dis_str, { Rect.x + Rect.z + 4, Rect.y }, ImColor(255, 255, 255, 255), 14, false);
	}


	ImVec4 Get2DBox(const CEntity& Entity)
	{
		BoneJointPos Head = Entity.GetBone().BonePosList[BONEINDEX::head];
		Vec2 Size, Pos;
		Size.y = (Entity.Pawn.ScreenPos.y - Head.ScreenPos.y) * 1.09;
		Size.x = Size.y * 0.6;

		Pos = ImVec2(Entity.Pawn.ScreenPos.x - Size.x / 2, Head.ScreenPos.y- Size.y*0.08);

		return ImVec4{ Pos.x,Pos.y,Size.x,Size.y };
	}

	void DrawBone(const CEntity& Entity, ImColor Color, float Thickness)
	{
		BoneJointPos Previous, Current;
		for (auto i : BoneJointList::List)
		{
			Previous.Pos = Vec3(0, 0, 0);
			for (auto Index : i)
			{
				Current = Entity.GetBone().BonePosList[Index];
				if (Previous.Pos == Vec3(0, 0, 0))
				{
					Previous = Current;
					continue;
				}
				if (Previous.IsVisible && Current.IsVisible)
				{
					Gui.Line(Previous.ScreenPos, Current.ScreenPos, Color, Thickness);
				}
				Previous = Current;
			}
		}
	}

	void ShowLosLine(const CEntity& Entity, const float Length, ImColor Color, float Thickness)
	{
		Vec2 StartPoint, EndPoint;
		Vec3 Temp;
		BoneJointPos Head = Entity.GetBone().BonePosList[BONEINDEX::head];

		StartPoint = Head.ScreenPos;

		float LineLength = cos(Entity.Pawn.ViewAngle.x * M_PI / 180) * Length;

		Temp.x = Head.Pos.x + cos(Entity.Pawn.ViewAngle.y * M_PI / 180) * LineLength;
		Temp.y = Head.Pos.y + sin(Entity.Pawn.ViewAngle.y * M_PI / 180) * LineLength;
		Temp.z = Head.Pos.z - sin(Entity.Pawn.ViewAngle.x * M_PI / 180) * Length;

		if (!gGame.View.WorldToScreen(Temp, EndPoint))
			return;

		Gui.Line(StartPoint, EndPoint, Color, Thickness);
	}

	ImVec4 Get2DBoneRect(const CEntity& Entity)
	{
		Vec2 Min, Max, Size;
		Min = Max = Entity.GetBone().BonePosList[0].ScreenPos;

		for (auto &BoneJoint : Entity.GetBone().BonePosList)
		{
			if (!BoneJoint.IsVisible)
				continue;
			Min.x = std::min(BoneJoint.ScreenPos.x, Min.x);
			Min.y = std::min(BoneJoint.ScreenPos.y, Min.y);
			Max.x = std::max(BoneJoint.ScreenPos.x, Max.x);
			Max.y = std::max(BoneJoint.ScreenPos.y, Max.y);
		}
		Size.x = Max.x - Min.x;
		Size.y = Max.y - Min.y;

		return ImVec4(Min.x, Min.y, Size.x, Size.y);
	}

	class HealthBar
	{
	private:
		using TimePoint_ = std::chrono::steady_clock::time_point;
	private:
		const int ShowBackUpHealthDuration = 500;

		float MaxHealth = 0.f;

		float CurrentHealth = 0.f;

		float LastestBackupHealth = 0.f;

		ImVec2 RectPos{};

		ImVec2 RectSize{};

		bool InShowBackupHealth = false;

		TimePoint_ BackupHealthTimePoint{};
	public:
		HealthBar() {}

		void DrawHealthBar_Horizontal(float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size);

		void DrawHealthBar_Vertical(float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size);
	private:
		ImColor Mix(ImColor Col_1, ImColor Col_2, float t);

		ImColor FirstStageColor = ImColor(96, 246, 113, 220);

		ImColor SecondStageColor = ImColor(247, 214, 103, 220);

		ImColor ThirdStageColor = ImColor(255, 95, 95, 220);

		ImColor BackupHealthColor = ImColor(255, 255, 255, 220);

		ImColor FrameColor = ImColor(45, 45, 45, 220);

		ImColor BackGroundColor = ImColor(90, 90, 90, 220);
	};

	void HealthBar::DrawHealthBar_Horizontal(float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size)
	{
		auto InRange = [&](float value, float min, float max) -> bool
		{
			return value > min && value <= max;
		};

		ImDrawList* DrawList = ImGui::GetBackgroundDrawList();

		this->MaxHealth = MaxHealth;
		this->CurrentHealth = CurrentHealth;
		this->RectPos = Pos;
		this->RectSize = Size;


		float Proportion = CurrentHealth / MaxHealth;

		float Width = RectSize.x * Proportion;

		ImColor Color;


		DrawList->AddRectFilled(RectPos,
			{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
			BackGroundColor, 5, 15);


		float Color_Lerp_t = pow(Proportion, 2.5);
		if (InRange(Proportion, 0.5, 1))
			Color = Mix(FirstStageColor, SecondStageColor, Color_Lerp_t * 3 - 1);
		else
			Color = Mix(SecondStageColor, ThirdStageColor, Color_Lerp_t * 4);


		if (LastestBackupHealth == 0
			|| LastestBackupHealth < CurrentHealth)
			LastestBackupHealth = CurrentHealth;

		if (LastestBackupHealth != CurrentHealth)
		{
			if (!InShowBackupHealth)
			{
				BackupHealthTimePoint = std::chrono::steady_clock::now();
				InShowBackupHealth = true;
			}

			std::chrono::steady_clock::time_point CurrentTime = std::chrono::steady_clock::now();
			if (CurrentTime - BackupHealthTimePoint > std::chrono::milliseconds(ShowBackUpHealthDuration))
			{

				LastestBackupHealth = CurrentHealth;
				InShowBackupHealth = false;
			}

			if (InShowBackupHealth)
			{
				float BackupHealthWidth = LastestBackupHealth / MaxHealth * RectSize.x;

				float BackupHealthColorAlpha = 1 - 0.95 * (std::chrono::duration_cast<std::chrono::milliseconds>(CurrentTime - BackupHealthTimePoint).count() / (float)ShowBackUpHealthDuration);
				ImColor BackupHealthColorTemp = BackupHealthColor;
				BackupHealthColorTemp.Value.w = BackupHealthColorAlpha;

				float BackupHealthWidth_Lerp = 1 * (std::chrono::duration_cast<std::chrono::milliseconds>(CurrentTime - BackupHealthTimePoint).count() / (float)ShowBackUpHealthDuration);
				BackupHealthWidth_Lerp *= (BackupHealthWidth - Width);
				BackupHealthWidth -= BackupHealthWidth_Lerp;

				DrawList->AddRectFilled(RectPos,
					{ RectPos.x + BackupHealthWidth,RectPos.y + RectSize.y },
					BackupHealthColorTemp, 5);
			}
		}


		DrawList->AddRectFilled(RectPos,
			{ RectPos.x + Width,RectPos.y + RectSize.y },
			Color, 5);


		DrawList->AddRect(RectPos,
			{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
			FrameColor, 5, 15, 1);
	}

	void HealthBar::DrawHealthBar_Vertical(float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size)
	{
		auto InRange = [&](float value, float min, float max) -> bool
		{
			return value > min && value <= max;
		};

		ImDrawList* DrawList = ImGui::GetBackgroundDrawList();

		this->MaxHealth = MaxHealth;
		this->CurrentHealth = CurrentHealth;
		this->RectPos = Pos;
		this->RectSize = Size;


		float Proportion = CurrentHealth / MaxHealth;

		float Height = RectSize.y * Proportion;

		ImColor Color;

		DrawList->AddRectFilled(RectPos,
			{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
			BackGroundColor, 5, 15);

		float Color_Lerp_t = pow(Proportion, 2.5);
		if (InRange(Proportion, 0.5, 1))
			Color = Mix(FirstStageColor, SecondStageColor, Color_Lerp_t * 3 - 1);
		else
			Color = Mix(SecondStageColor, ThirdStageColor, Color_Lerp_t * 4);

		if (LastestBackupHealth == 0
			|| LastestBackupHealth < CurrentHealth)
			LastestBackupHealth = CurrentHealth;

		if (LastestBackupHealth != CurrentHealth)
		{
			if (!InShowBackupHealth)
			{
				BackupHealthTimePoint = std::chrono::steady_clock::now();
				InShowBackupHealth = true;
			}

			std::chrono::steady_clock::time_point CurrentTime = std::chrono::steady_clock::now();
			if (CurrentTime - BackupHealthTimePoint > std::chrono::milliseconds(ShowBackUpHealthDuration))
			{
				LastestBackupHealth = CurrentHealth;
				InShowBackupHealth = false;
			}

			if (InShowBackupHealth)
			{
				float BackupHealthHeight = LastestBackupHealth / MaxHealth * RectSize.y;
				float BackupHealthColorAlpha = 1 - 0.95 * (std::chrono::duration_cast<std::chrono::milliseconds>(CurrentTime - BackupHealthTimePoint).count() / (float)ShowBackUpHealthDuration);
				ImColor BackupHealthColorTemp = BackupHealthColor;
				BackupHealthColorTemp.Value.w = BackupHealthColorAlpha;
				float BackupHealthHeight_Lerp = 1 * (std::chrono::duration_cast<std::chrono::milliseconds>(CurrentTime - BackupHealthTimePoint).count() / (float)ShowBackUpHealthDuration);
				BackupHealthHeight_Lerp *= (BackupHealthHeight - Height);
				BackupHealthHeight -= BackupHealthHeight_Lerp;
				DrawList->AddRectFilled({ RectPos.x,RectPos.y + RectSize.y - BackupHealthHeight },
					{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
					BackupHealthColorTemp, 5);
			}
		}

		DrawList->AddRectFilled({ RectPos.x,RectPos.y + RectSize.y - Height },
			{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
			Color, 5);

		DrawList->AddRect(RectPos,
			{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
			FrameColor, 5, 15, 1);
	}

	ImColor HealthBar::Mix(ImColor Col_1, ImColor Col_2, float t)
	{
		ImColor Col;
		Col.Value.x = t * Col_1.Value.x + (1 - t) * Col_2.Value.x;
		Col.Value.y = t * Col_1.Value.y + (1 - t) * Col_2.Value.y;
		Col.Value.z = t * Col_1.Value.z + (1 - t) * Col_2.Value.z;
		Col.Value.w = Col_1.Value.w;
		return Col;
	}

	void DrawHealthBar(DWORD Sign, float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size, bool Horizontal)
	{
		static std::map<DWORD, HealthBar> HealthBarMap;
		if (!HealthBarMap.count(Sign))
		{
			HealthBarMap.insert({ Sign,HealthBar() });
		}
		if (HealthBarMap.count(Sign))
		{
			if (Horizontal)
				HealthBarMap[Sign].DrawHealthBar_Horizontal(MaxHealth, CurrentHealth, Pos, Size);
			else
				HealthBarMap[Sign].DrawHealthBar_Vertical(MaxHealth, CurrentHealth, Pos, Size);
		}
	}

}
