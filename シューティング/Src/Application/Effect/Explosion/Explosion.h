#pragma once
#include "../EffectBase.h"

class C_Explosion : public C_EffectBase
{
public:
    C_Explosion() {}

    ~C_Explosion() override { Release(); }

    void Init(Math::Vector2 pos) override;
    void Update() override;
    void Draw() override;

private:

	void Release() override;

    static const int AnimMax = 7;

    float m_anim = 0.0f;
};