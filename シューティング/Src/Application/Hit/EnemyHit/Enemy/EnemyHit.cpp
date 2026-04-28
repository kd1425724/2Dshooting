#include"EnemyHit.h"
#include"../../../Enemy/EnemyMoveBase.h" 

C_EnemyHit::C_EnemyHit()
{
	m_enemy = nullptr;
}

C_EnemyHit::~C_EnemyHit()
{
}

void C_EnemyHit::Init()
{
	SetType(HitType::Player);
}

void C_EnemyHit::Update()
{
	//// 必要ならここで座標同期など
	//// 例：
	/* if (m_player)
	 {
		 SetPos(m_player->GetPos());
	 }*/
}

void C_EnemyHit::OnHit(std::shared_ptr<C_HitBase> other)
{
	switch (GetType())
	{
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
	case HitType::S_PlayerGenerateEnemy:
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