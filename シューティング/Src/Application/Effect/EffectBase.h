#pragma once

class C_EffectBase
{
public:
    C_EffectBase() {}

    virtual ~C_EffectBase() {}

    // 基本処理
    virtual void Init(Math::Vector2 pos) {}
    virtual void Init(Math::Vector2 pos, Math::Vector2 scale, int time) {}
    virtual void Update() {}
    virtual void Draw() {}

    // ===== 生存管理 =====
    bool GetAlive() const { return m_alive; }
    void Kill() { m_alive = false; }

    // ===== 位置 =====
    Math::Vector2 GetPos() const { return m_pos; }

    // ===== テクスチャ =====
    void SetTexture(std::shared_ptr<KdTexture> tex) { m_tex = tex; }

protected:
    bool m_alive = false;

    Math::Vector2 m_pos = { 0, 0 };
    float m_scale = 1.0f;
    float m_angle = 0.0f;
    Math::Vector2 m_rect = { 0, 0 };
    float m_alpha = 1.0f;

    std::weak_ptr<KdTexture> m_tex;

    Math::Matrix m_scalemat = Math::Matrix::Identity;
    Math::Matrix m_rotmat = Math::Matrix::Identity;
    Math::Matrix m_transmat = Math::Matrix::Identity;
    Math::Matrix m_mat = Math::Matrix::Identity;
};