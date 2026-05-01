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
}

void C_Copy::Update()
{
	m_shot->Update();
}

void C_Copy::Draw()
{
	
	m_shot->Draw();
	
}

void C_Copy::SkillActivate()
{
	std::shared_ptr<C_Player> p = m_player.lock();

	if (p)
	{
		Math::Vector2 p_pos = p->GetPos();

		m_shot->ShotManager(ShotType::CopyShot, ShotTextureType::Bolt, { 4,0 }, { 48,32 },
			p_pos, { p_pos.x + 100,p_pos.y }, 7);
	}
}

void C_Copy::EnemySkillActivate()
{
	return;
}

