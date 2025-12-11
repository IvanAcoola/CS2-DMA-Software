#pragma once

#include "../Language.h"
#include "../Globals.h"

#include "Cheats.h"
#include "Render.hpp"
#include "MenuConfig.hpp"
#include "../utils/ConfigMenu.hpp"
#include "../utils/ConfigSaver.hpp"


void setStyles() {

	ImGuiStyle* style = &ImGui::GetStyle();

	style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 5.0f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 4.0f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 3.0f;

	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.8f, 0.11f, 0.82f, 0.40f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_Tab] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TabHovered] = ImVec4(0.10f, 0.10f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TabActive] = ImVec4(0.10f, 0.11f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);

	if (MenuConfig::MaxFrameRate) Gui.delayticks = (1000000 / MenuConfig::MaxFrameRate) - 5000;
	else Gui.delayticks = 0;
}

void Cheats::Menu()
{
	//ImGui::ShowMetricsWindow();
	static int active_tab = 0;

	static int active_sub_tab = 0;

	static bool IsMenuInit = false;

	if (!IsMenuInit)
	{
		setStyles();
		IsMenuInit = true;
	}

	ImGui::GetIO().Fonts->Fonts[0];

	ImGui::Begin("CS 2 / DMA", nullptr, ImGuiWindowFlags_NoDecoration);
	ImGui::SetWindowSize({ globalVars::windowx, globalVars::windowy });
	{
		ImGui::BeginChild("Container##1", ImVec2((globalVars::windowx) / 10 * 2.3, globalVars::windowy - 30), true);
		{
			static float subblockw = 2.0;

			ImGui::BeginChild("Logo", ImVec2((globalVars::windowx) / 10 * subblockw, 50), false);
			{
				ImGui::PushFont(Gui.iconFont);
				ImGui::GetWindowDrawList()->AddText(ImVec2(ImGui::GetWindowPos().x + 10, ImGui::GetWindowPos().y + 10), ImColor(255, 255, 255), "github.com/IvanAcoola");
				ImGui::PopFont();
				ImGui::GetWindowDrawList()->AddText(ImVec2(ImGui::GetWindowPos().x + 10, ImGui::GetWindowPos().y + 25), ImColor(255, 255, 255), "free to use");
			}
			ImGui::EndChild();
			ImGui::BeginChild("ButtonBlock", ImVec2((globalVars::windowx) / 10 * subblockw, 313), false);
			{
				ImGui::Separator();

				ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 40);

				if (KmBox::type != "None" && ImGui::Button(lang.tab_aimbot.c_str(), ImVec2((globalVars::windowx) / 10 * subblockw - 10, 30))) active_tab = 0;
				if (KmBox::type != "None" && ImGui::Button(lang.tab_trigger.c_str(), ImVec2((globalVars::windowx) / 10 * subblockw - 10, 30))) active_tab = 1;
				if (ImGui::Button(lang.tab_visuals.c_str(), ImVec2((globalVars::windowx) / 10 * subblockw - 10, 30))) active_tab = 2;
				if (ImGui::Button(lang.tab_radar.c_str(), ImVec2((globalVars::windowx) / 10 * subblockw - 10, 30))) active_tab = 3;
				if (ImGui::Button(lang.tab_settings.c_str(), ImVec2((globalVars::windowx) / 10 * subblockw - 10, 30))) active_tab = 4;
				if (ImGui::Button(lang.tab_config.c_str(), ImVec2((globalVars::windowx) / 10 * subblockw - 10, 30))) active_tab = 5;
			}
			ImGui::EndChild();
			ImGui::BeginChild("Language Block", ImVec2((globalVars::windowx) / 10 * subblockw, 60), false);
			{
				ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 20);

				if (ImGui::Combo("##", &MenuConfig::SelectedLanguage, lang.utilities_langselect, IM_ARRAYSIZE(lang.utilities_langselect)))
				{
					switch (MenuConfig::SelectedLanguage)
					{
					case 0:
						lang.english();
						break;
					case 1:
						lang.chineese();
						break;
					default:
						break;
					}
				}
			}
			ImGui::EndChild();

		}
		ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginChild("Container##2", ImVec2((globalVars::windowx) / 10 * 7.2, globalVars::windowy - 30), true);
		{
			if (active_tab == 0) { // Aimbot
				Gui.MyCheckBox(lang.aimbot_enable.c_str(), &MenuConfig::AimBot);
			
				if (MenuConfig::AimBot) {
					ImGui::SameLine();
					Gui.MyCheckBox(lang.aimbot_showaimfov.c_str(), &MenuConfig::ShowAimFovRange);
					Gui.MyCheckBox(lang.aimbot_recolcontrol.c_str(), &AimControl::RecoilControl);
					if (MenuConfig::ShowAimFovRange) {
						ImGui::SameLine();
						ImGui::ColorEdit4(lang.aimbot_aimfovcolor.c_str(), reinterpret_cast<float*>(&MenuConfig::AimFovRangeColor), ImGuiColorEditFlags_NoInputs);
					}

					if (ImGui::Combo(lang.aimbot_hotkey.c_str(), &MenuConfig::AimBotHotKey, lang.aimbot_hotkeyselect, IM_ARRAYSIZE(lang.aimbot_hotkeyselect)))
					{
						AimControl::SetHotKey(MenuConfig::AimBotHotKey);
					}

					Gui.MyCheckBox(lang.aimbot_autoshot.c_str(), &AimControl::AutoShot);

					ImGui::SameLine();

					Gui.MyCheckBox(lang.aimbot_visiblecheck.c_str(), &MenuConfig::VisibleCheck);

					ImGui::SameLine();

					Gui.MyCheckBox(lang.aimbot_ignoreonshot.c_str(), &AimControl::ignoreOnShot);

					float FovMin = 0.1f, FovMax = 89.f;

					ImGui::Separator();

					if (ImGui::Button(lang.aimbot_rifles.c_str(), ImVec2(70, 30))) active_sub_tab = 0;
					ImGui::SameLine();
					if(ImGui::Button(lang.aimbot_pistols.c_str(), ImVec2(70, 30))) active_sub_tab = 1;
					ImGui::SameLine();
					if (ImGui::Button(lang.aimbot_snipers.c_str(), ImVec2(70, 30))) active_sub_tab = 2;
					ImGui::SameLine();
					if (ImGui::Button(lang.aimbot_shotguns.c_str(), ImVec2(70, 30))) active_sub_tab = 3;
					ImGui::SameLine();
					if(ImGui::Button(lang.aimbot_other.c_str(), ImVec2(70, 30))) active_sub_tab = 4;

					float SmoothMin, SmoothMax;
					SmoothMin = 1.2f; SmoothMax = 10.f;

					if (active_sub_tab == 0) { // rifles
						Gui.SliderScalarEx1(lang.aimbot_fov.c_str(), ImGuiDataType_Float, &AimControl::AimFovRifles, &FovMin, &FovMax, "%.1f", ImGuiSliderFlags_None);

						Gui.SliderScalarEx1(lang.aimbot_smooth.c_str(), ImGuiDataType_Float, &AimControl::SmoothRifles, &SmoothMin, &SmoothMax, "%.1f", ImGuiSliderFlags_None);

						if (ImGui::Combo(lang.aimbot_posrifles.c_str(), &MenuConfig::AimPositionRifles, lang.aimbot_posselect, IM_ARRAYSIZE(lang.aimbot_posselect)))
						{
							switch (MenuConfig::AimPositionRifles)
							{
							case 0:
								MenuConfig::AimPositionIndexRifles = BONEINDEX::head;
								break;
							case 1:
								MenuConfig::AimPositionIndexRifles = BONEINDEX::neck_0;
								break;
							case 2:
								MenuConfig::AimPositionIndexRifles = BONEINDEX::spine_1;
								break;
							default:
								break;
							}
						}
					}
					else if (active_sub_tab == 1) { // pistols
						Gui.SliderScalarEx1(lang.aimbot_fov.c_str(), ImGuiDataType_Float, &AimControl::AimFovPistols, &FovMin, &FovMax, "%.1f", ImGuiSliderFlags_None);

						Gui.SliderScalarEx1(lang.aimbot_smooth.c_str(), ImGuiDataType_Float, &AimControl::SmoothPistols, &SmoothMin, &SmoothMax, "%.1f", ImGuiSliderFlags_None);

						if (ImGui::Combo(lang.aimbot_pospis.c_str(), &MenuConfig::AimPositionPistol, lang.aimbot_posselect, IM_ARRAYSIZE(lang.aimbot_posselect)))
						{
							switch (MenuConfig::AimPositionPistol)
							{
							case 0:
								MenuConfig::AimPositionIndexPistol = BONEINDEX::head;
								break;
							case 1:
								MenuConfig::AimPositionIndexPistol = BONEINDEX::neck_0;
								break;
							case 2:
								MenuConfig::AimPositionIndexPistol = BONEINDEX::spine_1;
								break;
							default:
								break;
							}
						}
					}
					else if (active_sub_tab == 2) { // snipers
						Gui.SliderScalarEx1(lang.aimbot_fov.c_str(), ImGuiDataType_Float, &AimControl::AimFovSnipers, &FovMin, &FovMax, "%.1f", ImGuiSliderFlags_None);

						Gui.SliderScalarEx1(lang.aimbot_smooth.c_str(), ImGuiDataType_Float, &AimControl::SmoothSnipers, &SmoothMin, &SmoothMax, "%.1f", ImGuiSliderFlags_None);


						if (ImGui::Combo(lang.aimbot_possn.c_str(), &MenuConfig::AimPositionSniper, lang.aimbot_posselect, IM_ARRAYSIZE(lang.aimbot_posselect)))
						{
							switch (MenuConfig::AimPositionSniper)
							{
							case 0:
								MenuConfig::AimPositionIndexSniper = BONEINDEX::head;
								break;
							case 1:
								MenuConfig::AimPositionIndexSniper = BONEINDEX::neck_0;
								break;
							case 2:
								MenuConfig::AimPositionIndexSniper = BONEINDEX::spine_1;
								break;
							default:
								break;
							}
						}
					}
					else if (active_sub_tab == 3) { // shotguns
						Gui.SliderScalarEx1(lang.aimbot_fov.c_str(), ImGuiDataType_Float, &AimControl::AimFovShotguns, &FovMin, &FovMax, "%.1f", ImGuiSliderFlags_None);

						Gui.SliderScalarEx1(lang.aimbot_smooth.c_str(), ImGuiDataType_Float, &AimControl::SmoothShotguns, &SmoothMin, &SmoothMax, "%.1f", ImGuiSliderFlags_None);


						if (ImGui::Combo(lang.aimbot_posshotguns.c_str(), &MenuConfig::AimPositionShotguns, lang.aimbot_posselect, IM_ARRAYSIZE(lang.aimbot_posselect)))
						{
							switch (MenuConfig::AimPositionShotguns)
							{
							case 0:
								MenuConfig::AimPositionIndexShotGuns = BONEINDEX::head;
								break;
							case 1:
								MenuConfig::AimPositionIndexShotGuns = BONEINDEX::neck_0;
								break;
							case 2:
								MenuConfig::AimPositionIndexShotGuns = BONEINDEX::spine_1;
								break;
							default:
								break;
							}
						}
					}
					else if (active_sub_tab == 4) { // other
						Gui.SliderScalarEx1(lang.aimbot_fov.c_str(), ImGuiDataType_Float, &AimControl::AimFov, &FovMin, &FovMax, "%.1f", ImGuiSliderFlags_None);

						Gui.SliderScalarEx1(lang.aimbot_smooth.c_str(), ImGuiDataType_Float, &AimControl::Smooth, &SmoothMin, &SmoothMax, "%.1f", ImGuiSliderFlags_None);
						if (ImGui::Combo(lang.aimbot_posdef.c_str(), &MenuConfig::AimPosition, lang.aimbot_posselect, IM_ARRAYSIZE(lang.aimbot_posselect)))
						{
							switch (MenuConfig::AimPosition)
							{
							case 0:
								MenuConfig::AimPositionIndex = BONEINDEX::head;
								break;
							case 1:
								MenuConfig::AimPositionIndex = BONEINDEX::neck_0;
								break;
							case 2:
								MenuConfig::AimPositionIndex = BONEINDEX::spine_1;
								break;
							default:
								break;
							}
						}
					}

					ImGui::Separator();
				}
			}
			else if (active_tab == 1) { // TriggerBot
				Gui.MyCheckBox(lang.trigger_enable.c_str(), &MenuConfig::TriggerBot);
				if (MenuConfig::TriggerBot) {
					DWORD TriggerDelayMin = 0, TriggerDelayMax = 250;
					Gui.SliderScalarEx1(lang.trigger_delay.c_str(), ImGuiDataType_U32, &TriggerBot::TriggerDelay, &TriggerDelayMin, &TriggerDelayMax, "%d", ImGuiSliderFlags_None);
					if (ImGui::Combo(lang.trigger_hotkey.c_str(), &MenuConfig::TriggerHotKey, lang.trigger_hotkeyselect, IM_ARRAYSIZE(lang.trigger_hotkeyselect)))
					{
						TriggerBot::SetHotKey(MenuConfig::TriggerHotKey);
					}
					if (ImGui::Combo(lang.trigger_mode.c_str(), &MenuConfig::TriggerMode, lang.trigger_onkeyselect, IM_ARRAYSIZE(lang.trigger_onkeyselect)))
					{
						TriggerBot::SetMode(MenuConfig::TriggerMode);
					}
				}
			}
			else if (active_tab == 2) { // Visuals
				Gui.MyCheckBox(lang.visuals_showbox.c_str(), &MenuConfig::ShowBoxESP);
				//ImGui::SameLine();
				if (MenuConfig::ShowBoxESP) {
					ImGui::SameLine();
					ImGui::ColorEdit4(lang.visuals_boxcolor.c_str(), reinterpret_cast<float*>(&MenuConfig::BoxColor), ImGuiColorEditFlags_NoInputs);
					ImGui::Combo(lang.visuals_boxtype.c_str(), &MenuConfig::BoxType, lang.visuals_boxtypeselect, IM_ARRAYSIZE(lang.visuals_boxtypeselect));
				}
				ImGui::Separator();
				Gui.MyCheckBox(lang.visuals_showbone.c_str(), &MenuConfig::ShowBoneESP);
				if (MenuConfig::ShowBoneESP) {
					ImGui::SameLine();
					ImGui::ColorEdit4(lang.visuals_bonecolor.c_str(), reinterpret_cast<float*>(&MenuConfig::BoneColor), ImGuiColorEditFlags_NoInputs);
					Gui.MyCheckBox(lang.visuals_showeyeray.c_str(), &MenuConfig::ShowEyeRay);
					if (MenuConfig::ShowEyeRay) {
						ImGui::SameLine();
						ImGui::ColorEdit4(lang.visuals_eyeraycolor.c_str(), reinterpret_cast<float*>(&MenuConfig::EyeRayColor), ImGuiColorEditFlags_NoInputs);
					}
				}
				ImGui::Separator();
				Gui.MyCheckBox(lang.visuals_showbar.c_str(), &MenuConfig::ShowHealthBar);
				if (MenuConfig::ShowHealthBar) {
					ImGui::Combo(lang.visuals_barpos.c_str(), &MenuConfig::HealthBarType, lang.visuals_heathbarselect, IM_ARRAYSIZE(lang.visuals_heathbarselect));
				}
				ImGui::Separator();

				Gui.MyCheckBox(lang.visuals_weaponesp.c_str(), &MenuConfig::ShowWeaponESP);
				ImGui::SameLine();
				Gui.MyCheckBox(lang.visuals_distance.c_str(), &MenuConfig::ShowDistance);
				ImGui::SameLine();
				Gui.MyCheckBox(lang.visuals_name.c_str(), &MenuConfig::ShowPlayerName);
				ImGui::Separator();

				Gui.MyCheckBox(lang.visuals_line.c_str(), &MenuConfig::ShowLineToEnemy);
				if (MenuConfig::ShowLineToEnemy) {
					ImGui::SameLine();
					ImGui::ColorEdit4(lang.visuals_linecolor.c_str(), reinterpret_cast<float*>(&MenuConfig::LineToEnemyColor), ImGuiColorEditFlags_NoInputs);
				}
			}
			else if (active_tab == 3) { // Radar
				Gui.MyCheckBox(lang.radar_showradar.c_str(), &MenuConfig::ShowRadar);
				ImGui::SameLine();
				if (ImGui::Combo(lang.radar_radarsize.c_str(), &MenuConfig::RadarType, lang.radar_sizeselect, IM_ARRAYSIZE(lang.radar_sizeselect))) {
					switch (MenuConfig::RadarType)
					{
					case 0:
						mp::CircleSize = 2; mp::LineLenght = 6; mp::RadarSize = 300;
						break;
					case 1:
						mp::CircleSize = 5; mp::LineLenght = 10; mp::RadarSize = 600;
						break;
					default:
						break;
					}
				}
			}
			else if (active_tab == 4) { // Settings
				Gui.MyCheckBox(lang.utilities_teamcheck.c_str(), &MenuConfig::TeamCheck);

				static bool buffer1 = false;
				static bool buffer2 = false;
				ImGui::Separator();


				if (ImGui::Checkbox(lang.utilities_closehack.c_str(), &buffer1)) {
					TerminateProcess(GetCurrentProcess(), 0);
				}
				ImGui::Separator();
				if (ImGui::Checkbox(lang.utilities_reloadhack.c_str(), &buffer2)) {
					ProcessMgr.RefindGame();
					gGame.InitAddress();
					buffer2 = false;
				}
				if (ImGui::InputInt(lang.frames.c_str(), &MenuConfig::MaxFrameRate)) {
					if (MenuConfig::MaxFrameRate) Gui.delayticks = (1000000 / MenuConfig::MaxFrameRate) - 5000;
					else Gui.delayticks = 0;
				}
			}
			else if (active_tab == 5) { // Config
				ConfigMenu::RenderConfigMenu();
			}
		}
		ImGui::EndChild();
	}
	ImGui::End();
}
