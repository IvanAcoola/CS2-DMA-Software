#include "CheatsThread.h"

#include <winnt.h>

#include <thread>


using namespace Cheats;


VOID UpdateMatrix()
{
	while (true)
	{
		Sleep(1);

		if (!ProcessMgr.ReadMemory(gGame.GetMatrixAddress(), gGame.View.Matrix, 64))
			return;
	}
}

VOID LoadLocalEntity()
{
	while (true)
	{
		try {
			Sleep(1);
			DWORD64 LocalControllerAddress = 0;
			DWORD64 LocalPawnAddress = 0;
			if (!ProcessMgr.ReadMemory(gGame.GetLocalControllerAddress(), LocalControllerAddress))
				continue;
			if (!ProcessMgr.ReadMemory(gGame.GetLocalPawnAddress(), LocalPawnAddress))
				continue;
			CEntity LocalPlayer;
			if (!LocalPlayer.UpdateController(LocalControllerAddress))
				continue;
			if (!LocalPlayer.UpdatePawn(LocalPawnAddress))
				continue;

			LocalEntityPlayer = LocalPlayer;
		}
		catch (const std::exception& ex) {
			//std::cout << "2: " << ex.what() << std::endl;
		}
	}
}
std::vector<CEntity> TempEntityList;

bool isSameCEntity(std::vector<CEntity>list1, std::vector<CEntity>list2) {
	bool isSame = true;
	if (list1.size() != list2.size()) {
		isSame = false;
	}
	return isSame;
}

VOID UpdatePlayer(int index) {
	try {
		CEntity Entity;
		DWORD64 EntityAddress = 0;

		if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetEntityListEntry() + (index + 1) * 0x70, EntityAddress))
			return;


		if (EntityAddress == LocalEntityPlayer.Controller.Address)
		{
			LocalEntityPlayer.LocalPlayerControllerIndex = index;
			return;
		}


		if (!Entity.UpdateController(EntityAddress))
			return;

		if (!Entity.UpdatePawn(Entity.Pawn.Address))
			return;

		if (!Entity.IsAlive())
			return;

		TempEntityList.push_back(Entity);
	}
	catch (const std::exception& ex) {
		//std::cout << "Catched exception while get player: " << ex.what() << std::endl;
	}

}
VOID LoadEntity()
{
	while (true)
	{
		try {
			if (LocalEntityPlayer.Controller.Address == 0) {
				continue;
			}

			std::vector<std::thread> threads;
			TempEntityList.clear();
			for (int i = 0; i < 64; i++)
			{
				threads.push_back(std::thread(UpdatePlayer, i));
			}
			for (auto& t : threads) {
				if (t.joinable()) {
					t.join();
				}
			}
			threads.clear();

			if (!isSameCEntity(EntityList, TempEntityList)) {
				EntityList = TempEntityList;
			}
		}
		catch (const std::exception& ex) {
			//std::cout << "LoadEntity: " << ex.what() << std::endl;
		}
		Sleep(1);
	}
}

VOID UpdateEntityListEntry()
{
	while (true)
	{
		try {
			gGame.UpdateEntityListEntry();

			uintptr_t mapaddress;
			uintptr_t mapaddress2;


			ProcessMgr.ReadMemory(gGame.GetClientDLLAddress() + Offset::GlobalVars, mapaddress);

			ProcessMgr.ReadMemory(mapaddress + 0x0180, mapaddress2);

			ProcessMgr.ReadMemory(mapaddress2, mapname);

			Sleep(5000);
		}
		catch (const std::exception& ex) {
			//std::cout << "4: " << ex.what() << std::endl;
		}
		catch (const std::string& ex) {
			//std::cout << "4: " << ex << std::endl;
		}
		catch (...) {
			//std::cout << "4: " << std::endl;
		}
	}
}

VOID UpdateWeaponName(int index) {
	if (EntityList.size() <= index) return;
	EntityList[index].Pawn.GetWeaponName();
}

