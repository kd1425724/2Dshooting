#pragma once
#include "../EffectBase.h"

enum class LineAlpha
{
    Up,
    Down
};

class C_WarningLine : public C_EffectBase
{
public:
    C_WarningLine() {}
    ~C_WarningLine() override {}

    void Init(Math::Vector2 pos, Math::Vector2 scale, int time) override;
    void Update() override;
    void Draw() override;

private:
    Math::Vector2 m_linescale = { 1.0f, 1.0f };

    LineAlpha m_linealpha = LineAlpha::Up;

    int m_linetime = 0;
};