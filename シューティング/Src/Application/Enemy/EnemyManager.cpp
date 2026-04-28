#include "EnemyManager.h"
#include"Application/Common/CommonAPI.h"
#include"Application/Enemy/EnemyMove/EnemyMove1/EnemyMove1.h"
#include"Application/Enemy/EnemyMove/EnemyMove2/EnemyMove2.h"
#include"Application/Enemy/EnemyMove/EnemyMove3/EnemyMove3.h"
#include"Application/Enemy/Boss/Boss/Boss.h"
#include"Application/Enemy/Boss/SubBoss/SubBoss.h"
#include"../Skill/SkillBase.h"


void C_EnemyManager::Init(std::shared_ptr<C_Player> player)
{
	m_player = move(player);

	SpwornEnemyLoad();

	m_enemytex.Load("Texture/Enemy/Fighter.png");

	m_subbosstex.Load("Texture/Enemy/SubBoss/SubBossBase.png");
	m_subbossmovetex.Load("Texture/Enemy/SubBoss/SubBossMove.png");
	m_subbossenginetex.Load("Texture/Enemy/SubBoss/SubBossEngine.png");
	m_subbossdeathtex.Load("Texture/Enemy/SubBoss/SubBossDeath.png");

	m_bosstex.Load("Texture/Enemy/Boss/BossBase.png");
	m_bossmovetex.Load("Texture/Enemy/Boss/BossMove.png");
	m_bossenginetex.Load("Texture/Enemy/Boss/BossEngine.png");
	m_bossdeathtex.Load("Texture/Enemy/Boss/BossDeath.png");
}
void C_EnemyManager::Release()
{

	m_player = nullptr;
	

	m_enemytex.Release();
	m_subbosstex.Release();
	m_subbossmovetex.Release();
	m_subbossenginetex.Release();
	m_subbossdeathtex.Release();

	m_bosstex.Release();
	m_bossmovetex.Release();
	m_bossenginetex.Release();
	m_bossdeathtex.Release();
}

void C_EnemyManager::SpwornEnemyLoad()
{
	FILE* fp;

	if (fopen_s(&fp, "Data/EnemyData/StageEnemyData.csv", "r") == 0)
	{
		char dummy[255];

		int setenemytype[JudgmentNum] = {};
		int setmovetype[JudgmentNum] = {};
		int setpospattern[JudgmentNum] = {};
		int setmovepattern[JudgmentNum] = {};

		fgets(dummy, 255, fp);				//1行飛ばす

		for (int i = 0; i < JudgmentNum; i++)
		{
			fscanf_s(fp, "%*[^,],%*[^,],%d,%d,%d,%d",&setenemytype[i],&setmovetype[i],&setpospattern[i],&setmovepattern[i]);

			switch (setenemytype[i])
			{
			case 1:
				m_spworntype[i].type = EnemyType::s;
				break;
			default:
				break;
			}

			switch (setmovetype[i])
			{
			case 1:
				m_spworntype[i].movetype = EnemyMoveType::Type1;
				break;
			case 2:
				m_spworntype[i].movetype = EnemyMoveType::Type2;
				break;
			case 3:
				m_spworntype[i].movetype = EnemyMoveType::Type3;
				break;
			default:
				break;
			}

			switch (setpospattern[i])
			{
			case 1:
				m_spworntype[i].pospattern = PosPattern::Pattern1;
				break;
			case 2:
				m_spworntype[i].pospattern = PosPattern::Pattern2;
				break;
			case 3:
				m_spworntype[i].pospattern = PosPattern::Pattern3;
				break;
			case 4:
				m_spworntype[i].pospattern = PosPattern::Pattern4;
				break;
			default:
				break;
			}

			switch (setmovepattern[i])
			{
			case 1:
				m_spworntype[i].movepattern = MovePattern::Pattern1;
				break;
			case 2:
				m_spworntype[i].movepattern = MovePattern::Pattern2;
				break;
			case 3:
				m_spworntype[i].movepattern = MovePattern::Pattern3;
				break;
			case 4:
				m_spworntype[i].movepattern = MovePattern::Pattern4;
				break;
			case 5:
				m_spworntype[i].movepattern = MovePattern::Pattern5;
				break;
			default:
				break;
			}
		}

		fclose(fp);
	}
	else
	{
		//デバッグ用
		//OutputDebugStringA("CSV読み込み失敗\n");

	}
}


