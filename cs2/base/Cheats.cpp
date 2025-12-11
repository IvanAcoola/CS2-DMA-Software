#include "../KeysValues.h"

#include "GUI.h"
#include "../Globals.h"

#include "Cheats.h"
#include "Render.hpp"
#include "MenuConfig.hpp"
#include "../utils/ConfigMenu.hpp"
#include "../utils/ConfigSaver.hpp"


void Cheats::RadarSetting(Base_Radar& Radar)
{
	ImGui::SetNextWindowBgAlpha(0.1f);
	ImGui::Begin("Radar", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);
	ImGui::SetWindowSize({ mp::RadarSize, mp::RadarSize });

	Radar.SetDrawList(ImGui::GetWindowDrawList());

	Radar.SetPos({ ImGui::GetWindowPos().x, ImGui::GetWindowPos().y });
	Radar.Opened = true;
}

void Cheats::Run()
{
	try {
		static std::chrono::time_point LastTimePoint = std::chrono::steady_clock::now();
		auto CurTimePoint = std::chrono::steady_clock::now();

		if (Keys::MenuKey
			&& CurTimePoint - LastTimePoint >= std::chrono::milliseconds(150))
		{
			MenuConfig::ShowMenu = !MenuConfig::ShowMenu;
			LastTimePoint = CurTimePoint;
		}

		if (MenuConfig::ShowMenu)
			Menu();

		static std::map<DWORD64, Render::HealthBar> HealthBarMap;

		float DistanceToSight = 0;
		float MaxAimDistance = 100000;
		Vec3  HeadPos{ 0,0,0 };
		Vec3  AimPos{ 0,0,0 };

		int weaponTypeSmooth = 0; // 0 - default, 1 - rifles, 2 - snipers, 3 - pistols, 4 - shotguns

		Base_Radar Radar;

		if (MenuConfig::ShowRadar)
			RadarSetting(Radar);

		if (MenuConfig::ShowRadar)
			Radar.UpdateMap(mapname);

		for (int i = 0; i < EntityList.size(); i++)
		{
			CEntity Entity = EntityList[i];

			if (Entity.Pawn.Health <= 0) {
				continue;
			}

			if (MenuConfig::ShowRadar)
				Radar.AddPoint(LocalEntityPlayer.Pawn.Pos, Entity.Pawn.ViewAngle.y, Entity.Pawn.Pos, ImColor(237, 85, 106, 200), Entity.Pawn.ViewAngle.y, (int)(Entity.Controller.TeamID == LocalEntityPlayer.Controller.TeamID), Entity.Pawn.Health);

			if (MenuConfig::TeamCheck && Entity.Controller.TeamID == LocalEntityPlayer.Controller.TeamID)
				continue;

			if (!Entity.IsInScreen()) {
				continue;
			}
			if (Entity.GetBone().BonePosList.size() <= BONEINDEX::head) continue;
			DistanceToSight = Entity.GetBone().BonePosList[BONEINDEX::head].ScreenPos.DistanceTo({ Gui.Window.Size.x / 2,Gui.Window.Size.y / 2 });

			if (DistanceToSight < MaxAimDistance)
			{
				MaxAimDistance = DistanceToSight;
				// 0 - default, 1 - rifles, 2 - snipers, 3 - pistols, 4 - shotguns
				if (!MenuConfig::VisibleCheck ||
					Entity.Pawn.bSpottedByMask & (DWORD64(1) << (LocalEntityPlayer.LocalPlayerControllerIndex)) ||
					LocalEntityPlayer.Pawn.bSpottedByMask & (DWORD64(1) << (i)))
				{	// pistols
					if (std::find(GunList::pistolsList.begin(), GunList::pistolsList.end(), LocalEntityPlayer.Pawn.WeaponName) != GunList::pistolsList.end()) {
						if (Entity.GetBone().BonePosList.size() <= MenuConfig::AimPositionIndexPistol) continue;
						AimPos = Entity.GetBone().BonePosList[MenuConfig::AimPositionIndexPistol].Pos;
						if (MenuConfig::AimPositionIndexPistol == BONEINDEX::head)
							AimPos.z -= 1.f;
						weaponTypeSmooth = 3;
					} // snipers
					else if (std::find(GunList::snipersList.begin(), GunList::snipersList.end(), LocalEntityPlayer.Pawn.WeaponName) != GunList::snipersList.end()) {
						if (Entity.GetBone().BonePosList.size() <= MenuConfig::AimPositionIndexSniper) continue;
						AimPos = Entity.GetBone().BonePosList[MenuConfig::AimPositionIndexSniper].Pos;
						if (MenuConfig::AimPositionIndexSniper == BONEINDEX::head)
							AimPos.z -= 1.f;
						weaponTypeSmooth = 2;
					} // rifles
					else if (std::find(GunList::riflesList.begin(), GunList::riflesList.end(), LocalEntityPlayer.Pawn.WeaponName) != GunList::riflesList.end()) {
						if (Entity.GetBone().BonePosList.size() <= MenuConfig::AimPositionIndexRifles) continue;
						AimPos = Entity.GetBone().BonePosList[MenuConfig::AimPositionIndexRifles].Pos;
						if (MenuConfig::AimPositionIndexRifles == BONEINDEX::head)
							AimPos.z -= 1.f;
						weaponTypeSmooth = 1;
					} // shotguns
					else if (std::find(GunList::shotgunsList.begin(), GunList::shotgunsList.end(), LocalEntityPlayer.Pawn.WeaponName) != GunList::shotgunsList.end()) {
						if (Entity.GetBone().BonePosList.size() <= MenuConfig::AimPositionIndexShotGuns) continue;
						AimPos = Entity.GetBone().BonePosList[MenuConfig::AimPositionIndexShotGuns].Pos;
						if (MenuConfig::AimPositionIndexShotGuns == BONEINDEX::head)
							AimPos.z -= 1.f;
						weaponTypeSmooth = 4;
					} 
					else { // default
						if (Entity.GetBone().BonePosList.size() <= MenuConfig::AimPositionIndex) continue;
						AimPos = Entity.GetBone().BonePosList[MenuConfig::AimPositionIndex].Pos;
						if (MenuConfig::AimPositionIndex == BONEINDEX::head)
							AimPos.z -= 1.f;
					}
				}
			}

			if (MenuConfig::ShowBoneESP)
				Render::DrawBone(Entity, MenuConfig::BoneColor, 1.3);

			if (MenuConfig::ShowEyeRay)
				Render::ShowLosLine(Entity, 50, MenuConfig::EyeRayColor, 1.3);

			ImVec4 Rect;
			switch (MenuConfig::BoxType)
			{
			case 0:
				Rect = Render::Get2DBox(Entity);
				break;
			case 1:
				Rect = Render::Get2DBoneRect(Entity);
				break;
			default:
				break;
			}

			if (MenuConfig::ShowLineToEnemy)
				Render::LineToEnemy(Rect, MenuConfig::LineToEnemyColor, 1.2);

			if (MenuConfig::ShowBoxESP)
				Gui.Rectangle({ Rect.x,Rect.y }, { Rect.z,Rect.w }, MenuConfig::BoxColor, 1.3);

			if (MenuConfig::ShowHealthBar)
			{
				ImVec2 HealthBarPos, HealthBarSize;
				if (MenuConfig::HealthBarType == 0)
				{
					HealthBarPos = { Rect.x - 7.f,Rect.y };
					HealthBarSize = { 7 ,Rect.w };
				}
				else
				{
					HealthBarPos = { Rect.x + Rect.z / 2 - 70 / 2,Rect.y - 13 };
					HealthBarSize = { 70,8 };
				}
				Render::DrawHealthBar(Entity.Controller.Address, 100, Entity.Pawn.Health, HealthBarPos, HealthBarSize, MenuConfig::HealthBarType);
			}

			if (MenuConfig::ShowWeaponESP)
				Gui.StrokeText(Entity.Pawn.WeaponName, { Rect.x,Rect.y + Rect.w }, ImColor(255, 255, 255, 255), 14);

			if (MenuConfig::ShowDistance)
				Render::DrawDistance(LocalEntityPlayer, Entity, Rect);

			if (MenuConfig::ShowPlayerName)
			{
				if (MenuConfig::HealthBarType == 0)
					Gui.StrokeText(Entity.Controller.PlayerName, { Rect.x + Rect.z / 2,Rect.y - 14 }, ImColor(255, 255, 255, 255), 14, true);
				else
					Gui.StrokeText(Entity.Controller.PlayerName, { Rect.x + Rect.z / 2,Rect.y - 13 - 14 }, ImColor(255, 255, 255, 255), 14, true);
			}
		}

		if (MenuConfig::ShowRadar && LocalEntityPlayer.IsAlive())
			Radar.AddPoint(LocalEntityPlayer.Pawn.Pos, LocalEntityPlayer.Pawn.ViewAngle.y, LocalEntityPlayer.Pawn.Pos, ImColor(237, 85, 106, 200), LocalEntityPlayer.Pawn.ViewAngle.y, 2, LocalEntityPlayer.Pawn.Health);

		if (MenuConfig::ShowRadar)
		{
			Radar.Render();
			ImGui::End();
		}

		if (MenuConfig::TriggerMode == 0 && MenuConfig::TriggerBot && Keys::TriggerKey)
		{
			MenuConfig::Shoot = true;
			TriggerBot::Run(LocalEntityPlayer);
			MenuConfig::Shoot = false;
		}

		else if (MenuConfig::TriggerMode == 1 && MenuConfig::TriggerBot)
		{
			MenuConfig::Shoot = true;
			TriggerBot::Run(LocalEntityPlayer);
			MenuConfig::Shoot = false;
		}

		if (std::find(GunList::pistolsList.begin(), GunList::pistolsList.end(), LocalEntityPlayer.Pawn.WeaponName) != GunList::pistolsList.end()) {
			weaponTypeSmooth = 3;
		} // snipers
		else if (std::find(GunList::snipersList.begin(), GunList::snipersList.end(), LocalEntityPlayer.Pawn.WeaponName) != GunList::snipersList.end()) {
			weaponTypeSmooth = 2;
		} // rifles
		else if (std::find(GunList::riflesList.begin(), GunList::riflesList.end(), LocalEntityPlayer.Pawn.WeaponName) != GunList::riflesList.end()) {
			weaponTypeSmooth = 1;
		} // shotguns
		else if (std::find(GunList::shotgunsList.begin(), GunList::shotgunsList.end(), LocalEntityPlayer.Pawn.WeaponName) != GunList::shotgunsList.end()) {
			weaponTypeSmooth = 4;
		}

		if (MenuConfig::ShowAimFovRange)
			Render::DrawFovCircle(LocalEntityPlayer, weaponTypeSmooth);

		if (MenuConfig::AimBot && Keys::AimKey)
		{
			if (AimPos != Vec3(0, 0, 0))
			{
				AimControl::AimBot(LocalEntityPlayer, LocalEntityPlayer.Pawn.CameraPos, AimPos, weaponTypeSmooth);
			}
		}
	}
	catch (std::exception const& e)
	{
		//if (globalVars::debug) std::cout << e.what() << std::endl;

	}
}