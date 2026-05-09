#pragma once
#include "Application/Enemy/Boss/BossBase.h"

enum class SubBossActionPattern
{
    None,
    p1_Laser,
    p2_Barrier,
    SubBossActionPatternNum
};

class C_SubBoss : public C_BossBase, public std::enable_shared_from_this<C_SubBoss>
{
public:
    C_SubBoss() {}
    ~C_SubBoss() { Release(); }

    void Init(Math::Vector2 pos) override;
    void Update() override;
    void Draw() override;

    void SetId(int id) { m_id = id; }
    int GetId() { return m_id; }

private:
    int m_id = 0;

    void Release() override;

    // ===== 状態管理 =====
    static const int NoneTime = 60;
    int m_nonetime = 0;

    Pattern m_pattern = Pattern::Start;

    SubBossActionPattern m_actionpattern = SubBossActionPattern::None;
    SubBossActionPattern m_nextactionpattern = SubBossActionPattern::None;

    Math::Vector2 m_stoppos = { 0, 0 };

    float m_texangle = 0.0f;

    KdTexture tex;

    // ===== 行動時間 =====
    static const int LaserTime = 300;
    int m_lasertime = 0;
    int m_laserprogresstime = 0;
    bool m_laserflg = false;

    static const int BarrierTime = 300;
    int m_barriertime = 0;

    // ===== 状態遷移 =====
    void StartUpdate();
    void StartDraw();
    void LoopUpdate();
    void LoopDraw();
    void DeathUpdate();
    void DeathDraw();

    // ===== 行動初期化 =====
    void NoneInit(SubBossActionPattern pattern);
    void p1_LaserInit();
    void p2_BarrierInit();

    // ===== 行動更新 =====
    void NoneUpdate();
    void p1_LaserUpdate();
    void p2_BarrierUpdate();

    // ===== 描画 =====
    void p1_LaserDrawSprite();
    void p2_BarrierDrawSprite();

    // ===== パターン制御 =====
    void SetActionPattern(SubBossActionPattern pattern);
    SubBossActionPattern GetRandomPatternExclude(SubBossActionPattern exclude);
};