#include"ShotHit.h"
#include"../../Skill/Shot/Shot.h" 

C_ShotHit::C_ShotHit()
{
	m_shot = nullptr;
}

C_ShotHit::~C_ShotHit()
{
}

void C_ShotHit::Init()
{
	SetType(HitType::Player);
}

void C_ShotHit::Update()
{
	//// 必要ならここで座標同期など
	//// 例：
	/* if (m_player)
	 {
		 SetPos(m_player->GetPos());
	 }*/
}

void C_ShotHit::OnHit(std::shared_ptr<C_HitBase> other)
{
	switch (GetType())
	{
	case HitType::PlayerShot:

		switch (other->GetType())
		{
		case HitType::Player:
			break;
		case HitType::Enemy:
			break;
		case HitType::PlayerShot:
			break;
		case HitType::S_PlayerBarrier:
			break;
		case HitType::S_EnemyBarrier:
			break;
		case HitType::S_PlayerLaser:
			break;
		case HitType::S_PlayerGenerateEnemy:
			break;
		default:
			break;
		}
		break;
	case HitType::Enemy:

		switch (other->GetType())
		{
		case HitType::Player:
			break;
		case HitType::Enemy:
			break;
		case HitType::PlayerShot:
			break;
		case HitType::S_PlayerBarrier:
			break;
		case HitType::S_EnemyBarrier:
			break;
		case HitType::S_PlayerLaser:
			break;
		case HitType::S_PlayerGenerateEnemy:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

}