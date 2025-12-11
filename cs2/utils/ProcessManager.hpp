#pragma once
#include "../Globals.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include <Tlhelp32.h>
#include <atlconv.h>
#include <leechcore.h>
#include <vmmdll.h>
#include <chrono>
#include <string>

#define _is_invalid(v) if(v==NULL) return false
#define _is_invalid(v,n) if(v==NULL) return n

/**
 * @file ProcessManager.hpp
 * @brief Lightweight wrapper around VMMDLL to manage target process access and memory operations.
 *
 * This header defines the `ProcessManager` class which provides process discovery,
 * read/write memory helpers (including scatter reads), registry queries and a small
 * keyboard state helper using kernel exports. Designed to encapsulate VMMDLL usage
 * for the project.
 */

/**
 * @enum StatusCode
 * @brief Return codes for process attach operations.
 */
enum StatusCode
{
	/// Operation succeeded.
	SUCCEED,
	/// Failed to obtain the target process ID.
	FAILE_PROCESSID,
	/// Failed to obtain a process handle (unused with VMM).
	FAILE_HPROCESS,
	/// Failed to find a module.
	FAILE_MODULE,
};

/**
 * @struct Info
 * @brief Small information record used for enumerating processes/modules.
 */
struct Info
{
	/// Index in an enumeration.
	uint32_t index;
	/// Process identifier (PID).
	uint32_t process_id;
	/// Directory table base (DTB) value if available.
	uint64_t dtb;
	/// Kernel address associated with the entry.
	uint64_t kernelAddr;
	/// Friendly name for the process/module.
	std::string name;
};

/**
 * @class ProcessManager
 * @brief Encapsulates VMMDLL-based process management and memory helpers.
 *
 * Responsibilities:
 * - Initialize/attach to VMMDLL.
 * - Find and refresh the target process PID.
 * - Provide typed read/write memory helpers, including scatter reads.
 * - Provide registry query helper and keyboard state helpers backed by kernel exports.
 *
 * Note: This class uses VMMDLL APIs and therefore uses VMMDLL-specific flags and
 * conventions (e.g. process IDs passed to VMMDLL functions).
 */
class ProcessManager
{
private:

	bool   Attached = false;

	uint64_t gafAsyncKeyStateExport = 0;

	uint8_t state_bitmap[64]{ };

	uint8_t previous_state_bitmap[256 / 8]{ };
	uint64_t win32kbase = 0;

	int win_logon_pid = 0;
	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

	DWORD  ProcessID2 = 0;

public:
	std::string AttachProcessName;
	HANDLE hProcess = 0;
	DWORD  ProcessID = 0;
	VMM_HANDLE HANDLE;
public:
	~ProcessManager()
	{

	}
	StatusCode Attach(std::string ProcessName)
	{
		this->AttachProcessName = ProcessName;
		LPSTR args[] = { (LPSTR)"",(LPSTR)"-device", (LPSTR)"FPGA",(LPSTR)"-norefresh" };
		this->HANDLE = VMMDLL_Initialize(3, args);

		if (this->HANDLE) {
			SIZE_T pcPIDs;
			VMMDLL_PidList(this->HANDLE, nullptr, &pcPIDs);
			DWORD* pPIDs = (DWORD*)new char[pcPIDs * 4];
			VMMDLL_PidList(this->HANDLE, pPIDs, &pcPIDs);
			for (int i = 0; i < pcPIDs; i++)
			{
				VMMDLL_PROCESS_INFORMATION ProcessInformation = { 0 };
				ProcessInformation.magic = VMMDLL_PROCESS_INFORMATION_MAGIC;
				ProcessInformation.wVersion = VMMDLL_PROCESS_INFORMATION_VERSION;
				SIZE_T pcbProcessInformation = sizeof(VMMDLL_PROCESS_INFORMATION);
				VMMDLL_ProcessGetInformation(this->HANDLE, pPIDs[i], &ProcessInformation, &pcbProcessInformation);


				if (strcmp(ProcessInformation.szName, "cs2.exe") == 0) {
					ProcessID = pPIDs[i];
				}


			}
		}
		_is_invalid(ProcessID, FAILE_PROCESSID);

		Attached = true;

		return SUCCEED;
	}

