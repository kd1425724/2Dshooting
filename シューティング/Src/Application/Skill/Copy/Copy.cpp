#include"Copy.h"
#include"Application/Enemy/EnemyManager.h"
#include"Application/Enemy/EnemyMoveBase.h"
#include"../../Player/Player.h"
#include"../../Skill/Shot/Shot.h"
void C_Copy::Init()
{
	m_shot = std::make_shared<C_Shot>();
	if (auto hm = m_hitmanager.lock())
	{
		m_shot->SetHitManager(hm);
	}

	m_alive = false;

	m_time = 0;
}

void C_Copy::Update()
{
	m_shot->Update();

	m_time--;
	if (m_time <= 0)
	{
		m_time = 0;
		m_alive = false;
	}
}

void C_Copy::Draw()
{
	
	m_shot->Draw();
	
}

void C_Copy::SkillActivate()
{
	m_alive = true;
	m_time = 60;

	std::shared_ptr<C_Player> p = m_player.lock();

	if (p)
	{
		Math::Vector2 p_pos = p->GetPos();

		m_shot->ShotManager(ShotType::CopyShot, ShotTextureType::Copy, { 5,0 }, { 63,32 },
			p_pos, { p_pos.x + 100,p_pos.y }, 30);
	}
}

void C_Copy::EnemySkillActivate()
{
	return;
}

void C_Copy::Release()
{
	m_shot = nullptr;
}
