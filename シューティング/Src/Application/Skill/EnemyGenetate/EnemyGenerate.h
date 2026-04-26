#pragma once
#include"Application/Skill/SkillBase.h"

class C_EnemyGenerate:public C_SkillBase
{
public:
	C_EnemyGenerate(){}
	~C_EnemyGenerate(){}

	void Init()		override;
	void Update()	override;
	void Draw()		override;

	void SetEnemyMagager(std::shared_ptr<C_EnemyManager> manager)override { m_enemymanager = manager; }

	//“GŽæ“¾—p
	void SetEnemy(std::shared_ptr<C_EnemyMoveBase> enemybase)override { m_enemy = enemybase; }

	void SkillActivate()override;

	//“G—p
	void EnemySkillActivate()override;

	bool IsTopDraw()override { return false; }

private:

	std::shared_ptr<C_EnemyManager> m_enemymanager;

	std::shared_ptr<C_EnemyMoveBase> m_enemy;



};
