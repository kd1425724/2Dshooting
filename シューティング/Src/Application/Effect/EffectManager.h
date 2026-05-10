#pragma once

class C_EffectBase;

enum class EffectType
{
    Explosion,
    ExplosionTopDraw,
    LaserStartGreen,
    LaserStartRed,
    BoltHitBlue,
    BoltHitGreen,
    CopyHit,
    WarningLine
};

class C_EffectManager
{
public:
    void Init();
    void Update();
    void Draw();

    void IsTopDraw();
    void IsBottomDraw();

    void Release();

    void AddEffect(
        EffectType type,
        Math::Vector2 pos={0,0},
        Math::Vector2 scale = { 1.0f, 1.0f },
        int time = 0);

    void ScoreEffect(int value);

    void SetScoreUpPos(Math::Vector2 pos) { m_scoreeffectpos = pos; }

private:
    // ===== エフェクト管理 =====
    std::vector<std::shared_ptr<C_EffectBase>> m_effects;
    std::vector<std::shared_ptr<C_EffectBase>> m_topdraweffects;
    std::vector<std::shared_ptr<C_EffectBase>> m_bottomdraweffects;

    std::vector<std::shared_ptr<C_EffectBase>> m_addeffects;
    std::vector<std::shared_ptr<C_EffectBase>> m_addtopdraweffects;
    std::vector<std::shared_ptr<C_EffectBase>> m_addbottomdraweffects;

    // ===== テクスチャ（全部nullptr初期化）=====
    std::shared_ptr<KdTexture> m_explosiontex = nullptr;

    std::shared_ptr<KdTexture> m_laserstartgreeneffecttex = nullptr;
    std::shared_ptr<KdTexture> m_laserstartredeffecttex = nullptr;

    std::shared_ptr<KdTexture> m_warninglinetex = nullptr;

    std::shared_ptr<KdTexture> m_boltbluehiteffecttex = nullptr;
    std::shared_ptr<KdTexture> m_boltgreenhiteffecttex = nullptr;
    std::shared_ptr<KdTexture> m_copyhiteffecttex = nullptr;

    Math::Vector2 m_scoreeffectpos = {};

private:
    C_EffectManager() {};
    ~C_EffectManager() { Release(); }

public:
    static C_EffectManager& GetInstance()
    {
        static C_EffectManager instance;
        return instance;
    }
};

#define EFFECTMANAGER C_EffectManager::GetInstance()