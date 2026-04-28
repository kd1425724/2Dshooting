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
	// 必要ならここで座標同期など
	// 例：
	 if (m_player)
	 {
	     SetPos(m_player->GetPos());
	 }
}

void C_PlayerHit::OnHit(C_HitBase* other)
{
	// 例：あとでここに処理を書く
	// if (other->GetType() == HitType::EnemyShot)
	// {
	//     m_player->Damage(1);
	// }
	if (other->GetType() == HitType::Enemy)
	{
		//m_isDead = true; // 消える
	}
}