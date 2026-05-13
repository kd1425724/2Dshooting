#include"SkillManager.h"
#include"SkillBase.h"
#include"EnemyGenetate/EnemyGenerate.h"
#include"Laser1/Laser.h"
#include"Barrier/Barrier.h"
#include"Copy/Copy.h"
#include"../Input/Input.h"
#include"../Enemy/EnemyMoveBase.h"
#include"../Ui/ScenesUi/GameUi.h"
#include"../Scenes/Game/Game.h"
#include"../Common/CommonTexture.h"
void C_SkillManager::Release()
{
	
}

void C_SkillManager::Init() 
{
	auto gu = m_gameui.lock();
	if (gu)
	{
		gu->SetSkillIconTex(CommonTex.GetSkillIcontex());
	}

	SetPlayerSkill(SkillType::CopyShot);
}
void C_SkillManager::Update()
{
	if (Input.GetDebugKey(DebugKeyType::Pkey) &&
		!Input.GetDebugKeyFlg(DebugKeyType::Pkey))
	{
		SetPlayerSkill(SkillType::Laser);
	}

	if (Input.GetDebugKey(DebugKeyType::Okey) &&
		!Input.GetDebugKeyFlg(DebugKeyType::Okey))
	{
		SetPlayerSkill(SkillType::Barrier);
	}
	if (Input.GetDebugKey(DebugKeyType::Ikey) &&
		!Input.GetDebugKeyFlg(DebugKeyType::Ikey))
	{
		SetPlayerSkill(SkillType::EnemyGenerate);
	}
	if (auto o = m_owner.lock())
	{
		if (o->GetGameMode() != GameMode::Start)
		{
			if (m_playerskills)
			{
				//スキル発動
				if (Input.GetPlayerKeyDown(PlayerKeyType::Skill) &&
					!m_playerskills->GetAlive())
				{
					m_playerskills->SkillActivate();
				}

				m_playerskills->Update();

				bool finished = m_playerskills->GetFinishedFlg();

				if (finished)
				{
					SetPlayerSkill(SkillType::CopyShot);
					return;
				}
			}
		}
	}

	for (int i = 0; i < m_enemyskills.size(); )
	{
		// nullチェック
		if (!m_enemyskills[i])
		{
			m_enemyskills.erase(m_enemyskills.begin() + i);
			continue;
		}

		// 更新
		m_enemyskills[i]->Update();

		// 死んだら削除
		if (!m_enemyskills[i]->GetAlive())
		{
			m_enemyskills.erase(m_enemyskills.begin() + i);
			continue;
		}

		i++;
	}

	for (auto& s : m_addenemyskill)
	{
		m_enemyskills.push_back(s);
	}

	m_addenemyskill.clear();
}
void C_SkillManager::Draw()
{

	if (m_playerskills)
	{
		//画像順番調整用
		if (m_playerskills->IsDrawType() == DrawType::MidDraw)
		{
			m_playerskills->Draw();
		}
	}
	if (m_playerskills)
	{
		//画像順番調整用
		if (m_playerskills->IsDrawType()== DrawType::BottomDraw)
		{
			m_playerskills->Draw();
		}
	}

	for (int i = 0; i < m_enemyskills.size(); i++)
	{
		if (m_enemyskills[i])
		{
			//画像順番調整用
			if (m_enemyskills[i]->IsDrawType()==DrawType::BottomDraw)
			{
				m_enemyskills[i]->Draw();
			}
		}
	}
}

void C_SkillManager::TopDraw()
{
	if (m_playerskills)
	{
		//画像順番調整用
		if (m_playerskills->IsDrawType() == DrawType::TopDraw)
		{
			m_playerskills->Draw();
		}
	}

	for (int i = 0; i < m_enemyskills.size(); i++)
	{
		if (m_enemyskills[i])
		{
			//画像順番調整用
			if (m_enemyskills[i]->IsDrawType()==DrawType::TopDraw)
			{
				m_enemyskills[i]->Draw();
			}
		}
	}


}

void C_SkillManager::MidDraw()
{
	for (int i = 0; i < m_enemyskills.size(); i++)
	{
		if (m_enemyskills[i])
		{
			//画像順番調整用
			if (m_enemyskills[i]->IsDrawType() == DrawType::MidDraw)
			{
				m_enemyskills[i]->Draw();
			}
		}
	}

}


