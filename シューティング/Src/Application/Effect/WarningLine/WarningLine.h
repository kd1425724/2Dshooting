#pragma once
#include"../EffectBase.h"

enum class LineAlpha
{
	Up,
	Down
};

class C_WarningLine:public C_EffectBase
{
public:
	C_WarningLine(){}
	~C_WarningLine(){}

	void Init(Math::Vector2 pos,Math::Vector2 scale,int time) override;
	void Update() override;
	void Draw() override;

private:

	Math::Vector2 m_linescale;

	LineAlpha m_linealpha;

	int m_killcnt;

	int m_linetime;

};