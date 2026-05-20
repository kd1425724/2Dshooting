#pragma once

class C_SkillManager;
class C_EnemyMoveBase;

class C_Game;
class C_Game2;

class C_HitManager;

class C_EffectBase
{
public:
    C_EffectBase() {}

    virtual ~C_EffectBase() { Release(); }

    // 基本処理
    virtual void Init(Math::Vector2 pos) {}
    virtual void Init(Math::Vector2 pos, Math::Vector2 scale, int time) {}
    virtual void Init(Math::Vector2 pos,int value) {}
    virtual void Init(Math::Vector2 pos, std::shared_ptr<C_SkillManager> skillmanager,std::shared_ptr<C_EnemyMoveBase> enemy){}
	virtual void Init(Math::Vector2 pos, Math::Color color) {}
    virtual void Update() {}
    virtual void Draw() {}

    // ===== 生存管理 =====
    bool GetAlive() const { return m_alive; }
    void Kill() { m_alive = false; }

    // ===== 位置 =====
    Math::Vector2 GetPos() const { return m_pos; }

    // ===== テクスチャ =====
    void SetTexture(std::shared_ptr<KdTexture> tex) { m_tex = tex; }

	// ===== オーナー =====
	void SetOwner(std::weak_ptr<C_Game> owner) { m_owner = owner; }
	void SetOwner(std::weak_ptr<C_Game2> owner) { m_owner2 = owner; }

	// ===== 当たり判定管理 =====
    void SetHitManager(std::shared_ptr<C_HitManager> hitmanager)
    {
        m_hitmanager = hitmanager;
	}

protected:

    //オーナー
	std::weak_ptr<C_Game> m_owner = {};
	std::weak_ptr<C_Game2> m_owner2 = {};

	std::weak_ptr<C_HitManager> m_hitmanager = {};
    std::weak_ptr<C_SkillManager> m_skillmanager = {};
    std::weak_ptr<C_EnemyMoveBase> m_enemy = {};

	virtual void Release() {}

    bool m_alive = false;

    Math::Vector2 m_pos = { 0, 0 };
    float m_scale = 1.0f;
    float m_angle = 0.0f;
    Math::Vector2 m_rect = { 0, 0 };
    float m_alpha = 1.0f;
	Math::Color m_color = { 1,1,1,1 };

    std::weak_ptr<KdTexture> m_tex;

    Math::Matrix m_scalemat = Math::Matrix::Identity;
    Math::Matrix m_rotmat = Math::Matrix::Identity;
    Math::Matrix m_transmat = Math::Matrix::Identity;
    Math::Matrix m_mat = Math::Matrix::Identity;
};