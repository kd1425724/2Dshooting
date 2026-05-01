#pragma once
#include "../EffectBase.h"

class C_Explosion : public C_EffectBase
{
public:
	C_Explosion() :
		m_timer(0),
		m_lifetime(30) // 30ÉtÉåÅ[ÉÄÇ≈è¡Ç¶ÇÈ
	{
	}

	~C_Explosion() {}

	void Init(Math::Vector2 pos) override;
	void Update() override;
	void Draw() override;

private:

	static const int StartAnim = 4;
	static const int AnimMax = 9;

	int m_timer;
	int m_lifetime;

	float m_anim;
};