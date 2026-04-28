#pragma once

enum class HitType
{
	Player,
	Enemy,
	SubBoss,
	Boss,
	PlayerShot,
	EnemyShot,
	BossShot,
	S_PlayerBarrier,
	S_EnemyBarrier,
	S_PlayerLaser,
	S_EnemyLaser,
	HitTypeNum
};


class C_HitBase
{
public:
	C_HitBase();
	virtual ~C_HitBase();

	virtual void Init();
	virtual void Update();

	// “–‚½‚è”»’è
	bool IsHit(const C_HitBase& other) const;

	virtual void OnHit(C_HitBase* other){}

	// Getter / Setter
	void SetPos(const Math::Vector2& pos) { m_pos = pos; }
	void SetRadius(float r) { m_radius = r; }

	const Math::Vector2& GetPos() const { return m_pos; }
	float GetRadius() const { return m_radius; }

	HitType GetType() const { return m_type; }
	void SetType(HitType type) { m_type = type; }

private:
	HitType m_type;

	Math::Vector2 m_pos;
	float m_radius;

};