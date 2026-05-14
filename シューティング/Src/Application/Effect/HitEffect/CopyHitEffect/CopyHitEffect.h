#pragma once
#include "../../EffectBase.h"

class C_CopyHitEffect : public C_EffectBase
{
public:
	C_CopyHitEffect() {}
	~C_CopyHitEffect()override { Release(); }

	void Init(Math::Vector2 pos) override;
	void Update() override;
	void Draw() override;

private:

	void Release() override;

	static const int AnimMax = 5;

	float m_anim=0;
};