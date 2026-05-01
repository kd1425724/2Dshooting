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
    ~C_Barrier()override;

    void Init() override;
    void Update() override;
    void Draw() override;

    void SkillActivate() override;
    void EnemySkillActivate() override;

    void SetTexture(std::shared_ptr<KdTexture> tex);

    void SetEnemy(std::shared_ptr<C_EnemyMoveBase> enemybase) override{ m_enemy = enemybase; }

    bool IsTopDraw()override { return true; }

    void SetHitManager(std::shared_ptr<C_HitManager> hitmanager)override { m_hitmanager = hitmanager; }

private:

    //”­¶ŠÔ
    static const int MaxTime = 300;
    int m_time;

    // ˆÊ’u
    //Math::Vector2 m_pos;

    // •`‰æ
    std::weak_ptr<KdTexture> m_tex;
    Math::Vector2 m_rect;
    Math::Color m_color;

    Math::Matrix m_mat;

    Math::Vector2 m_scale;

    // ‰‰o
    float m_rot;
    Math::Vector2 m_dir;
    float m_alpha;

    static const int AnimMaxNum = 6;
    float m_anim;

    Flashing m_flashing;

    std::weak_ptr<C_EnemyMoveBase> m_enemy;

    //“–‚½‚è”»’è
    std::weak_ptr<C_HitManager> m_hitmanager;
};