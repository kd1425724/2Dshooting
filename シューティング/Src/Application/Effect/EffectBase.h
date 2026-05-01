#pragma once

class C_EffectBase
{
public:
	C_EffectBase(){}

	virtual ~C_EffectBase() {}

	// 基本処理
	virtual void Init(Math::Vector2 pos) { m_pos = pos; }
	virtual void Update() {}
	virtual void Draw() {}

	// 生存フラグ（Managerで削除判断に使う）
	bool GetAlive() const { return m_alive; }
	void Kill() { m_alive = false; }

	// 位置取得
	Math::Vector2 GetPos() const { return m_pos; }

	//画像セット
	void SetTexture(std::shared_ptr<KdTexture> tex) { m_tex = tex; }

protected:
	bool m_alive;

	Math::Vector2 m_pos;
	float m_scale;
	float m_angle;
	Math::Vector2 m_rect;
	float m_alpha;

	std::weak_ptr<KdTexture> m_tex;

	Math::Matrix m_scalemat;
	Math::Matrix m_rotmat;
	Math::Matrix m_transmat;
	Math::Matrix m_mat;
};