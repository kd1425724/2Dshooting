#pragma once
#include "../EffectBase.h"

class C_ScoreUp : public C_EffectBase
{
public:
	C_ScoreUp() {}
	~C_ScoreUp() override { Release(); }

	void Init(Math::Vector2 pos,int value) override;
	void Update() override;
	void Draw() override;

private:

	int m_value = 0;

	void Release() override;
};