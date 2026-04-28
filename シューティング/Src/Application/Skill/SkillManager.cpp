#include"SkillManager.h"
#include"SkillBase.h"
#include"EnemyGenetate/EnemyGenerate.h"
#include"Laser1/Laser.h"
#include"Barrier/Barrier.h"
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

	SetPlayerSkill(SkillType::Barrier);
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

	for (int i = 0; i < m_enemyskills.size(); i++)
	{
		if (m_enemyskills[i])
		{
			m_enemyskills[i]->Update();
		}
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

	switch (skilltype)
	{
	case SkillType::CopyShot:
		break;
	case SkillType::EnemyGenerate:
		m_playerskills = std::make_shared<C_EnemyGenerate>();
		m_playerskills->SetUseType(UseType::Player);
		m_playerskills->SetEnemyMagager(m_enemymanager);
		m_playerskills->SetPlayer(m_player);
		m_playerskills->Init();
		break;
	case SkillType::Barrier:
		m_playerskills = std::make_shared<C_Barrier>();
		m_playerskills->SetUseType(UseType::Player);
		m_playerskills->SetPlayer(m_player);
		m_playerskills->SetTexture(m_barriertex);
		m_playerskills->Init();
		break;
	case SkillType::Laser:
		m_playerskills = std::make_shared<C_Laser>();
		m_playerskills->SetUseType(UseType::Player);
		m_playerskills->SetPlayer(m_player);
		m_playerskills->SetTexture(m_lasertex);
		m_playerskills->Init();
		break;
	default:
		break;
	}	
}

void C_SkillManager::SetEnemySkill(SkillType skilltype, std::shared_ptr<C_EnemyMoveBase> enemybase)
{
	switch (skilltype)
	{
	case SkillType::None:
		break;
	case SkillType::CopyShot:
		break;
	case SkillType::EnemyGenerate:
		m_enemyskills.emplace_back(std::make_shared<C_EnemyGenerate>());
		m_enemyskills.back()->SetUseType(UseType::Enemy);
		m_enemyskills.back()->SetEnemyMagager(m_enemymanager);
		m_enemyskills.back()->SetEnemy(enemybase);
		m_enemyskills.back()->Init();
		m_enemyskills.back()->EnemySkillActivate();
		break;
	case SkillType::Barrier:
		m_enemyskills.emplace_back(std::make_shared<C_Barrier>());
		m_enemyskills.back()->SetUseType(UseType::Enemy);
		m_enemyskills.back()->SetEnemy(enemybase);
		m_enemyskills.back()->SetTexture(m_barriertex);
		m_enemyskills.back()->Init();
		m_enemyskills.back()->EnemySkillActivate();
		break;
	case SkillType::Laser:
		m_enemyskills.emplace_back(std::make_shared<C_Laser>());
		m_enemyskills.back()->SetUseType(UseType::Enemy);
		m_enemyskills.back()->SetEnemy(enemybase);
		m_enemyskills.back()->SetTexture(m_lasertex);
		m_enemyskills.back()->Init();
		m_enemyskills.back()->EnemySkillActivate();
		break;
	default:
		break;
	}
}
