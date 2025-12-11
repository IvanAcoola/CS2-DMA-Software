#include "setmgr/SettingsManager.h"

#include "Language.h"
#include "Globals.h"

#include "KMbox/KmboxB.h"
#include "KMbox/KmBoxNetManager.h"
#include "KMbox/kmboxNetPlusManager.cpp"

#ifndef NTSTATUS
typedef long NTSTATUS;
#endif

#include "CheatsThread.h"

#include <iostream>
#include <filesystem>
#include <windows.h>

#pragma comment(lib, "D3DX11.lib")

namespace fs = std::filesystem;

std::string readFile(const std::string& path) {
	std::ifstream file(path);
	if (!file) return "";
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}


void main(HMODULE module) {
	std::cout << " -- Software coded by github.com/IvanAcoola -- " << std::endl << std::endl;

	std::cout << "[ DMA ] Starting..." << std::endl;
	settingsJson.LoadSettings();
	std::cout << "[ DMA ] Settings parsed" << std::endl;
	{
		const auto& type = settingsJson.type;
		if (type == "net") {
			if (KmBoxMgr.InitDevice(settingsJson.ip, settingsJson.port, settingsJson.uuid) != 0)
			{
				std::cout << "[ DMA ] Error! KmBoxNet Initialize failed." << std::endl;
				return;
			}
			KmBox::type = "net";
			std::cout << "[ DMA ] Net connected!" << std::endl;
		}
		else if (type == "net+") {
			if (kmboxnew::kmNet_init(const_cast<char*>(settingsJson.ip.c_str()), (char*)settingsJson.port, const_cast<char*>(settingsJson.uuid.c_str()))) {
				std::cout << "[ DMA ] Error! KmBoxNet-2 Initialize failed." << std::endl;
				return;
			}
			KmBox::type = "net2";
			std::cout << "[ DMA ] Net+ connected!" << std::endl;
		}
		else if (type == "b") {
			if (kmBoxBMgr.init() != 0) {
				std::cout << "[ DMA ] Error! KmBoxB Initialize failed." << std::endl;
				return;
			}
			std::cout << "[ DMA ] BPro connected!" << std::endl;

			KmBox::type = "b";
		}
		else {
			KmBox::type = "None";
		}
	}

	auto ProcessStatus = ProcessMgr.Attach("cs2.exe");

	if (ProcessStatus != StatusCode::SUCCEED)
	{
		std::cout << "[ DMA ] Error! Failed to attach process, StatusCode:" << ProcessStatus << std::endl;
		return;
	}

	std::cout << "[ DMA ] Attached to game process" << std::endl;

	std::string offsets = readFile("offsets.json");
	std::string client = readFile("client_dll.json");

	Offset::UpdateOffsets(offsets, client);

	std::cout << "[ DMA ] Updated offsets" << std::endl;

	ProcessMgr.init_keystates();

	if (!gGame.InitAddress())
	{
		std::cout << "[ DMA ] Error! Failed to call InitAddress()." << std::endl;
		return;
	}

	if (!fs::directory_entry(MenuConfig::path).exists()) {
		fs::create_directory(MenuConfig::path);
	}

	std::cout << "[ DMA ] Starting threads..." << std::endl;

	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(UpdateMatrix), NULL, 0, 0);

	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(LoadLocalEntity), NULL, 0, 0);

	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(LoadEntity), NULL, 0, 0);

	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(UpdateEntityListEntry), NULL, 0, 0);

	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(ScatterReadThreads), NULL, 0, 0);

	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(UpdateWeaponNameThreads), NULL, 0, 0);

	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(KeysCheckThread), NULL, 0, 0);

	if (settingsJson.language == "en") lang.english();
	else if (settingsJson.language == "ch") lang.chineese();
	else lang.english();

	SetThreadPriority(GetCurrentThread(), HIGH_PRIORITY_CLASS);

	std::cout << "[ DMA ] Enjoy gameplay $" << std::endl;

	Gui.NewWindow("CS2DMA", Vec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), Cheats::Run);
}