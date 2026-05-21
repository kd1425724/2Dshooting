#pragma once
#include "../EffectBase.h"

class C_CopyScan : public C_EffectBase
{
public:
	C_CopyScan() {}
	~C_CopyScan() override { Release(); }

	void Init(Math::Vector2 pos, std::shared_ptr<C_SkillManager> skillmanager, std::shared_ptr<C_EnemyMoveBase> enemy) override;
	void Update() override;
	void Draw() override;

private:

	void Release() override;

	static const int AnimMax = 5;

	float m_anim = 0;

	static const int Time = 60;

	int m_time = 0;

	float m_notgreenalpha = 1;
};