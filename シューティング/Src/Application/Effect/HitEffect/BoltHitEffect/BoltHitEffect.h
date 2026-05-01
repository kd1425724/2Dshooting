#pragma once
#include "../../EffectBase.h"

class C_BoltHitEffect : public C_EffectBase
{
public:
	C_BoltHitEffect() :
		m_timer(0),
		m_lifetime(30) // 30ƒtƒŒ[ƒ€‚ÅÁ‚¦‚é
	{
	}

	~C_BoltHitEffect() {}

	void Init(Math::Vector2 pos) override;
	void Update() override;
	void Draw() override;

private:

	static const int AnimMax = 7;

	int m_timer;
	int m_lifetime;

	float m_anim;
};