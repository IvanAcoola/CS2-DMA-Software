#include "Offsets.h"

#include "rapidjson/document.h"
#include <iostream>
#include <iomanip>

using namespace rapidjson;

bool Offset::UpdateOffsets(std::string offsetdata, std::string clientdata)
{
	Document offsets, client;
	offsets.Parse(offsetdata.c_str());
	client.Parse(clientdata.c_str());

	offsetdata.clear(); clientdata.clear();

	Offset::EntityList = offsets["client.dll"]["dwEntityList"].GetUint64();
	Offset::Matrix = offsets["client.dll"]["dwViewMatrix"].GetUint64();
	Offset::ViewAngle = offsets["client.dll"]["dwViewAngles"].GetUint64();
	Offset::LocalPlayerController = offsets["client.dll"]["dwLocalPlayerController"].GetUint64();
	Offset::LocalPlayerPawn = offsets["client.dll"]["dwLocalPlayerPawn"].GetUint64();
	Offset::GlobalVars = offsets["client.dll"]["dwGlobalVars"].GetUint64();
	Offset::Health = client["client.dll"]["classes"]["C_BaseEntity"]["fields"]["m_iHealth"].GetUint64();
	Offset::TeamID = client["client.dll"]["classes"]["C_BaseEntity"]["fields"]["m_iTeamNum"].GetUint64();
	Offset::Armor = client["client.dll"]["classes"]["CCSPlayerController"]["fields"]["m_iPawnArmor"].GetUint64();
	Offset::IsAlive = client["client.dll"]["classes"]["CCSPlayerController"]["fields"]["m_bPawnIsAlive"].GetUint64();
	Offset::MoneyService = client["client.dll"]["classes"]["CCSPlayerController"]["fields"]["m_pInGameMoneyServices"].GetUint64();
	Offset::PlayerPawn = client["client.dll"]["classes"]["CCSPlayerController"]["fields"]["m_hPlayerPawn"].GetUint64();
	Offset::iszPlayerName = client["client.dll"]["classes"]["CBasePlayerController"]["fields"]["m_iszPlayerName"].GetUint64();
	Offset::Pos = client["client.dll"]["classes"]["C_BasePlayerPawn"]["fields"]["m_vOldOrigin"].GetUint64();
	Offset::MaxHealth = client["client.dll"]["classes"]["C_BaseEntity"]["fields"]["m_iMaxHealth"].GetUint64();
	Offset::CurrentHealth = client["client.dll"]["classes"]["C_BaseEntity"]["fields"]["m_iHealth"].GetUint64();
	Offset::GameSceneNode = client["client.dll"]["classes"]["C_BaseEntity"]["fields"]["m_pGameSceneNode"].GetUint64();
	Offset::BoneArray = client["client.dll"]["classes"]["CSkeletonInstance"]["fields"]["m_modelState"].GetUint64() + 0x80;
	Offset::MapName = offsets["matchmaking.dll"]["dwGameTypes_mapName"].GetUint64();	// ERROR
	Offset::angEyeAngles = client["client.dll"]["classes"]["C_CSPlayerPawn"]["fields"]["m_angEyeAngles"].GetUint64();
	Offset::vecLastClipCameraPos = client["client.dll"]["classes"]["C_CSPlayerPawn"]["fields"]["m_vecLastClipCameraPos"].GetUint64();
	Offset::pClippingWeapon = client["client.dll"]["classes"]["C_CSPlayerPawn"]["fields"]["m_pClippingWeapon"].GetUint64(); // ERROR
	Offset::iShotsFired = client["client.dll"]["classes"]["C_CSPlayerPawn"]["fields"]["m_iShotsFired"].GetUint64();
	Offset::flFlashDuration = client["client.dll"]["classes"]["C_CSPlayerPawnBase"]["fields"]["m_flFlashDuration"].GetUint64();
	Offset::aimPunchAngle = client["client.dll"]["classes"]["C_CSPlayerPawn"]["fields"]["m_aimPunchAngle"].GetUint64();
	Offset::aimPunchCache = client["client.dll"]["classes"]["C_CSPlayerPawn"]["fields"]["m_aimPunchCache"].GetUint64();
	Offset::iIDEntIndex = client["client.dll"]["classes"]["C_CSPlayerPawn"]["fields"]["m_iIDEntIndex"].GetUint64();
	Offset::iTeamNum = client["client.dll"]["classes"]["C_BaseEntity"]["fields"]["m_iTeamNum"].GetUint64();
	Offset::CameraServices = client["client.dll"]["classes"]["C_BasePlayerPawn"]["fields"]["m_pCameraServices"].GetUint64();
	Offset::iFovStart = client["client.dll"]["classes"]["CCSPlayerBase_CameraServices"]["fields"]["m_iFOVStart"].GetUint64();
	Offset::fFlags = client["client.dll"]["classes"]["C_BaseEntity"]["fields"]["m_fFlags"].GetUint64();

	int m_entitySpottedState = client["client.dll"]["classes"]["C_CSPlayerPawn"]["fields"]["m_entitySpottedState"].GetUint64();
	int m_bSpottedByMask = client["client.dll"]["classes"]["EntitySpottedState_t"]["fields"]["m_bSpottedByMask"].GetUint64();
	Offset::bSpottedByMask = m_entitySpottedState + m_bSpottedByMask;

	//auto print_hex = [](const char* name, uint64_t value) {
	//	std::cout << std::left << std::setw(30) << name << " : 0x" << std::hex << value << std::dec << std::endl;
	//};
	//auto print_int = [](const char* name, int value) {
	//	std::cout << std::left << std::setw(30) << name << " : " << value << std::endl;
	//};

	//print_hex("EntityList", Offset::EntityList);
	//print_hex("Matrix", Offset::Matrix);
	//print_hex("ViewAngle", Offset::ViewAngle);
	//print_hex("LocalPlayerController", Offset::LocalPlayerController);
	//print_hex("LocalPlayerPawn", Offset::LocalPlayerPawn);
	//print_hex("GlobalVars", Offset::GlobalVars);
	//print_hex("Health", Offset::Health);
	//print_hex("TeamID", Offset::TeamID);
	//print_hex("Armor", Offset::Armor);
	//print_hex("IsAlive", Offset::IsAlive);
	//print_hex("MoneyService", Offset::MoneyService);
	//print_hex("PlayerPawn", Offset::PlayerPawn);
	//print_hex("iszPlayerName", Offset::iszPlayerName);
	//print_hex("Pos", Offset::Pos);
	//print_hex("MaxHealth", Offset::MaxHealth);
	//print_hex("CurrentHealth", Offset::CurrentHealth);
	//print_hex("GameSceneNode", Offset::GameSceneNode);
	//print_hex("BoneArray", Offset::BoneArray);
	//print_hex("MapName", Offset::MapName);
	//print_hex("angEyeAngles", Offset::angEyeAngles);
	//print_hex("vecLastClipCameraPos", Offset::vecLastClipCameraPos);
	//print_hex("pClippingWeapon", Offset::pClippingWeapon);
	//print_hex("iShotsFired", Offset::iShotsFired);
	//print_hex("flFlashDuration", Offset::flFlashDuration);
	//print_hex("aimPunchAngle", Offset::aimPunchAngle);
	//print_hex("aimPunchCache", Offset::aimPunchCache);
	//print_hex("iIDEntIndex", Offset::iIDEntIndex);
	//print_hex("iTeamNum", Offset::iTeamNum);
	//print_hex("CameraServices", Offset::CameraServices);
	//print_hex("iFovStart", Offset::iFovStart);
	//print_hex("fFlags", Offset::fFlags);

	//print_int("m_entitySpottedState", m_entitySpottedState);
	//print_int("m_bSpottedByMask", m_bSpottedByMask);
	//print_hex("bSpottedByMask", Offset::bSpottedByMask);

	return true;
}