#pragma once
#include "../EffectBase.h"

class C_LaserStartEffect : public C_EffectBase
{
public:
	C_LaserStartEffect() {}
	~C_LaserStartEffect() {}

	void Init(Math::Vector2 pos) override;
	void Update() override;
	void Draw() override;

private:

	static const int AnimMax = 7;

	float m_anim=0;
};