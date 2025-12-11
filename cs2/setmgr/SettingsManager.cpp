#include "SettingsManager.h"


#include "rapidjson/document.h"

#include <fstream>
#include <sstream>
#include <filesystem>

void SettingsManager::LoadSettings()
{
    if (!std::filesystem::exists("config.json")) {
        std::cout << "[ DMA ] Config file not found!" << std::endl;
        return;
    }
	std::cout << "[ DMA ] Config file found" << std::endl;
    std::string readeddata;
    std::ifstream file("config.json");
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    readeddata = buffer.str();
    rapidjson::Document kmboxdata;
    kmboxdata.Parse(readeddata.c_str());

    this->type = kmboxdata["type"].GetString();
    this->language = kmboxdata["en"].GetString(); // en or ch

    if ((this->type != "net") && (this->type != "net+")) return;

    this->ip = kmboxdata["ip"].GetString();
    this->port = kmboxdata["port"].GetInt64();
    this->uuid = kmboxdata["uuid"].GetString();

    return;
}
