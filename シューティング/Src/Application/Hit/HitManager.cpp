#include "HitManager.h"
#include "HitBase.h"

C_HitManager::C_HitManager()
{
}

C_HitManager::~C_HitManager()
{
}

void C_HitManager::Init()
{
}

void C_HitManager::Update()
{
	int size = (int)m_hits.size();

	for (int i = 0; i < size; i++)
	{
		m_hits[i]->Update();

		for (int j = i + 1; j < size; j++)
		{
			C_HitBase* a = m_hits[i];
			C_HitBase* b = m_hits[j];

			// 当たる組み合わせだけ判定
			if (!CanHit(a->GetType(), b->GetType()))
				continue;

			if (a->IsHit(*b))
			{
				// ここで通知
				// a->OnHit(b);
				// b->OnHit(a);
			}
		}
	}
}

void C_HitManager::AddHit(C_HitBase* hit)
{
	m_hits.push_back(hit);
}

void C_HitManager::Clear()
{
	m_hits.clear();
}

bool C_HitManager::CanHit(HitType a, HitType b)
{
	// 例：当たる組み合わせ
	if (a == HitType::Player && b == HitType::Enemy) return true;
	if (a == HitType::Player && b == HitType::EnemyShot) return true;
	if (a == HitType::PlayerShot && b == HitType::Enemy) return true;

	// 逆もOKにする
	if (b == HitType::Player && a == HitType::Enemy) return true;
	if (b == HitType::Player && a == HitType::EnemyShot) return true;
	if (b == HitType::PlayerShot && a == HitType::Enemy) return true;

	return false;
}