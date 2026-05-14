#pragma once
#include "Application/Skill/SkillBase.h"

class C_EnemyMoveBase;

enum LaserPattern
{
    Time,
    ShotLa,
    Upd
};

class C_Laser : public C_SkillBase, public std::enable_shared_from_this<C_Laser>
{
public:
    C_Laser();
	~C_Laser() override { Release(); }

    void Init() override;
    void Update() override;
    void Draw() override;

    void SkillActivate() override;
    void EnemySkillActivate() override;

    void SetEnemy(std::shared_ptr<C_EnemyMoveBase> enemybase) override
    {
        m_enemy = enemybase;
    }

    void SetTexture(std::shared_ptr<KdTexture> tex) override
    {
        m_tex = tex;
    }

    DrawType IsDrawType() override { return DrawType::MidDraw; }

    float GetThick() { return m_thick; }
    Math::Vector2 GetStart() { return m_start; }
    Math::Vector2 GetEnd() { return m_end; }

    void SetHitManager(std::shared_ptr<C_HitManager> hitmanager)
    {
        m_hitmanager = hitmanager;
    }

private:

	void Release() override;

    // ===== 基本情報 =====
    Math::Vector2 m_start = { 0,0 };
    Math::Vector2 m_end = { 0,0 };
    Math::Vector2 m_dir = { 0,0 };

    float m_length = 0.0f;
    float m_maxLength = 0.0f;
    float m_growSpeed = 0.0f;

    float m_segmentHeight = 0.0f;
    int   m_drawCount = 0;
    float m_thick = 0.0f;

    // ===== 描画 =====
    std::shared_ptr<KdTexture> m_tex = nullptr;
    Math::Vector2 m_rect = { 18, 38 };
    Math::Color m_color = {};

    Math::Vector2 m_scale = { 1.0f, 1.0f };
    Math::Matrix m_scalemat = Math::Matrix::Identity;
    Math::Matrix m_mat = Math::Matrix::Identity;

    // 疑似スクロール
    static const int TexNum = 2000 / 38;
    float m_anim[TexNum] = {};
    static const int m_animmaxnum = 4;

    // ===== 状態 =====
    static const int LaunshTime = 120;
    int m_launchtime = 0;

    std::weak_ptr<C_EnemyMoveBase> m_enemy;
    std::weak_ptr<C_HitManager> m_hitmanager;

    int m_warningtime = 0;

    LaserPattern m_pattern = Time;

    void P_Active();
    void E_Active();
};