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
		m_finished = true;
	}
}

void C_EnemyGenerate::Draw()
{
}

void C_EnemyGenerate::SkillActivate()
{
	m_alive = true;
	m_time = 60;
	auto p = m_player.lock();
	auto em = m_enemymanager.lock();

	if (p&&em)
	{
		em->SkillEnemySpworn(p->GetPos(), m_usetype,EnemyMoveType::Type3);
	}
}

void C_EnemyGenerate::EnemySkillActivate()
{
	m_alive = true;
	m_time = 30;
	auto e = m_enemy.lock();
	auto em = m_enemymanager.lock();

	if (e && em)
	{
		// —”¶¬Šíi1‰ñ‚¾‚¯¶¬j
		static std::random_device rd;
		static std::mt19937 mt(rd());

		// 0`EnemyMoveTypeNum
		std::uniform_int_distribution<int> dist((int)EnemyMoveType::Type1, (int)EnemyMoveType::Type3);

		EnemyMoveType type =(EnemyMoveType)dist(mt);

		em->SkillEnemySpworn(
			e->GetPos(),
			m_usetype,
			type
		);
	}
}
