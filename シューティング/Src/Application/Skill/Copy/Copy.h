#pragma once
#include "Application/Skill/SkillBase.h"

enum class Pattern
{
	Shot,
};

class C_Copy : public C_SkillBase
{
public:
	C_Copy(){}
	~C_Copy()override{}

	void Init() override;
	void Update() override;
	void Draw() override;

	// スキル発動
	void SkillActivate() override;
	void EnemySkillActivate() override;

	// 各種セット
	void SetTexture(std::shared_ptr<KdTexture> tex) override { m_tex = tex; }

	// 描画順
	bool IsTopDraw() override { return false; }

private:

	std::shared_ptr<KdTexture> m_tex;
};