	void RefindGame() {
		if (this->HANDLE) {
			SIZE_T pcPIDs;
			VMMDLL_PidList(this->HANDLE, nullptr, &pcPIDs);
			DWORD* pPIDs = (DWORD*)new char[pcPIDs * 4];
			VMMDLL_PidList(this->HANDLE, pPIDs, &pcPIDs);
			for (int i = 0; i < pcPIDs; i++)
			{
				VMMDLL_PROCESS_INFORMATION ProcessInformation = { 0 };
				ProcessInformation.magic = VMMDLL_PROCESS_INFORMATION_MAGIC;
				ProcessInformation.wVersion = VMMDLL_PROCESS_INFORMATION_VERSION;
				SIZE_T pcbProcessInformation = sizeof(VMMDLL_PROCESS_INFORMATION);
				VMMDLL_ProcessGetInformation(this->HANDLE, pPIDs[i], &ProcessInformation, &pcbProcessInformation);


				if (strcmp(ProcessInformation.szName, "cs2.exe") == 0) {
					ProcessID = pPIDs[i];
				}


			}
		}
	}

	bool findProcessByName(std::string ProcessName) {
		SIZE_T pcPIDs;
		VMMDLL_PidList(this->HANDLE, nullptr, &pcPIDs);
		DWORD* pPIDs = (DWORD*)new char[pcPIDs * 4];
		VMMDLL_PidList(this->HANDLE, pPIDs, &pcPIDs);
		for (int i = 0; i < pcPIDs; i++)
		{
			VMMDLL_PROCESS_INFORMATION ProcessInformation = { 0 };
			ProcessInformation.magic = VMMDLL_PROCESS_INFORMATION_MAGIC;
			ProcessInformation.wVersion = VMMDLL_PROCESS_INFORMATION_VERSION;
			SIZE_T pcbProcessInformation = sizeof(VMMDLL_PROCESS_INFORMATION);
			VMMDLL_ProcessGetInformation(this->HANDLE, pPIDs[i], &ProcessInformation, &pcbProcessInformation);


			if (strcmp(ProcessInformation.szName, ProcessName.c_str()) == 0) {
				return true;
			}
		}
		return false;
	}

	void Detach()
	{
		if (hProcess)
			CloseHandle(hProcess);
		hProcess = 0;
		ProcessID = 0;
		Attached = false;
	}

	bool IsActive()
	{
		if (!Attached)
			return false;
		DWORD ExitCode{};
		return true;
	}

	template <typename ReadType>
	bool ReadMemory(DWORD64 Address, ReadType& Value, int Size)
	{
		_is_invalid(ProcessID, false);
		if (VMMDLL_MemReadEx(this->HANDLE, ProcessID, Address, (PBYTE)&Value, Size, 0, VMMDLL_FLAG_NOCACHE | VMMDLL_FLAG_NOPAGING | VMMDLL_FLAG_ZEROPAD_ON_FAIL | VMMDLL_FLAG_NOPAGING_IO))
			return true;
		return false;
	}

	template <typename ReadType>
	bool ReadMemory(DWORD64 Address, ReadType& Value)
	{
		_is_invalid(ProcessID, false);

		if (VMMDLL_MemReadEx(this->HANDLE, ProcessID, Address, (PBYTE)&Value, sizeof(ReadType), 0, VMMDLL_FLAG_NOCACHE | VMMDLL_FLAG_NOPAGING | VMMDLL_FLAG_ZEROPAD_ON_FAIL | VMMDLL_FLAG_NOPAGING_IO))
			return true;
		return false;
	}

	VMMDLL_SCATTER_HANDLE CreateScatterHandle()
	{
		return VMMDLL_Scatter_Initialize(this->HANDLE, ProcessID, VMMDLL_FLAG_NOCACHE);
	}

