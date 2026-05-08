#include "EffectManager.h"
#include"Explosion/Explosion.h"
#include"HitEffect/BoltHitEffect/BoltHitEffect.h"
#include"HitEffect/CopyHitEffect/CopyHitEffect.h"
#include"LaserStartEffect/LaserStartEffect.h"

void C_EffectManager::Init()
{
	//爆発画像
	m_explosiontex = std::make_shared<KdTexture>();
	m_explosiontex->Load("Texture/Effect/Game/Explosion.png");

	//レーザー緑
	m_laserstartgreeneffecttex = std::make_shared<KdTexture>();
	m_laserstartgreeneffecttex->Load("Texture/Effect/Game/LaserStartGreen.png");
	//レーザー赤
	m_laserstartredeffecttex = std::make_shared<KdTexture>();
	m_laserstartredeffecttex->Load("Texture/Effect/Game/LaserStartRed.png");

	//Hit画像
	//bolt青
	m_boltbulehiteffecttex = std::make_shared<KdTexture>();
	m_boltbulehiteffecttex->Load("Texture/Effect/Game/Hit/BuleHit5.png");
	//bolt緑
	m_boltgreenhiteffecttex = std::make_shared<KdTexture>();
	m_boltgreenhiteffecttex->Load("Texture/Effect/Game/Hit/GreenHit5.png");
	//コピー
	m_copyhiteffecttex = std::make_shared<KdTexture>();
	m_copyhiteffecttex->Load("Texture/Effect/Game/Hit/CopyHit.png");
}
void C_EffectManager::Update()
{
	for (auto it = m_effects.begin(); it != m_effects.end();)
	{
		//存在しなければ消去
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

	for (auto it = m_topdraweffects.begin(); it != m_topdraweffects.end();)
	{
		//存在しなければ消去
		if (!(*it)->GetAlive())
		{
			it = m_topdraweffects.erase(it);
		}

		else
		{
			(*it)->Update();
			++it;
		}
	}

	for (auto& eff : m_addeffects)
	{
		m_effects.push_back(eff);
	}

	m_addeffects.clear();

	for (auto& eff : m_addtopdraweffects)
	{
		m_topdraweffects.push_back(eff);
	}

	m_addtopdraweffects.clear();
}

void C_EffectManager::Draw()
{
	for (auto& e : m_effects)
	{
		e->Draw();
	}
}

void C_EffectManager::IsTopDraw()
{
	for (auto& e : m_topdraweffects)
	{
		e->Draw();
	}
}


void C_EffectManager::AddEffect(EffectType type, Math::Vector2 pos)
{
	switch (type)
	{
	case EffectType::Explosion:
		m_addeffects.push_back(std::make_shared<C_Explosion>());
		m_addeffects.back()->SetTexture(m_explosiontex);
		m_addeffects.back()->Init(pos);
		break;
	case EffectType::ExplosionTopDraw:
		m_addtopdraweffects.push_back(std::make_shared<C_Explosion>());
		m_addtopdraweffects.back()->SetTexture(m_explosiontex);
		m_addtopdraweffects.back()->Init(pos);
		break;
	case EffectType::LaserStartGreen:
		m_addeffects.push_back(std::make_shared<C_LaserStartEffect>());
		m_addeffects.back()->SetTexture(m_laserstartgreeneffecttex);
		m_addeffects.back()->Init(pos);
		break;
	case EffectType::LaserStartRed:
		m_addeffects.push_back(std::make_shared<C_LaserStartEffect>());
		m_addeffects.back()->SetTexture(m_laserstartredeffecttex);
		m_addeffects.back()->Init(pos);
		break;
	case EffectType::BoltHitBule:
		m_addeffects.push_back(std::make_shared<C_BoltHitEffect>());
		m_addeffects.back()->SetTexture(m_boltbulehiteffecttex);
		m_addeffects.back()->Init(pos);
		break;
	case EffectType::BoltHitGreen:
		m_addeffects.push_back(std::make_shared<C_BoltHitEffect>());
		m_addeffects.back()->SetTexture(m_boltgreenhiteffecttex);
		m_addeffects.back()->Init(pos);
		break;
	case EffectType::CopyHit:
		m_addeffects.push_back(std::make_shared<C_CopyHitEffect>());
		m_addeffects.back()->SetTexture(m_copyhiteffecttex);
		m_addeffects.back()->Init(pos);
		break;
	
	default:
		break;
	}
}

void C_EffectManager::Release()
{
	m_effects.clear();
	m_addeffects.clear();
	m_topdraweffects.clear();
	m_addtopdraweffects.clear();
}
