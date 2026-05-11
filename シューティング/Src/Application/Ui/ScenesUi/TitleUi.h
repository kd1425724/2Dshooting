#pragma once
#include "Application/Ui/ScenesUi/ScenesUiBase.h"

enum TitleButton
{
    START, // スタートボタン
};

class C_Player;

class C_TitleUi : public C_ScenesUiBase
{
public:
    C_TitleUi() {}
    ~C_TitleUi() override { Release(); }

    void Init() override;
    void Update() override;
    void Draw() override;

    // スタートテクスチャセット
    void SetStartTex(std::shared_ptr<KdTexture> tex)
    {
        m_starttex = tex;
    }

    // 背景
    void BackGroundInit() override;
    void BackGroundUpdate() override;
    void BackGroundDraw() override;

private:
    void Release() override;

    //背景
    KdTexture m_movebackgroundtex;
    Math::Vector2 m_movebackgroundpos = {};
    Math::Vector2 m_movebackgroundpos2 = {};

    Math::Rectangle m_movebackgroundrect = {};

    Math::Matrix m_movebackgroundmat = {};
    Math::Matrix m_movebackgroundmat2 = {};

    // ===== スタート =====
    void StartInit();
    void StartUpdate();
    void StartDraw();

    enum class StartAlphaPattern
    {
        None,
        Up,
        Down
    };

    Math::Vector2 m_startpos = { 0, 0 };
    std::shared_ptr<KdTexture> m_starttex = nullptr;
    float m_startalpha = 1.0f;
    Math::Vector2 m_startscale = { 1.0f, 1.0f };

    StartAlphaPattern m_startalphapattern = StartAlphaPattern::None;

    // ===== タイトルロゴ =====
    void TitleLogoInit();
    void TitleLogoDraw();

    KdTexture m_titlelogotex;

    // ===== プレイヤー =====
    void PlayerInit();
    void PlayerUpdate();
    void PlayerDraw();

    std::shared_ptr<C_Player> m_player = nullptr;
    std::vector<std::shared_ptr<KdTexture>> m_playerenginetexs;
};