	void AddScatterReadRequest(VMMDLL_SCATTER_HANDLE handle, uint64_t address, void* buffer, size_t size)
	{
		VMMDLL_Scatter_PrepareEx(handle, address, size, (PBYTE)buffer, NULL);
	}
	void ExecuteReadScatter(VMMDLL_SCATTER_HANDLE handle)
	{
		VMMDLL_Scatter_ExecuteRead(handle);
		VMMDLL_Scatter_Clear(handle, ProcessID, NULL);
	}

	template <typename ReadType>
	bool WriteMemory(DWORD64 Address, ReadType& Value, int Size)
	{
		_is_invalid(ProcessID, false);
		if (VMMDLL_MemWrite(this->HANDLE, ProcessID, Address, (PBYTE)&Value, Size))
			return true;
		return false;
	}

	template <typename ReadType>
	bool WriteMemory(DWORD64 Address, ReadType& Value)
	{
		_is_invalid(ProcessID, false);

		if (VMMDLL_MemWrite(this->HANDLE, ProcessID, Address, (PBYTE)&Value, sizeof(ReadType)))
			return true;
		return false;
	}


	DWORD64 TraceAddress(DWORD64 BaseAddress, std::vector<DWORD> Offsets)
	{
		_is_invalid(ProcessID, 0);
		DWORD64 Address = 0;

		if (Offsets.size() == 0)
			return BaseAddress;

		if (!ReadMemory<DWORD64>(BaseAddress, Address))
			return 0;

		for (int i = 0; i < Offsets.size() - 1; i++)
		{
			if (!ReadMemory<DWORD64>(Address + Offsets[i], Address))
				return 0;
		}
		return Address == 0 ? 0 : Address + Offsets[Offsets.size() - 1];
	}

	template <typename T>
	T ReadMemoryExtra(uintptr_t address, DWORD pid = ProcessID2, bool cache = false, const DWORD size = sizeof(T))
	{
		T buffer{};
		DWORD bytes_read = 0;
		if (!cache)
			VMMDLL_MemReadEx(this->HANDLE, pid, address, (PBYTE)&buffer, size, &bytes_read, VMMDLL_FLAG_NOCACHE);
		else
			VMMDLL_MemReadEx(this->HANDLE, pid, address, (PBYTE)&buffer, size, &bytes_read, VMMDLL_FLAG_CACHE_RECENT_ONLY);
		return buffer;
	}

	DWORD GetProcID_Keys(LPSTR proc_name)
	{
		DWORD procID = 0;
		VMMDLL_PidGetFromName(this->HANDLE, (LPSTR)proc_name, &procID);
		return procID;
	}

	std::vector<int> GetPidListFromName(std::string name)
	{
		PVMMDLL_PROCESS_INFORMATION process_info = NULL;
		DWORD total_processes = 0;
		std::vector<int> list = { };

		if (!VMMDLL_ProcessGetInformationAll(this->HANDLE, &process_info, &total_processes))
		{
			return list;
		}

		for (size_t i = 0; i < total_processes; i++)
		{
			auto process = process_info[i];
			if (strstr(process.szNameLong, name.c_str()))
				list.push_back(process.dwPID);
		}

		return list;
	}

	enum class e_registry_type
	{
		none = REG_NONE,
		sz = REG_SZ,
		expand_sz = REG_EXPAND_SZ,
		binary = REG_BINARY,
		dword = REG_DWORD,
		dword_little_endian = REG_DWORD_LITTLE_ENDIAN,
		dword_big_endian = REG_DWORD_BIG_ENDIAN,
		link = REG_LINK,
		multi_sz = REG_MULTI_SZ,
		resource_list = REG_RESOURCE_LIST,
		full_resource_descriptor = REG_FULL_RESOURCE_DESCRIPTOR,
		resource_requirements_list = REG_RESOURCE_REQUIREMENTS_LIST,
		qword = REG_QWORD,
		qword_little_endian = REG_QWORD_LITTLE_ENDIAN
	};

