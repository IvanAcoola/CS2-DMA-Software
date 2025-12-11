#pragma once
#include <string>

class Language {
public:
	std::string tab_visuals;
	std::string tab_aimbot;
	std::string tab_radar;
	std::string tab_trigger;
	std::string tab_settings;
	std::string tab_config;

	std::string visuals_showbox;
	std::string visuals_boxcolor;
	std::string visuals_boxtype;
	std::string visuals_showbone;
	std::string visuals_bonecolor;
	std::string visuals_showeyeray;
	std::string visuals_eyeraycolor;
	std::string visuals_showbar;
	std::string visuals_barpos;
	std::string visuals_weaponesp;
	std::string visuals_distance;
	std::string visuals_name;
	std::string visuals_line;
	std::string visuals_linecolor;

	std::string aimbot_enable;
	std::string aimbot_hotkey;
	std::string aimbot_fov;
	std::string aimbot_showaimfov;
	std::string aimbot_aimfovcolor;
	std::string aimbot_smooth;

	std::string aimbot_posrifles;
	std::string aimbot_pospis;
	std::string aimbot_possn;
	std::string aimbot_posshotguns;
	std::string aimbot_posdef;
	std::string aimbot_recolcontrol;

	std::string aimbot_autoshot;
	std::string aimbot_visiblecheck;
	std::string aimbot_ignoreonshot;
	std::string aimbot_customweapon;
	std::string aimbot_customsmooth;

	std::string aimbot_pistols;
	std::string aimbot_rifles;
	std::string aimbot_snipers;
	std::string aimbot_shotguns;
	std::string aimbot_other;

	std::string radar_showradar;
	std::string radar_enableweb;
	std::string radar_radarsize;
	std::string radar_euserver;

	std::string trigger_enable;
	std::string trigger_hotkey;
	std::string trigger_mode;
	std::string trigger_delay;

	std::string utilities_teamcheck;
	std::string utilities_closehack;
	std::string utilities_reloadhack;
	std::string utilities_language;

	std::string config_newconfig;
	std::string config_create;
	std::string config_load;
	std::string config_save;
	std::string config_delete;

	const char* visuals_boxtypeselect[2];
	const char* visuals_heathbarselect[2];

	const char* aimbot_hotkeyselect[8] = { "LBUTTON", "MENU", "RBUTTON", "XBUTTON1", "XBUTTON2", "CAPITAL", "SHIFT", "CONTROL" };
	const char* aimbot_posselect[3];

	const char* radar_sizeselect[2];

	const char* trigger_hotkeyselect[7] = { "MENU", "RBUTTON", "XBUTTON1", "XBUTTON2", "CAPITAL", "SHIFT", "CONTROL" };
	const char* trigger_onkeyselect[2];

	const char* utilities_langselect[2] = { "English", u8"中文" };

	std::string days;

	std::string frames;


	void english() {
		this->tab_visuals = "Visuals";
		this->tab_aimbot = "Aimbot";
		this->tab_radar = "Radar";
		this->tab_trigger = "TriggerBot";
		this->tab_settings = "Settings";
		this->tab_config = "Config";

		this->visuals_showbox = "Show Box";
		this->visuals_boxcolor = "Box Color";
		this->visuals_boxtype = "Box Type";
		this->visuals_barpos = "Health Bar Position";
		this->visuals_showbone = "Bones";
		this->visuals_bonecolor = "Bones Color";
		this->visuals_showeyeray = "Eye Ray";
		this->visuals_eyeraycolor = "Eye Ray Color";
		this->visuals_showbar = "Health Bar";
		this->visuals_weaponesp = "Weapon";
		this->visuals_distance = "Distance";
		this->visuals_name = "Name";
		this->visuals_line = "Lines to Player";
		this->visuals_linecolor = "Lines color";

		this->aimbot_enable = "Enable";
		this->aimbot_hotkey = "Aimbot Hotkey";
		this->aimbot_fov = "fov";
		this->aimbot_showaimfov = "Show AimFov";
		this->aimbot_aimfovcolor = "Aimfov Color";
		this->aimbot_smooth = "Smooth";
		this->aimbot_recolcontrol = "Recoil Control";

		this->aimbot_posdef = "Aim Target / Default";
		this->aimbot_pospis = "Aim Target / Pistols";
		this->aimbot_possn = "Aim Target / Snipers";
		this->aimbot_posrifles = "Aim Target / Rifles";
		this->aimbot_posshotguns = "Aim Target / Shotguns";

		this->aimbot_pistols = "Pistols";
		this->aimbot_rifles = "Rifles";
		this->aimbot_snipers = "Snipers";
		this->aimbot_shotguns = "Shotguns";
		this->aimbot_other = "Other";

		this->aimbot_autoshot = "AutoShot";
		this->aimbot_visiblecheck = "Visible Check";
		this->aimbot_ignoreonshot = "IgnoreOnShot";
		this->aimbot_customweapon = "Custom Settings";
		this->aimbot_customsmooth = "Gun Smooth";

		this->radar_showradar = "Show Radar";
		this->radar_enableweb = "Enable Web Radar";
		this->radar_radarsize = "Radar Size";
		this->radar_euserver = "Web / EU Server";

		this->trigger_enable = "Enable";
		this->trigger_hotkey = "Trigger Hotkey";
		this->trigger_mode = "Trigger Mode";
		this->trigger_delay = "Delay";

		this->utilities_teamcheck = "Team Check";
		this->utilities_closehack = "Close Software";
		this->utilities_reloadhack = "Reload game";
		this->utilities_language = "Select Language";

		this->config_newconfig = "Config Name";
		this->config_create = "Create config";
		this->config_load = "Load";
		this->config_save = "Save";
		this->config_delete = "Delete";

		this->visuals_boxtypeselect[0] = "Normal"; this->visuals_boxtypeselect[1] = "Slim";
		this->visuals_heathbarselect[0] = "Left"; this->visuals_heathbarselect[1] = "Up";

		this->aimbot_posselect[0] = "Head"; this->aimbot_posselect[1] = "Neck"; this->aimbot_posselect[2] = "Spine";
		this->radar_sizeselect[0] = "Small"; this->radar_sizeselect[1] = "Big";

		this->trigger_onkeyselect[0] = "OnKey"; this->trigger_onkeyselect[1] = "Always";

		this->days = "days";

		this->frames = "Frames";
	}

