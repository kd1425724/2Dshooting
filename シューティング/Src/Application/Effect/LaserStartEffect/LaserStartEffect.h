#pragma once
#include "../EffectBase.h"

class C_LaserStartEffect : public C_EffectBase
{
public:
	C_LaserStartEffect() {}
	~C_LaserStartEffect()override { Release(); }

	void Init(Math::Vector2 pos) override;
	void Update() override;
	void Draw() override;

private:

	void Release() override;

	static const int AnimMax = 7;

	float m_anim=0;
};