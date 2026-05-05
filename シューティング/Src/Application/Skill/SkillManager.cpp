#include"SkillManager.h"
#include"SkillBase.h"
#include"EnemyGenetate/EnemyGenerate.h"
#include"Laser1/Laser.h"
#include"Barrier/Barrier.h"
#include"Copy/Copy.h"
#include"../Input/Input.h"
#include"../Enemy/EnemyMoveBase.h"

void C_SkillManager::Release()
{
	m_lasertex->Release();
	m_barriertex->Release();
}

void C_SkillManager::Init() 
{
	//レーザー
	m_lasertex = std::make_shared<KdTexture>();
	m_lasertex->Load("Texture/Skill/Attack/Laser.png");
	//バリア
	m_barriertex = std::make_shared<KdTexture>();
	m_barriertex->Load("Texture/Skill/Barrier/Barrier.png");

	SetPlayerSkill(SkillType::EnemyGenerate);
}
void C_SkillManager::Update()
{
	if (m_playerskills)
	{
		m_playerskills->Update();

		//スキル発動
		if (Input.GetPlayerKey(PlayerKeyType::Skill) &&
			!Input.GetPlayerKeyFlg(PlayerKeyType::Skill))
		{
			m_playerskills->SkillActivate();
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


}
void C_SkillManager::Draw()
{
	if (m_playerskills)
	{
		//画像順番調整用
		if (!m_playerskills->IsTopDraw())
		{
			m_playerskills->Draw();
		}
	}

	for (int i = 0; i < m_enemyskills.size(); i++)
	{
		//画像順番調整用
		if (!m_enemyskills[i]->IsTopDraw())
		{
			if (m_enemyskills[i])
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
		if (m_playerskills->IsTopDraw())
		{
			m_playerskills->Draw();
		}
	}

	for (int i = 0; i < m_enemyskills.size(); i++)
	{
		//画像順番調整用
		if (m_enemyskills[i]->IsTopDraw())
		{
			if (m_enemyskills[i])
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
		m_playerskills->SetTexture(m_barriertex);
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
		m_playerskills->SetTexture(m_lasertex);
		m_playerskills->Init();
		break;
	default:
		break;
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
		m_enemyskills.emplace_back(std::make_shared<C_EnemyGenerate>());
		m_enemyskills.back()->SetUseType(UseType::Enemy);	
		if (em)
		{
			m_enemyskills.back()->SetEnemyMagager(em);
		}
		m_enemyskills.back()->SetEnemy(enemybase);
		m_enemyskills.back()->Init();
		m_enemyskills.back()->EnemySkillActivate();
		break;
	case SkillType::Barrier:
		m_enemyskills.emplace_back(std::make_shared<C_Barrier>());
		m_enemyskills.back()->SetUseType(UseType::Enemy);
		if (hm)
		{
			m_enemyskills.back()->SetHitManager(hm);
		}
		m_enemyskills.back()->SetEnemy(enemybase);
		m_enemyskills.back()->SetTexture(m_barriertex);
		m_enemyskills.back()->Init();
		if (enemybase->GetEnemyType() != EnemySType::SubBoss)
		{
			m_enemyskills.back()->EnemySkillActivate({ 2.6f,2.6f });
		}
		else
		{
			m_enemyskills.back()->EnemySkillActivate({ 1.6f,1.6f });
		}
		break;
	case SkillType::Laser:
		m_enemyskills.emplace_back(std::make_shared<C_Laser>());
		m_enemyskills.back()->SetUseType(UseType::Enemy);
		if (hm)
		{
			m_enemyskills.back()->SetHitManager(hm);
		}
		m_enemyskills.back()->SetEnemy(enemybase);
		m_enemyskills.back()->SetTexture(m_lasertex);
		m_enemyskills.back()->Init();
		m_enemyskills.back()->EnemySkillActivate();
		break;
	default:
		break;
	}
}