	std::string QueryValue(const char* path, e_registry_type type)
	{
		BYTE buffer[0x128];
		DWORD _type = static_cast<DWORD>(type);
		DWORD size = sizeof(buffer);

		if (!VMMDLL_WinReg_QueryValueExU(this->HANDLE, const_cast<LPSTR>(path), &_type, buffer, &size))
		{
			return "";
		}

		std::wstring wstr = std::wstring(reinterpret_cast<wchar_t*>(buffer));
		return std::string(wstr.begin(), wstr.end());
	}

	void init_keystates() {
		std::string win = QueryValue("HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\CurrentBuild", e_registry_type::sz);
		int Winver = 0;
		if (!win.empty())
			Winver = std::stoi(win);

		this->win_logon_pid = GetProcID_Keys((LPSTR)"winlogon.exe");

		if (Winver > 22000) {
			auto pids = GetPidListFromName("csrss.exe");
			for (size_t i = 0; i < pids.size(); i++)
			{
				auto pid = pids[i];
				uintptr_t tmp = VMMDLL_ProcessGetModuleBaseU(this->HANDLE, pid, const_cast<LPSTR>("win32ksgd.sys"));
				uintptr_t g_session_global_slots = tmp + 0x3110;
				uintptr_t user_session_state = ReadMemoryExtra<uintptr_t>(ReadMemoryExtra<uintptr_t>(ReadMemoryExtra<uintptr_t>(g_session_global_slots, pid), pid), pid);
				gafAsyncKeyStateExport = user_session_state + 0x3690;
				if (gafAsyncKeyStateExport > 0x7FFFFFFFFFFF)
					break;
			}
			if (!(gafAsyncKeyStateExport > 0x7FFFFFFFFFFF))
				std::cout << "[ WG ] Error: Keys-1" << std::endl;
		} else {
			PVMMDLL_MAP_EAT eat_map = NULL;
			PVMMDLL_MAP_EATENTRY eat_map_entry;
			bool result = VMMDLL_Map_GetEATU(this->HANDLE, GetProcID_Keys((LPSTR)"winlogon.exe") | VMMDLL_PID_PROCESS_WITH_KERNELMEMORY, (LPSTR)"win32kbase.sys", &eat_map);
			for (int i = 0; i < eat_map->cMap; i++)
			{
				eat_map_entry = eat_map->pMap + i;
				if (strcmp(eat_map_entry->uszFunction, "gafAsyncKeyState") == 0)
				{
					gafAsyncKeyStateExport = eat_map_entry->vaFunction;
					break;
				}
			}
			VMMDLL_MemFree(eat_map);
			eat_map = NULL;

		}
	}

	void update_key_state_bitmap() {
		uint8_t previous_key_state_bitmap[64] = { 0 };
		memcpy(previous_key_state_bitmap, state_bitmap, 64);

		VMMDLL_MemReadEx(this->HANDLE, this->win_logon_pid | VMMDLL_PID_PROCESS_WITH_KERNELMEMORY, gafAsyncKeyStateExport, (PBYTE)&state_bitmap, 64, NULL, VMMDLL_FLAG_NOCACHE);
		for (int vk = 0; vk < 256; ++vk)
			if ((state_bitmap[(vk * 2 / 8)] & 1 << vk % 4 * 2) && !(previous_key_state_bitmap[(vk * 2 / 8)] & 1 << vk % 4 * 2))
				previous_state_bitmap[vk / 8] |= 1 << vk % 8;
	}

	bool is_key_down(uint32_t virtual_key_code) {
		if (gafAsyncKeyStateExport < 0x7FFFFFFFFFFF)
			return false;
		if (std::chrono::system_clock::now() - start > std::chrono::milliseconds(1))
		{
			update_key_state_bitmap();
			start = std::chrono::system_clock::now();
		}
		return state_bitmap[(virtual_key_code * 2 / 8)] & 1 << virtual_key_code % 4 * 2;
	}
};

inline ProcessManager ProcessMgr;