#pragma once

#include <Windows.h>
#include <string>

namespace Offset
{
	inline DWORD EntityList;
	inline DWORD Matrix ;
	inline DWORD ViewAngle;
	inline DWORD LocalPlayerController;
	inline DWORD LocalPlayerPawn;
	inline DWORD ForceJump;
	inline DWORD GlobalVars;

	
	inline	DWORD Health;
	inline	DWORD TeamID;
	inline	DWORD IsAlive;
	inline	DWORD PlayerPawn;
	inline	DWORD iszPlayerName;
	inline	DWORD MoneyService;

	
	inline DWORD Pos;
	inline DWORD MaxHealth;
	inline DWORD CurrentHealth;
	inline DWORD Armor;
	inline DWORD GameSceneNode;
	inline DWORD BoneArray;
	inline DWORD MapName;
	inline DWORD angEyeAngles;
	inline DWORD vecLastClipCameraPos;
	inline DWORD pClippingWeapon;
	inline DWORD iShotsFired;
	inline DWORD flFlashDuration;
	inline DWORD aimPunchAngle;
	inline DWORD aimPunchCache;
	inline DWORD iIDEntIndex;
	inline DWORD iTeamNum;
	inline DWORD CameraServices;
	inline DWORD iFovStart;
	inline DWORD fFlags;
	inline DWORD bSpottedByMask;

	struct
	{
		DWORD RealTime = 0x00;
		DWORD FrameCount = 0x04;
		DWORD MaxClients = 0x10;
		DWORD IntervalPerTick = 0x14;
		DWORD CurrentTime = 0x2C;
		DWORD CurrentTime2 = 0x30;
		DWORD TickCount = 0x40;
		DWORD IntervalPerTick2 = 0x44;
		DWORD CurrentNetchan = 0x0048;
		DWORD CurrentMap = 0x0180;
		DWORD CurrentMapName = 0x0188;
	} inline GlobalVar;

	bool UpdateOffsets(std::string clientdata, std::string offsetdata);
}
