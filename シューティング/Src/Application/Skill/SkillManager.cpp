#include"SkillManager.h"
#include"SkillBase.h"
#include"EnemyGenetate/EnemyGenerate.h"
#include"Laser1/Laser.h"
#include"Barrier/Barrier.h"
#include"Copy/Copy.h"
#include"../Input/Input.h"
#include"../Enemy/EnemyMoveBase.h"
#include"../Ui/ScenesUi/GameUi.h"

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

	std::vector<std::shared_ptr<KdTexture>> tex;
	tex.push_back(std::make_shared<KdTexture>());
	tex.back()->Load("Texture/Ui/HUD/Copy.png");
	tex.push_back(std::make_shared<KdTexture>());
	tex.back()->Load("Texture/Ui/HUD/EnemyGenerate.png");
	tex.push_back(std::make_shared<KdTexture>());
	tex.back()->Load("Texture/Ui/HUD/Barrier.png");
	tex.push_back(std::make_shared<KdTexture>());
	tex.back()->Load("Texture/Ui/HUD/Laser.png");

	auto gu = m_gameui.lock();
	if (gu)
	{
		gu->SetSkillIconTex(tex);
	}

	SetPlayerSkill(SkillType::CopyShot);
}
void C_SkillManager::Update()
{
	if (GetAsyncKeyState('P') & 0x8000)
	{
		SetPlayerSkill(SkillType::Laser);
	}

	if (m_playerskills)
	{
		m_playerskills->Update();

		//スキル発動
		if (Input.GetPlayerKey(PlayerKeyType::Skill) &&
			!Input.GetPlayerKeyFlg(PlayerKeyType::Skill)&&
			!m_playerskills->GetAlive())
		{
			m_playerskills->SkillActivate();
		}

		if (m_playerskills->GetFinishedFlg())
		{
			SetPlayerSkill(SkillType::CopyShot);
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
	if (m_playerskills)
	{
		//画像順番調整用
		if (m_playerskills->IsDrawType() == DrawType::MidDraw)
		{
			m_playerskills->Draw();
		}
	}

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
		m_addenemyskill.back()->SetTexture(m_barriertex);
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
		m_addenemyskill.back()->SetTexture(m_lasertex);
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
}
