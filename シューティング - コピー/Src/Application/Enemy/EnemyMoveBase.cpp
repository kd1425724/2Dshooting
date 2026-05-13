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

		if (m_hittimer > 7)
		{
			m_color = { 30.0f, 30.0f, 30.0f, 1.0f }; // 明るく（白っぽく）
		}
		else
		{
			if ((m_hittimer / 2) % 2 == 0)
			{
				m_color = { 1.5f, 1.5f, 1.5f, 1.0f }; // 明るく（白っぽく）
			}
			else
			{
				m_color = { 1.0f, 1.0f, 1.0f, 1.0f }; // 通常
			}
		}
	}
	else
	{
		m_color = { 1.0f, 1.0f, 1.0f, 1.0f };
	}
}
void C_EnemyMoveBase::Release()
{
	return;
}