void C_EnemyManager::Update()
{
	if (!m_enemys.empty())
	{
		for (int i = 0; i < m_enemys.size(); i++)
		{
			m_enemys[i]->Update();

			if (COMMONAPI.OutOfPlayAreaPlusMargin(m_enemys[i]->GetPos(),m_enemys[i]->GetRadius())||
				!m_enemys[i]->GetAlive())
			{
				m_enemys.erase(m_enemys.begin() + i);

				i--;

				continue;
			}
		}
	}
	if (!m_skillenemys.empty())
	{
		for (int i = 0; i < m_skillenemys.size(); i++)
		{
			m_skillenemys[i]->Update();

			if (COMMONAPI.OutOfPlayAreaPlusMargin(m_skillenemys[i]->GetPos(),m_skillenemys[i]->GetRadius())||
				!m_skillenemys[i]->GetAlive())
			{
				m_skillenemys.erase(m_skillenemys.begin() + i);

				i--;

				continue;
			}
		}
	}
}
void C_EnemyManager::Draw()
{
	if (!m_enemys.empty())
	{
		for (int i = 0; i < m_enemys.size(); i++)
		{
			m_enemys[i]->Draw();
		}
	}

	if (!m_skillenemys.empty())
	{
		for (int i = 0; i < m_skillenemys.size(); i++)
		{
			m_skillenemys[i]->Draw();
		}
	}
}
void C_EnemyManager::EnemySpworn(int judgmentcount)
{
	switch (m_spworntype[judgmentcount].movetype)
	{
	case EnemyMoveType::Type1:
		for (int i = 0; i < 3; i++)
		{
			m_enemys.emplace_back(std::make_shared<C_EnemyMove1>());

			m_enemys.back()->SetTexandRectandAnimMax(&GetEnemyTexture(m_spworntype[judgmentcount].type),
				{ 64,64 }, { 0,0 });

			m_enemys.back()->Init(m_spworntype[judgmentcount].pospattern, m_spworntype[judgmentcount].movepattern,
				m_player,i);

			m_enemys.back()->SetSkillManager(m_skillmanager);
		}
		break;
	case EnemyMoveType::Type2:
		m_enemys.emplace_back(std::make_shared<C_EnemyMove2>());

		m_enemys.back()->SetTexandRectandAnimMax(&GetEnemyTexture(m_spworntype[judgmentcount].type),
			{ 64,64 }, { 0,0 });

		m_enemys.back()->Init(m_spworntype[judgmentcount].pospattern, m_spworntype[judgmentcount].movepattern,
			m_player, NULL);
		m_enemys.back()->SetSkillManager(m_skillmanager);
		break;
	case EnemyMoveType::Type3:
		break;
	default:
		break;
	}
}

void C_EnemyManager::BossSpworn()
{
	//サブボス
	for (int i = 0; i < 2; i++)
	{
		m_enemys.emplace_back(new C_SubBoss());
		m_enemys.back()->SetTexandRectandAnimMax(&GetEnemyTexture(EnemyType::Boss), { 128,128 }, { NULL,NULL });
		m_enemys.back()->SetMoveTex(&m_subbossmovetex);
		m_enemys.back()->SetEngineTex(&m_subbossenginetex);
		m_enemys.back()->SetDeathTex(&m_subbossdeathtex);
		m_enemys.back()->Init({ 700,(float)0 - 60 + 200 - (i * 400) });
		m_enemys.back()->SetSkillManager(m_skillmanager);
	}

	//ボス
	m_enemys.emplace_back(std::make_shared<C_Boss>());
	m_enemys.back()->Init();
	m_enemys.back()->SetTexandRectandAnimMax(&GetEnemyTexture(EnemyType::Boss), 
		{ 128,128 }, { NULL,NULL });
	m_enemys.back()->SetMoveTex(&m_bossmovetex);
	m_enemys.back()->SetEngineTex(&m_bossenginetex);
	m_enemys.back()->SetDeathTex(&m_bossdeathtex);

	m_enemys.back()->SetSkillManager(m_skillmanager);
}

void C_EnemyManager::SkillEnemySpworn(Math::Vector2 pos,UseType type)
{
	switch (type)
	{
	case UseType::Player:
		for (int i = 0; i < 4; i++)
		{
			//只止まって対称に向かって打つ
			m_skillenemys.emplace_back(std::make_shared<C_EnemyMove3>());

			m_skillenemys.back()->SetTexandRectandAnimMax(&GetEnemyTexture(EnemyType::s),
				{ 64,64 }, { 0,0 });

			m_skillenemys.back()->Init(pos, type, i);
		}
		break;
	case UseType::Enemy:
		for (int i = 0; i < 4; i++)
		{
			//只止まって対称に向かって打つ
			m_enemys.emplace_back(std::make_shared<C_EnemyMove3>());

			m_enemys.back()->SetTexandRectandAnimMax(&GetEnemyTexture(EnemyType::s),
				{ 64,64 }, { 0,0 });

			m_enemys.back()->Init(pos, type, i);

			m_enemys.back()->SetSkillManager(m_skillmanager);
		}
		break;
	default:
		break;
	}
}

KdTexture& C_EnemyManager::GetEnemyTexture(EnemyType type)
{
	switch (type)
	{
	case EnemyType::s:
		return m_enemytex;
	case EnemyType::SubBoss:
		return m_subbosstex;
	case EnemyType::Boss:
		return m_bosstex;
	default:
		return m_enemytex;
		break;
	}
}
