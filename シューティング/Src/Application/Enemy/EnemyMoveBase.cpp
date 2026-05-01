#include "EnemyMoveBase.h"
#include"../Player/Player.h"

void C_EnemyMoveBase::Update()
{
	return;
}
void C_EnemyMoveBase::Draw()
{
	return;
}
void C_EnemyMoveBase::Damage(int value)
{
	if (m_hittimer <= 0)
	{
		m_hp -= value;

		m_hittimer = HitTimer;
	}
}
void C_EnemyMoveBase::HitUpdate()
{
	if (m_hittimer > 0)
	{
		m_hittimer--;

		if ((m_hittimer / 2) % 2 == 0)
		{
			m_color = { 1.5f, 1.5f, 1.5f, 1.0f }; // ñæÇÈÇ≠ÅiîíÇ¡Ç€Ç≠Åj
		}
		else
		{
			m_color = { 1.0f, 1.0f, 1.0f, 1.0f }; // í èÌ
		}
	}
}
void C_EnemyMoveBase::Release()
{
	return;
}