VOID UpdateVlue(int index) {

	std::vector<BoneJointPos> BonePosList;
	try {

		for (int i = 0; i < 30; i++)
		{
			Vec2 ScreenPos;
			bool IsVisible = false;

			if (EntityList.size() <= index) return;

			if (gGame.View.WorldToScreen(EntityList[index].TempBoneArray[i].Pos, ScreenPos))
				IsVisible = true;

			if (EntityList.size() <= index) return;
			BonePosList.push_back({ EntityList[index].TempBoneArray[i].Pos ,ScreenPos,IsVisible });
		}
		if (EntityList.size() <= index) return;

		EntityList[index].Pawn.BoneData.BonePosList = BonePosList;

		EntityList[index].Pawn.Pos = EntityList[index].TempPos;
		EntityList[index].Pawn.Health = EntityList[index].TempHealth;
		EntityList[index].Pawn.ViewAngle = EntityList[index].TempViewAngle;
		EntityList[index].Pawn.bSpottedByMask = EntityList[index].TempbSpottedByMask;

		BonePosList.clear();
	}
	catch (const std::exception& ex) {
		//std::cout << "UpdateVlue " << ex.what() << std::endl;
		BonePosList.clear();
	}
}

VOID ScatterReadThreads()
{
	while (true)
	{
		try {
			Sleep(1);

			VMMDLL_SCATTER_HANDLE handle = ProcessMgr.CreateScatterHandle();

			for (int i = 0; i < EntityList.size(); i++)
			{
				ProcessMgr.AddScatterReadRequest(handle, EntityList[i].Pawn.BoneData.BoneArrayAddress, EntityList[i].TempBoneArray, 30 * sizeof(BoneJointData));
				ProcessMgr.AddScatterReadRequest(handle, EntityList[i].Pawn.Address + Offset::Pos, &EntityList[i].TempPos, sizeof(Vec3));
				ProcessMgr.AddScatterReadRequest(handle, EntityList[i].Pawn.Address + Offset::CurrentHealth, &EntityList[i].TempHealth, sizeof(int));
				ProcessMgr.AddScatterReadRequest(handle, EntityList[i].Pawn.Address + Offset::angEyeAngles, &EntityList[i].TempViewAngle, sizeof(Vec2));
				ProcessMgr.AddScatterReadRequest(handle, EntityList[i].Pawn.Address + Offset::bSpottedByMask, &EntityList[i].TempbSpottedByMask, sizeof(DWORD64));
			}
			ProcessMgr.ExecuteReadScatter(handle);


			std::vector<std::thread> threads;
			for (int i = 0; i < EntityList.size(); i++)
			{
				threads.push_back(std::thread(UpdateVlue, i));
			}
			for (auto& t : threads) {
				if (t.joinable()) {
					t.join();
				}
			}
			threads.clear();
		}
		catch (const std::exception& ex) {
			//std::cout << "5: " << ex.what() << std::endl;
		}
		catch (const std::string& ex) {
			//std::cout << "5: " << ex << std::endl;
		}
		catch (...) {
			//std::cout << "5: " << std::endl;
		}
	}
}

VOID UpdateWeaponNameThreads()
{
	while (true)
	{
		try {
			Sleep(100);

			std::vector<std::thread> threads;
			for (int i = 0; i < EntityList.size(); i++)
			{
				if (EntityList.size() <= i) return;
				threads.push_back(std::thread(UpdateWeaponName, i));
			}
			for (auto& t : threads) {
				if (t.joinable()) {
					t.join();
				}
			}
			threads.clear();
		}
		catch (const std::exception& ex) {
			//std::cout << "6: " << ex.what() << std::endl;
		}
		catch (const std::string& ex) {
			//std::cout << "6: " << ex << std::endl;
		}
		catch (...) {
			//std::cout << "6: " << std::endl;
		}
	}
}

VOID KeysCheckThread() {
	while (true)
	{
		Sleep(10);
		Keys::LeftKey = ProcessMgr.is_key_down(VK_LBUTTON);
		Keys::MenuKey = ProcessMgr.is_key_down(VK_F8);
		Keys::AimKey = ProcessMgr.is_key_down(AimControl::HotKey);
		Keys::TriggerKey = ProcessMgr.is_key_down(TriggerBot::HotKey);
	}
}
