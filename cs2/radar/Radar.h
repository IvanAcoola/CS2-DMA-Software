#pragma once
#define _USE_MATH_DEFINES
#include <../Globals.h>
#include "../base/Game.h"
#include "../OS-ImGui/OS-ImGui.h"
#include <math.h>
#include <tuple>


class Base_Radar
{
public:

	void SetPos(const Vec2& Pos);

	void SetDrawList(ImDrawList* DrawList);

	Vec2 GetPos();

	void AddPoint(const Vec3& LocalPos, const float& LocalYaw, const Vec3& Pos, ImColor Color, float Yaw = 0.0f, int same_team = 1, float hp = 100, int is_bomb = 0);

	void UpdateMap(std::string mapname);

public:
	ImDrawList* DrawList = nullptr;

	bool Opened = true;

	void Render();

private:
	std::pair<int, int> rotate_point(const std::pair<int, int>& center, const std::pair<int, int>& point, double angle);

	std::pair<int, int> world_to_minimap2(double x, double y, double pos_x, double pos_y, double scale, int map_w, int map_h);

	std::pair<int, int> world_to_minimap3(double x, double y, double pos_x, double pos_y, double scale, int map_w, int map_h);

	Vec2  Pos{ 0,0 };

	float Width = 200;

	std::vector<std::pair<Vec2, std::vector<std::pair<int, float>>>> Points_new;
};