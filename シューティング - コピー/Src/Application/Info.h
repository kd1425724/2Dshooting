#pragma once

class C_Info
{
public:
   
    // ===== 画面設定（定数） =====
    static const int ScrWidth = 1280;
    static const int ScrHeight = 720;

    // HUDエリア
    static const int HUDAreaWidth = 1280;
    static const int HUDAreaHeight = 160;

    // プレイエリア
    static const int PlayAreaWidth = 1280;
    static const int PlayAreaTop = ScrHeight / 2 - HUDAreaHeight;
    static const int PlayAreaBottom = -ScrHeight / 2;

    // ===== プレイヤー情報（セーブデータ） =====
    void PlayerInfoLoad();
    void PlayerInfoSave();

    int PlayerHpEnhancement = 1;
    int PlayerPowerEnhancement = 5;
    int PlayerSpeedEnhancement = 2;

private:
    C_Info() {}
    ~C_Info() {}

public:
    static C_Info& GetInstans()
    {
        static C_Info instans;
        return instans;
    }
};

#define INFO C_Info::GetInstans()