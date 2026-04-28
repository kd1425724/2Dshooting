#pragma once
#include "Application/Skill/SkillBase.h"

class C_EnemyMoveBase;

class C_Laser : public C_SkillBase
{
public:
    C_Laser();
    ~C_Laser()override;

    void Init() override;
    void Update() override;
    void Draw() override;

    void SkillActivate() override;
    void EnemySkillActivate() override;

    void SetEnemy(std::shared_ptr<C_EnemyMoveBase> enemybase) override { m_enemy = enemybase; }

    void SetTexture(std::shared_ptr<KdTexture> tex)override { m_tex = tex; }

    bool IsTopDraw()override { return false; }

private:

    // ===== 基本情報 =====
    Math::Vector2 m_start;     // 発射位置
    Math::Vector2 m_dir;       // 方向（正規化して使う）

    float m_length;            // 現在の長さ
    float m_maxLength;         // 最大長さ
    float m_growSpeed;         // 伸びる速度

    float m_segmentHeight;     // 1タイルの高さ
    int   m_drawCount;         // 描画枚数

    // ===== 描画 =====
    std::shared_ptr<KdTexture> m_tex;                 // テクスチャ
    Math::Vector2 m_rect = { 18,38 };    // 描画サイズ
    Math::Color m_color;      // 色

    Math::Vector2 m_scale;
    Math::Matrix m_scalemat;
    Math::Matrix m_mat;       // 描画行列

    // 疑似スクロール用
    static const int TexNum = 2000 / 38;
    float m_anim[TexNum];
    static  const int m_animmaxnum = 4;

    // ===== 状態 =====
    bool m_isActive;

    static const int LaunshTime = 120;
    int m_launchtime;

    std::shared_ptr<C_EnemyMoveBase> m_enemy;
};