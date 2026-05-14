#pragma once
#include"Application/Skill/SkillBase.h"

class C_EnemyGenerate : public C_SkillBase
{
public:
	C_EnemyGenerate();
	~C_EnemyGenerate() override { Release(); }

	void Init() override;
	void Update() override;
	void Draw() override;

	void SetEnemyMagager(std::shared_ptr<C_EnemyManager> manager) override
	{
		m_enemymanager = manager;
	}

	//“GŽæ“¾—p
	void SetEnemy(std::shared_ptr<C_EnemyMoveBase> enemybase) override
	{
		m_enemy = enemybase;
	}

	void SkillActivate() override;

	//“G—p
	void EnemySkillActivate() override;

	DrawType IsDrawType() override
	{
		return DrawType::BottomDraw;
	}

private:

	void Release() override;

	std::weak_ptr<C_EnemyManager> m_enemymanager;

	std::weak_ptr<C_EnemyMoveBase> m_enemy;

	int m_time = 0;
};