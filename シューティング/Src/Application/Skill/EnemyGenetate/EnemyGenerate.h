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

	void SetEnemyManager(std::shared_ptr<C_EnemyManager> manager) { m_manager = manager; }

	void SkillActivate()override;

private:

	std::shared_ptr<C_EnemyManager> m_manager;

};
