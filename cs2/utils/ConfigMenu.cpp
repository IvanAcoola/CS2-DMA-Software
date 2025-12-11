#include "ConfigMenu.hpp"
#include "../base/MenuConfig.hpp"
#include "ConfigSaver.hpp"
#include "../base/TriggerBot.h"
#include "../base/AimBot.hpp"
#include "../Language.h"
#include <filesystem>

namespace ConfigMenu {

    void RenderConfigMenu() {

		static char configNameBuffer[128] = "";

		ImGui::InputText(lang.config_newconfig.c_str(), configNameBuffer, sizeof(configNameBuffer));

		if (ImGui::Button(lang.config_create.c_str()))
		{
			std::string configFileName = std::string(configNameBuffer) + ".config";
			MyConfigSaver::SaveConfig(configFileName);
		}

		ImGui::Separator();

		static int selectedConfig = -1;

		const std::string configDir = MenuConfig::path;
		static std::vector<std::string> configFiles;

		configFiles.clear();
		for (const auto& entry : std::filesystem::directory_iterator(configDir))
		{
			if (entry.is_regular_file() && entry.path().extension() == ".config")
			{
				configFiles.push_back(entry.path().filename().string());
			}
		}

		for (int i = 0; i < configFiles.size(); ++i)
		{
			if (ImGui::Selectable(configFiles[i].c_str(), selectedConfig == i))
			{
				selectedConfig = i;
			}
		}
		ImGui::Separator();

		if (ImGui::Button(lang.config_load.c_str()) && selectedConfig >= 0 && selectedConfig < configFiles.size())
		{
			std::string selectedConfigFile = configFiles[selectedConfig];
			MyConfigSaver::LoadConfig(selectedConfigFile);
			Gui.delayticks = (1000000 / MenuConfig::MaxFrameRate) - 5000;
		}

		ImGui::SameLine();

		if (ImGui::Button(lang.config_save.c_str()) && selectedConfig >= 0 && selectedConfig < configFiles.size())
		{
			std::string selectedConfigFile = configFiles[selectedConfig];
			MyConfigSaver::SaveConfig(selectedConfigFile);
		}

		ImGui::SameLine();

		if (ImGui::Button(lang.config_delete.c_str()) && selectedConfig >= 0 && selectedConfig < configFiles.size())
		{
			std::string selectedConfigFile = configFiles[selectedConfig];
			std::string fullPath = configDir + "/" + selectedConfigFile;
			if (std::remove(fullPath.c_str()) == 0)
			{
				configFiles.erase(configFiles.begin() + selectedConfig);
				selectedConfig = -1;
			}
		}
    }

}
