#include "EnemyGenerate.h"
#include"../../Enemy/EnemyManager.h"
#include"../../Player/Player.h"
#include"../../Enemy/EnemyMoveBase.h"

C_EnemyGenerate::C_EnemyGenerate()
{
	m_finished = false;
}

void C_EnemyGenerate::Init()
{
	m_alive = false;
}

void C_EnemyGenerate::Update()
{
	if (!m_alive) return;

	m_time--;

	if (m_time <= 0)
	{
		m_alive = false;
	}
}

void C_EnemyGenerate::Draw()
{
}

void C_EnemyGenerate::SkillActivate()
{
	m_alive = true;
	m_time = 30;
	auto p = m_player.lock();
	auto em = m_enemymanager.lock();

	if (p&&em)
	{
		em->SkillEnemySpworn(p->GetPos(), m_usetype,EnemyMoveType::Type3);
	}

	m_finished = true;
}

void C_EnemyGenerate::EnemySkillActivate()
{
	m_alive = true;
	m_time = 30;
	auto e = m_enemy.lock();
	auto em = m_enemymanager.lock();

	if (e && em)
	{
		em->SkillEnemySpworn(e->GetPos(), m_usetype,EnemyMoveType::Type1);
	}
}
