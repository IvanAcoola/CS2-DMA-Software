#pragma once

#include "../radar/mapsdata.h"
#include "Game.h"
#include "Entity.h"
#include "AimBot.hpp"
#include "../radar/Radar.h"
#include "TriggerBot.h"


namespace Cheats
{
	void Menu();
	void RadarSetting(Base_Radar& Radar);
	void Run();
	inline CEntity LocalEntityPlayer;

	inline std::vector<CEntity> EntityList;

	inline char mapname[32];
}
