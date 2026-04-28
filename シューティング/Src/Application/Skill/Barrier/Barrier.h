#pragma once
#include "Application/Skill/SkillBase.h"

enum class Flashing
{
    Up,
    Down
};

class C_Barrier : public C_SkillBase
{
public:
    C_Barrier();
    ~C_Barrier()override;

    void Init() override;
    void Update() override;
    void Draw() override;

    void SkillActivate() override;
    void EnemySkillActivate() override;

    void SetTexture(std::shared_ptr<KdTexture> tex);

    void SetEnemy(std::shared_ptr<C_EnemyMoveBase> enemybase) override{ m_enemy = enemybase; }

    bool IsTopDraw()override { return true; }

private:

    // à íu
    Math::Vector2 m_pos;

    // ï`âÊ
    std::shared_ptr<KdTexture> m_tex;
    Math::Vector2 m_rect;
    Math::Color m_color;

    Math::Matrix m_mat;

    Math::Vector2 m_scale;

    // ââèo
    float m_rot;
    Math::Vector2 m_dir;
    float m_alpha;

    static const int AnimMaxNum = 6;
    float m_anim;

    bool m_isActive;

    Flashing m_flashing;

    std::shared_ptr<C_EnemyMoveBase> m_enemy;
};