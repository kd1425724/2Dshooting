#pragma once
#include "../../EffectBase.h"

class C_BoltHitEffect : public C_EffectBase
{
public:
	C_BoltHitEffect(){}

	~C_BoltHitEffect() {}

	void Init(Math::Vector2 pos) override;
	void Update() override;
	void Draw() override;

private:

	static const int AnimMax = 7;

	float m_anim=0;
};