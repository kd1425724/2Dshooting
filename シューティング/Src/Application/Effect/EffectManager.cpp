#include "EffectManager.h"
#include"Explosion/Explosion.h"
#include"HitEffect/BoltHitEffect/BoltHitEffect.h"

void C_EffectManager::Init()
{
	//”š”­‰æ‘œ
	m_explosiontex = std::make_shared<KdTexture>();
	m_explosiontex->Load("Texture/Effect/Game/Explosion.png");

	//Hit‰æ‘œ
	//bolt
	m_bolthiteffcttex = std::make_shared<KdTexture>();
	m_bolthiteffcttex->Load("Texture/Effect/Game/Hit/Hit5.png");
}
void C_EffectManager::Update()
{
	for (auto it = m_effects.begin(); it != m_effects.end();)
	{
		//‘¶Ý‚µ‚È‚¯‚ê‚ÎÁ‹Ž
		if (!(*it)->GetAlive())
		{
			it = m_effects.erase(it);
		}

		else
		{
			(*it)->Update();
			++it;
		}
	}
}

void C_EffectManager::Draw()
{
	for (auto& e : m_effects)
	{
		e->Draw();
	}
}


void C_EffectManager::AddEffect(EffectType type, Math::Vector2 pos)
{
	switch (type)
	{
	case EffectType::Explosion:
		m_effects.push_back(std::make_shared<C_Explosion>());
		m_effects.back()->SetTexture(m_explosiontex);
		m_effects.back()->Init(pos);
		break;
	case EffectType::BoltHitEffect:
		m_effects.push_back(std::make_shared<C_BoltHitEffect>());
		m_effects.back()->SetTexture(m_bolthiteffcttex);
		m_effects.back()->Init(pos);
		break;
	default:
		break;
	}
}

void C_EffectManager::Release()
{
	m_effects.clear();
}
