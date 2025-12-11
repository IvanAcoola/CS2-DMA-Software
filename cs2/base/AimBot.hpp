#pragma once

#include "../KeysValues.h"

#include "../kmbox/KmBoxNetManager.h"
#include "../kmbox/kmboxNetPlusManager.cpp"
#include "../kmbox/KmboxB.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include "Game.h"
#include "Entity.h"
#include "TriggerBot.h"
#include <iostream>

extern "C" {
#include "Entity.h"
}


namespace AimControl
{
    inline int HotKey = VK_XBUTTON2;
    inline float AimFov = 6;

    inline float AimFovRifles = 6;
    inline float AimFovSnipers = 6;
    inline float AimFovPistols = 6;
    inline float AimFovShotguns = 6;

    inline float Smooth = 3.9;

    inline float SmoothShotguns = 3.9;
    inline float SmoothPistols = 3.9;
    inline float SmoothSnipers = 3.9;
    inline float SmoothRifles = 3.9;

    inline std::vector<int> HotKeyList{VK_LBUTTON, VK_LMENU, VK_RBUTTON, VK_XBUTTON1, VK_XBUTTON2, VK_CAPITAL, VK_LSHIFT, VK_LCONTROL};

    inline bool AutoShot = false;
    inline bool ignoreOnShot = true;

    inline bool HasTarget = false;

    inline bool RecoilControl = false;

    inline Vec2 RCSScale = { 1.f,1.f };


    inline void SetHotKey(int Index)
    {
        HotKey = HotKeyList.at(Index);
    }

    inline void UpdateAngles(const CEntity& Local, Vec2& Angles)
    {
        auto oldPunch = Vec2{ };
        auto shotsFired = Local.Pawn.ShotsFired;

        int ScreenCenterX = Gui.Window.Size.x / 2;
        int ScreenCenterY = Gui.Window.Size.y / 2;

        if (shotsFired)
        {
            uintptr_t clientState;
            auto viewAngles = Local.Pawn.ViewAngle;
            auto aimPunch = Local.Pawn.AimPunchAngle;

            auto newAngles = Vec2
            {
                viewAngles.x + oldPunch.x - aimPunch.x * 2.f,
                viewAngles.y + oldPunch.y - aimPunch.y * 2.f,
            };

            if (newAngles.x > 89.f)
                newAngles.x = 89.f;

            if (newAngles.x < -89.f)
                newAngles.x = -89.f;

            while (newAngles.y > 180.f)
                newAngles.y -= 360.f;

            while (newAngles.y < -180.f)
                newAngles.y += 360.f;

            newAngles.x += ScreenCenterX;
            newAngles.y += ScreenCenterY;
            Angles = newAngles;
            oldPunch = aimPunch;
        }
        else
        {
            oldPunch.x = oldPunch.y = 0.f;
        }

        if (true)
        {
            Vec2 PunchAngle;
            if (Local.Pawn.AimPunchCache.Count <= 0 && Local.Pawn.AimPunchCache.Count > 0xFFFF)
                return;
            if (!ProcessMgr.ReadMemory<Vec2>(Local.Pawn.AimPunchCache.Data + (Local.Pawn.AimPunchCache.Count - 1) * sizeof(Vec3), PunchAngle))
                return;

            Angles.x = PunchAngle.x;
            Angles.y = PunchAngle.y;
        }
    }

