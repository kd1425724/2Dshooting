#include "EnemyGenerate.h"
#include"../../Enemy/EnemyManager.h"
#include"../../Prayer/Player.h"
#include"../../Enemy/EnemyMoveBase.h"

void C_EnemyGenerate::Init()
{

}

void C_EnemyGenerate::Update()
{
}

void C_EnemyGenerate::Draw()
{
}

void C_EnemyGenerate::SkillActivate()
{
	m_enemymanager->SkillEnemySpworn(m_player->GetPos(), m_usetype);
}

void C_EnemyGenerate::EnemySkillActivate()
{
	m_enemymanager->SkillEnemySpworn(m_enemy->GetPos(), m_usetype);
}
