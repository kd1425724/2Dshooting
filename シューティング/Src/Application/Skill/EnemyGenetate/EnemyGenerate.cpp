#include "EnemyGenerate.h"
#include"../../Enemy/EnemyManager.h"
#include"../../Prayer/Player.h"

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
	m_manager->SkillEnemySpworn(m_player->GetPlayerPos());
}