    inline void AimBot(const CEntity& Local, Vec3 LocalPos, Vec3 AimPos, int smoothType)
    {
        if (Local.Pawn.WeaponName == "knife") return;
        if (ignoreOnShot && Keys::LeftKey) return;

        float FinallySmooth = Smooth;
        float FinallyAimFov = AimFov;


        if (smoothType == 1) {
            FinallySmooth = SmoothRifles;
            FinallyAimFov = AimFovRifles;
        }
        else if (smoothType == 2) {
            FinallySmooth = SmoothSnipers;
            FinallyAimFov = AimFovSnipers;
        }
        else if (smoothType == 3) {
            FinallySmooth = SmoothPistols;
            FinallyAimFov = AimFovPistols;
        }
        else if (smoothType == 4) {
            FinallySmooth = SmoothShotguns;
            FinallyAimFov = AimFovShotguns;
        }

        float BestNorm = 10000e9;

        float Yaw, Pitch;
        float Distance, Norm, Length;
        Vec2 Angles{ 0,0 };
        int ScreenCenterX = Gui.Window.Size.x / 2;
        int ScreenCenterY = Gui.Window.Size.y / 2;
        float TargetX = 0.f;
        float TargetY = 0.f;

        Vec2 ScreenPos;

        Vec3 OppPos;

        OppPos = AimPos - LocalPos;

        Distance = sqrt(pow(OppPos.x, 2) + pow(OppPos.y, 2));

        Length = sqrt(Distance * Distance + OppPos.z * OppPos.z);

        if (RecoilControl)
        {
            UpdateAngles(Local, Angles);
            float rad = Angles.x * RCSScale.x / 360.f * M_PI;
            float si = sinf(rad);
            float co = cosf(rad);

            float z = OppPos.z * co + Distance * si;
            float d = (Distance * co - OppPos.z * si) / Distance;

            rad = -Angles.y * RCSScale.y / 360.f * M_PI;
            si = sinf(rad);
            co = cosf(rad);

            float x = (OppPos.x * co - OppPos.y * si) * d;
            float y = (OppPos.x * si + OppPos.y * co) * d;

            OppPos = Vec3{ x, y, z };

            AimPos = LocalPos + OppPos;
        }

        Yaw = atan2f(OppPos.y, OppPos.x) * 57.295779513 - Local.Pawn.ViewAngle.y;
        Pitch = -atan(OppPos.z / Distance) * 57.295779513 - Local.Pawn.ViewAngle.x;

        Norm = sqrt(pow(Yaw, 2) + pow(Pitch, 2));

        if (Norm < BestNorm)
            BestNorm = Norm;

        gGame.View.WorldToScreen(AimPos, ScreenPos);

        if (Norm < FinallyAimFov)
        {
            HasTarget = true;

            if (ScreenPos.x != ScreenCenterX)
            {
                TargetX = (ScreenPos.x > ScreenCenterX) ? -(ScreenCenterX - ScreenPos.x) : ScreenPos.x - ScreenCenterX;
                TargetX /= FinallySmooth != 0.0f ? FinallySmooth : 1.5f;
                TargetX = (TargetX + ScreenCenterX > ScreenCenterX * 2 || TargetX + ScreenCenterX < 0) ? 0 : TargetX;
            }

            if (ScreenPos.y != 0)
            {
                if (ScreenPos.y != ScreenCenterY)
                {
                    TargetY = (ScreenPos.y > ScreenCenterY) ? -(ScreenCenterY - ScreenPos.y) : ScreenPos.y - ScreenCenterY;
                    TargetY /= FinallySmooth != 0.0f ? FinallySmooth : 1.5f;
                    TargetY = (TargetY + ScreenCenterY > ScreenCenterY * 2 || TargetY + ScreenCenterY < 0) ? 0 : TargetY;
                }
            }

            float DistanceRatio = Norm / FinallyAimFov;
            float SpeedFactor = 1.0f + (1.0f - DistanceRatio);
            TargetX /= (FinallySmooth * SpeedFactor);
            TargetY /= (FinallySmooth * SpeedFactor);

            if (ScreenPos.x != ScreenCenterX)
            {
                TargetX = (ScreenPos.x > ScreenCenterX) ? -(ScreenCenterX - ScreenPos.x) : ScreenPos.x - ScreenCenterX;
                TargetX /= FinallySmooth != 0.0f ? FinallySmooth : 1.5f;
                TargetX = (TargetX + ScreenCenterX > ScreenCenterX * 2 || TargetX + ScreenCenterX < 0) ? 0 : TargetX;
            }

            if (ScreenPos.y != 0)
            {
                if (ScreenPos.y != ScreenCenterY)
                {
                    TargetY = (ScreenPos.y > ScreenCenterY) ? -(ScreenCenterY - ScreenPos.y) : ScreenPos.y - ScreenCenterY;
                    TargetY /= FinallySmooth != 0.0f ? FinallySmooth : 1.5f;
                    TargetY = (TargetY + ScreenCenterY > ScreenCenterY * 2 || TargetY + ScreenCenterY < 0) ? 0 : TargetY;
                }
            }

            if (KmBox::type == "net") KmBoxMgr.Mouse.Move(TargetX, TargetY);
            if (KmBox::type == "net2") kmboxnew::kmNet_mouse_move(TargetX, TargetY);
            if (KmBox::type == "b") kmBoxBMgr.km_move(TargetX, TargetY);

            if (AutoShot && TargetX <= 2 && TargetY <= 2) {
                if (KmBox::type == "net") {
                    KmBoxMgr.Mouse.Left(true);
                    Sleep(10);
                    KmBoxMgr.Mouse.Left(false);
                }
                else if (KmBox::type == "net2") {
                    kmboxnew::kmNet_mask_mouse_left(true);
                    Sleep(10);
                    kmboxnew::kmNet_mask_mouse_left(false);
                }
                else if (KmBox::type == "b") {
                    kmBoxBMgr.km_click();
                }
            }
        }
        else
            HasTarget = false;
    }
}