#pragma once

#include <string>

#include <iostream>

class SettingsManager
{
public:
	std::string type = "none";

	std::string language = "en";

	std::string ip;

	int port;

	std::string uuid;

	void LoadSettings();
};

inline SettingsManager settingsJson;
