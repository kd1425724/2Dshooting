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
			std::shared_ptr<C_HitBase> a = m_hits[i];
			std::shared_ptr<C_HitBase> b = m_hits[j];

			// 当たる組み合わせだけ判定
			if (!CanHit(a->GetType(), b->GetType()))
				continue;

			if (a->IsHit(*b))
			{
				// ここで通知
				a->OnHit(b);
				b->OnHit(a);
			}
		}
	}
}

void C_HitManager::AddHit(std::shared_ptr<C_HitBase> hit)
{
	m_hits.push_back(hit);
}

void C_HitManager::Clear()
{
	m_hits.clear();
}

void C_HitManager::RemoveHit(std::shared_ptr<C_HitBase> hit)
{
	//m_hitsの最初から最後からhitを探しそれを消去
	auto it = std::find(m_hits.begin(), m_hits.end(), hit);

	if (it != m_hits.end())
	{
		m_hits.erase(it);
	}
}

bool C_HitManager::CanHit(HitType a, HitType b)
{
	// 当たる組み合わせ
	//プレイヤー
	if (a == HitType::Player && b == HitType::Enemy) return true;
	if (a == HitType::Player && b == HitType::S_EnemyBarrier) return true;
	
	//プレイヤーショット
	if (a == HitType::PlayerShot && b == HitType::Enemy) return true;
	if (a == HitType::PlayerShot && b == HitType::S_EnemyBarrier) return true;

	// 逆もOKにする
	//プレイヤー
	if (b == HitType::Player && a == HitType::Enemy) return true;
	if (b == HitType::Player && a == HitType::S_EnemyBarrier) return true;
	if (b == HitType::PlayerShot && a == HitType::Enemy) return true;

	//プレイヤーショット
	if (b == HitType::PlayerShot && a == HitType::Enemy) return true;
	if (b == HitType::PlayerShot && a == HitType::S_EnemyBarrier) return true;


	return false;
}