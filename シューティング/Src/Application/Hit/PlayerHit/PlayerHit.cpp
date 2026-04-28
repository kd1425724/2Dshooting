#include"PlayerHit.h"
#include"../../Player/Player.h" 

C_PlayerHit::C_PlayerHit()
{
	m_player = nullptr;
}

C_PlayerHit::~C_PlayerHit()
{
}

void C_PlayerHit::Init()
{
	SetType(HitType::Player);
}

void C_PlayerHit::Update()
{
	//// 必要ならここで座標同期など
	//// 例：
	/* if (m_player)
	 {
	     SetPos(m_player->GetPos());
	 }*/
}

void C_PlayerHit::OnHit(std::shared_ptr<C_HitBase> other)
{
	switch (other->GetType())
	{
	case HitType::Player:
		break;
	case HitType::Enemy:
		m_player->Dameage();
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
}