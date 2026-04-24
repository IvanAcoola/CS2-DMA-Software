# CS2 DMA Cheat

Open source CS2 DMA Software. I m the author of most popular open source dma cheat (now its fork has 160+ stars.). Its 2.0 version with all fixed bugs, new features, all types of kmbox support.

In ReadMe you can find full installation & build guide. If you have any questions - you can ask them in contacts.

![C++](https://img.shields.io/badge/C%2B%2B-23-blue.svg)
![Visual Studio](https://img.shields.io/badge/IDE-Visual%20Studio-5C2D91?logo=visual-studio&logoColor=white)
![Ready to build](https://img.shields.io/badge/status-ready--to--build-brightgreen)

## ⚡ Installation

Firstly you need to download exe / build it from sources.

You need to put files in same 

- exe
- [offsets.json](https://github.com/a2x/cs2-dumper/blob/main/output/offsets.json)
- [client.dll.json](https://github.com/a2x/cs2-dumper/blob/main/output/client_dll.json)
- config
- FTD3XX.dll
- leechcore.dll
- vmm.dll

[VT - exe from release (you can compare hash)](https://www.virustotal.com/gui/file/6088ea757fe0bcbf4ee2b718a11f7ccddaa80dfef7ac39e90fa8a2376e94fa3d?nocache=1)


## 🔨 Building

```bash
  git clone https://github.com/IvanAcoola/CS2-DMA-Software.git
```

Open the project (slnx file) with visual studio (builded with VS2026). 
Ready-to-build on Release.

## 📄 Configuration

Example for net kmbox
```json
{
    "type": "net", 
    "en": "en",
    "ip": "192.168.2.198",
    "port": 12345,
    "uuid": "0000000"
}
```
Example for BPro
```json
{
   "type":"b",
   "en": "en"
}
```

Possible values for: 
* "en" - en / ch (English, Chinese)
* "type" - net / net+ (encrypted net-kmbox) / b (its BPro) / none (to use without kmbox)
    
## 🤖 Features

- **Visuals**
* ESP: Box, health bar, weapon, distance, name
* Eye ray
* Bones
* Lines to enemy
- **AimBot**
* Hotkey, Aimfov, Visual Check, Smooth, IgnoreOnShoot
* AutoShot
* Different settings for each weapon-type (rifles, pistols, snipers, shotguns, other). FOV & Smooth & AimTarget (bone) 
- **Radar**
* Size (small, big), map auto-selection
- **TriggerBot**
* Hotkey, mode (always, onkey), delay
- **Utilities**
* Team Check
- **Configs**
* Create, Save, Load, Delete
- **Languages**
* English 🇺🇸 & Chinese 🇨🇳 supported

## Screenshots

![](https://i.ibb.co/fdftpD9R/photo-5318998954227732201-w.jpg)


## ❔ FAQ

#### How to open & hide menu?

F8 on your main keyboard. All binds works only on main computer.

#### vmm.dll not found...

Check one more time installation guide. Do not forget to put needed dlls to same folder as .exe.

#### How can I support the project or say "thank you" to author?

Contact me on telegram



## ✉️ Contacts

 - [Telegram](https://t.me/cherepoveciv) - support on 🇺🇸 🇷🇺 🇮🇱
 - [GitHub](https://github.com/IvanAcoola)


## 🤝 Credits

- [@CS2_DMA_Extrnal](https://github.com/Mzzzj/CS2_DMA_Extrnal)
- [@KmBoxNet](https://github.com/TKazer/KmBoxNetManager)
- [@KmBoxB](https://github.com/sys-1337/kmbox-communication)