	void chineese() {
		this->tab_visuals = u8"视觉";
		this->tab_aimbot = u8"自瞄";
		this->tab_radar = u8"雷达";
		this->tab_trigger = u8"自动扳机";
		this->tab_settings = u8"设置";
		this->tab_config = u8"配置";

		this->visuals_showbox = u8"显示透视框";
		this->visuals_boxcolor = u8"框颜色";
		this->visuals_boxtype = u8"框类型";
		this->visuals_barpos = u8"生命条位置";
		this->visuals_showbone = u8"显示骨骼";
		this->visuals_bonecolor = u8"骨骼颜色";
		this->visuals_showeyeray = u8"显示视线";
		this->visuals_eyeraycolor = u8"视线颜色";
		this->visuals_showbar = u8"显示生命条";
		this->visuals_weaponesp = u8"显示武器";
		this->visuals_distance = u8"显示距离";
		this->visuals_name = u8"显示名称";
		this->visuals_line = u8"显示指向玩家的线";
		this->visuals_linecolor = u8"线颜色";

		this->aimbot_enable = u8"启用";
		this->aimbot_hotkey = u8"自瞄热键";
		this->aimbot_fov = u8"自瞄范围";
		this->aimbot_showaimfov = u8"显示自瞄范围";
		this->aimbot_aimfovcolor = u8"自瞄范围颜色";
		this->aimbot_smooth = u8"平滑度";
		this->aimbot_recolcontrol = u8"后坐力控制";

		this->aimbot_posdef = u8"瞄准目标 / 默认";
		this->aimbot_pospis = u8"瞄准目标 / 手枪";
		this->aimbot_possn = u8"瞄准目标 / 狙击";
		this->aimbot_posrifles = u8"瞄准目标 / 步枪";
		this->aimbot_posshotguns = u8"瞄准目标 / 霰弹枪";

		this->aimbot_autoshot = u8"自动射击";
		this->aimbot_visiblecheck = u8"可见性检查";
		this->aimbot_ignoreonshot = u8"忽略开火";
		this->aimbot_customweapon = u8"自定义设置";
		this->aimbot_customsmooth = u8"顺滑度";

		this->aimbot_pistols = u8"手枪";
		this->aimbot_rifles = u8"步枪";
		this->aimbot_snipers = u8"狙击枪";
		this->aimbot_shotguns = u8"霰弹枪";
		this->aimbot_other = u8"全局";

		this->radar_showradar = u8"显示雷达";
		this->radar_enableweb = u8"启用网络雷达";
		this->radar_radarsize = u8"雷达大小";
		this->radar_euserver = u8"网页/欧洲服务器";


		this->trigger_enable = u8"自动扳机启用";
		this->trigger_hotkey = u8"自动扳机热键";
		this->trigger_mode = u8"自动扳机模式";
		this->trigger_delay = u8"延迟";

		this->utilities_teamcheck = u8"队伍检查";
		this->utilities_closehack = u8"关闭软件";
		this->utilities_language = u8"选择语言";
		this->utilities_reloadhack = u8"重新获取数据";

		this->config_newconfig = u8"配置名称";
		this->config_create = u8"创建配置";
		this->config_load = u8"加载";
		this->config_save = u8"保存";
		this->config_delete = u8"删除";

		this->visuals_boxtypeselect[0] = u8"普通"; this->visuals_boxtypeselect[1] = u8"窄";
		this->visuals_heathbarselect[0] = u8"左侧"; this->visuals_heathbarselect[1] = u8"上侧";

		this->aimbot_posselect[0] = u8"头"; this->aimbot_posselect[1] = u8"脖子"; this->aimbot_posselect[2] = u8"胸";
		this->radar_sizeselect[0] = u8"小的"; this->radar_sizeselect[1] = u8"大的";

		this->trigger_onkeyselect[0] = u8"当按下时"; this->trigger_onkeyselect[1] = u8"总是";

		this->days = u8"剩余天数";

		this->frames = u8"框";
	}
};

inline Language lang;