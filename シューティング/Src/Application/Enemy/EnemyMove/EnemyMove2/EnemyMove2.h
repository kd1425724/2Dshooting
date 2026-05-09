#pragma once
#include "Application/Enemy/EnemyMoveBase.h"

enum class InherentMove2
{
    Start,
    Stop,
    Shot,
    Stop2,
    ReStart,
};

class C_EnemyMove2 : public C_EnemyMoveBase, public std::enable_shared_from_this<C_EnemyMove2>
{
public:
    C_EnemyMove2() {}
    ~C_EnemyMove2() override { Release(); }

    void Init(PosPattern pospattern, MovePattern movepattern, std::shared_ptr<C_Player> player, int i) override;
    void Update() override;
    void Draw() override;

    // ボス用なので使わない
    void Init() override {}

private:
    void Release() override;

    // ===== 固有行動 =====
    InherentMove2 m_inherentmove = InherentMove2::Start;

    // ===== ストップ制御 =====
    static const int m_stopcountmax = 1 * 60;
    int m_stopcount = 0;

    // ===== 発射関連 =====
    Math::Vector2 m_shotpos = { 0, 0 };
    float m_shotangle = 0.0f;
};