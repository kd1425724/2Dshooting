#pragma once
#include "Application/Skill/SkillBase.h"

class C_HitManager;

enum class Flashing
{
    Up,
    Down
};

class C_Barrier : public C_SkillBase, public std::enable_shared_from_this<C_Barrier>
{
public:
    C_Barrier();
    ~C_Barrier() override { Release(); }

    void Init() override;
    void Update() override;
    void Draw() override;

    void SkillActivate() override;
    void EnemySkillActivate(Math::Vector2 scale) override;

    void SetTexture(std::shared_ptr<KdTexture> tex);
    void SetEnemy(std::shared_ptr<C_EnemyMoveBase> enemybase) override
    {
        m_enemy = enemybase;
    }

    DrawType IsDrawType() override { return DrawType::TopDraw; }

    void SetHitManager(std::shared_ptr<C_HitManager> hitmanager) override
    {
        m_hitmanager = hitmanager;
    }

private:

	void Release() override;

    // ===== äÓñ{èÛë‘ =====
    static const int MaxTime = 300;
    int m_time = 0;

    // ===== ï`âÊ =====
    std::weak_ptr<KdTexture> m_tex;

    Math::Vector2 m_rect = { 0,0 };
    Math::Color m_color = {};

    Math::Matrix m_mat = Math::Matrix::Identity;

    Math::Vector2 m_scale = { 1.0f, 1.0f };

    // ===== ââèo =====
    float m_rot = 0.0f;
    Math::Vector2 m_dir = { 0,0 };
    float m_alpha = 1.0f;

    static const int AnimMaxNum = 6;
    float m_anim = 0.0f;

    Flashing m_flashing = Flashing::Up;

    std::weak_ptr<C_EnemyMoveBase> m_enemy;
    std::weak_ptr<C_HitManager> m_hitmanager;
};