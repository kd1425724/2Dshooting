#include "EffectManager.h"
#include"Explosion/Explosion.h"
#include"HitEffect/BoltHitEffect/BoltHitEffect.h"
#include"HitEffect/CopyHitEffect/CopyHitEffect.h"
#include"LaserStartEffect/LaserStartEffect.h"
#include"WarningLine/WarningLine.h"
#include"ScoreUp/ScoreUp.h"
#include"CopyScan/CopyScan.h"
#include"ScanCompleteText/ScanCompleteText.h"
#include"../Common/CommonTexture.h"

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

	//予告線
	m_warninglinetex = std::make_shared<KdTexture>();
	m_warninglinetex->Load("Texture/Effect/Game/WarningLine.png");

	//Hit画像
	//bolt青
	m_boltbluehiteffecttex = std::make_shared<KdTexture>();
	m_boltbluehiteffecttex->Load("Texture/Effect/Game/Hit/BlueHit5.png");
	//bolt緑
	m_boltgreenhiteffecttex = std::make_shared<KdTexture>();
	m_boltgreenhiteffecttex->Load("Texture/Effect/Game/Hit/GreenHit5.png");
	//コピー
	m_copyhiteffecttex = std::make_shared<KdTexture>();
	m_copyhiteffecttex->Load("Texture/Effect/Game/Hit/CopyHit.png");

	//プラス
	m_scoreupeffecttex = std::make_shared<KdTexture>();
	m_scoreupeffecttex->Load("Texture/Ui/Font/Plus.png");
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

	for (auto it = m_bottomdraweffects.begin(); it != m_bottomdraweffects.end();)
	{
		//存在しなければ消去
		if (!(*it)->GetAlive())
		{
			it = m_bottomdraweffects.erase(it);
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

	for (auto& eff : m_addbottomdraweffects)
	{
		m_bottomdraweffects.push_back(eff);
	}

	m_addbottomdraweffects.clear();
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

void C_EffectManager::IsBottomDraw()
{
	for (auto& e : m_bottomdraweffects)
	{
		e->Draw();
	}
}


void C_EffectManager::AddEffect(EffectType type, Math::Vector2 pos,Math::Vector2 scale,int time)
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
	case EffectType::BoltHitBlue:
		m_addeffects.push_back(std::make_shared<C_BoltHitEffect>());
		m_addeffects.back()->SetTexture(m_boltbluehiteffecttex);
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
	case EffectType::WarningLine:
		m_addbottomdraweffects.push_back(std::make_shared<C_WarningLine>());
		m_addbottomdraweffects.back()->SetTexture(m_warninglinetex);
		m_addbottomdraweffects.back()->Init(pos,scale,time);
		break;
	case EffectType::CopyScanConplete:
		m_addtopdraweffects.push_back(std::make_shared<C_ScanCompleteText>());
		m_addtopdraweffects.back()->SetTexture(CommonTex.GetScanCompleteTextTex());
		m_addtopdraweffects.back()->Init(pos, {0,1,0,1});
		break;
	case EffectType::CopyScanMiss:
		m_addtopdraweffects.push_back(std::make_shared<C_ScanCompleteText>());
		m_addtopdraweffects.back()->SetTexture(CommonTex.GetScanMissTextTex());
		m_addtopdraweffects.back()->Init(pos, {1,1,1,1});
		break;
	default:
		break;
	}
}

void C_EffectManager::CopyScanEffect(Math::Vector2 pos, std::shared_ptr<C_SkillManager> skillmanager, std::shared_ptr<C_EnemyMoveBase> enemy)
{
	m_addtopdraweffects.push_back(std::make_shared<C_CopyScan>());
	m_addtopdraweffects.back()->SetTexture(m_copyhiteffecttex);
	
	auto o = m_owner.lock();
	if(o)
	{
		m_addtopdraweffects.back()->SetOwner(m_owner);
	}
	else
	{
		auto o2 = m_owner2.lock();
		if (o2)
		{
			m_addtopdraweffects.back()->SetOwner(m_owner2);
		}
	}
	auto hm = m_hitmanager.lock();
	if (hm)
	{
		m_addtopdraweffects.back()->SetHitManager(hm);
	}
	m_addtopdraweffects.back()->Init(pos, skillmanager, enemy);
}

void C_EffectManager::ScoreEffect(int value)
{
	m_addeffects.push_back(std::make_shared<C_ScoreUp>());
	m_addeffects.back()->SetTexture(m_scoreupeffecttex);
	m_addeffects.back()->Init(m_scoreeffectpos, value);
}

void C_EffectManager::Release()
{
	m_effects.clear();
	m_addeffects.clear();
	m_topdraweffects.clear();
	m_addtopdraweffects.clear();
	m_bottomdraweffects.clear();
	m_addbottomdraweffects.clear();
}