void C_SkillManager::SetPlayerSkill(SkillType skilltype)
{
	auto p = m_player.lock();
	auto em = m_enemymanager.lock();
	auto hm = m_hitmanager.lock();

	switch (skilltype)
	{
	case SkillType::None:
	case SkillType::CopyShot:
		m_playerskills = std::make_shared<C_Copy>();
		m_playerskills->SetUseType(UseType::Player);
		if (p&&hm)
		{
			m_playerskills->SetPlayer(p);
			m_playerskills->SetHitManager(hm);
		}
		m_playerskills->Init();
		break;
		break;
	case SkillType::EnemyGenerate:
		m_playerskills = std::make_shared<C_EnemyGenerate>();
		m_playerskills->SetUseType(UseType::Player);
		if (p && em)
		{
			m_playerskills->SetEnemyMagager(em);
			m_playerskills->SetPlayer(p);
		}
		m_playerskills->Init();
		break;
	case SkillType::Barrier:
		m_playerskills = std::make_shared<C_Barrier>();
		m_playerskills->SetUseType(UseType::Player);
		if (p&&hm)
		{
			m_playerskills->SetPlayer(p);
			m_playerskills->SetHitManager(hm);
		}
		m_playerskills->SetTexture(CommonTex.GetBarriertex());
		m_playerskills->Init();
		break;
	case SkillType::Laser:
		m_playerskills = std::make_shared<C_Laser>();
		m_playerskills->SetUseType(UseType::Player);
		if (p&&hm)
		{
			m_playerskills->SetPlayer(p);
			m_playerskills->SetHitManager(hm);
		}
		m_playerskills->SetTexture(CommonTex.GetLasertex());
		m_playerskills->Init();
		break;
	default:
		break;
	}	

	//なし以外の時
	if (skilltype != SkillType::None)
	{
		auto gu = m_gameui.lock();

		if (gu)
		{
			gu->SetSkill(skilltype);
		}
	}

}

void C_SkillManager::SetEnemySkill(SkillType skilltype, std::shared_ptr<C_EnemyMoveBase> enemybase)
{
	auto em = m_enemymanager.lock();
	auto hm = m_hitmanager.lock();

	switch (skilltype)
	{
	case SkillType::None:
		break;
	case SkillType::CopyShot:
		break;
	case SkillType::EnemyGenerate:
		m_addenemyskill.emplace_back(std::make_shared<C_EnemyGenerate>());
		m_addenemyskill.back()->SetUseType(UseType::Enemy);	
		if (em)
		{
			m_addenemyskill.back()->SetEnemyMagager(em);
		}
		m_addenemyskill.back()->SetEnemy(enemybase);
		m_addenemyskill.back()->Init();
		m_addenemyskill.back()->EnemySkillActivate();
		break;
	case SkillType::Barrier:
		m_addenemyskill.emplace_back(std::make_shared<C_Barrier>());
		m_addenemyskill.back()->SetUseType(UseType::Enemy);
		if (hm)
		{
			m_addenemyskill.back()->SetHitManager(hm);
		}
		m_addenemyskill.back()->SetEnemy(enemybase);
		m_addenemyskill.back()->SetTexture(CommonTex.GetBarriertex());
		m_addenemyskill.back()->Init();
		if (enemybase->GetEnemyType() != EnemySType::SubBoss)
		{
			m_addenemyskill.back()->EnemySkillActivate({ 2.8f,2.8f });
		}
		else
		{
			m_addenemyskill.back()->EnemySkillActivate({ 1.6f,1.6f });
		}
		break;
	case SkillType::Laser:
		m_addenemyskill.emplace_back(std::make_shared<C_Laser>());
		m_addenemyskill.back()->SetUseType(UseType::Enemy);
		if (hm)
		{
			m_addenemyskill.back()->SetHitManager(hm);
		}
		m_addenemyskill.back()->SetEnemy(enemybase);
		m_addenemyskill.back()->SetTexture(CommonTex.GetLasertex());
		m_addenemyskill.back()->Init();
		m_addenemyskill.back()->EnemySkillActivate();
		break;
	default:
		break;
	}
}

bool C_SkillManager::GetPlayerSkillFlg()
{
	if (m_playerskills)
	{
		 return m_playerskills->GetAlive();
	}

	return false;
}
