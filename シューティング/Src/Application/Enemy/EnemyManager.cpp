#include "EnemyManager.h"
#include"Application/Common/CommonAPI.h"
#include"Application/Enemy/EnemyMove/EnemyMove1/EnemyMove1.h"
#include"Application/Enemy/EnemyMove/EnemyMove2/EnemyMove2.h"
#include"Application/Enemy/EnemyMove/EnemyMove3/EnemyMove3.h"
#include"Application/Enemy/Boss/Boss/Boss.h"
#include"Application/Enemy/Boss/SubBoss/SubBoss.h"
#include"../Skill/SkillBase.h"
#include"../Hit/HitManager.h"
#include"../Effect/EffectManager.h"

void C_EnemyManager::Init(std::shared_ptr<C_Player> player)
{
	m_player = move(player);

	SpwornEnemyLoad();

	//m_enemytex.Load("Texture/Enemy/Fighter.png");

	//敵１
	m_enemy1tex.Load("Texture/Enemy/Enemy1/Enemy1Base.png");
	m_enemy1enginetex.Load("Texture/Enemy/Enemy1/Enemy1Engine.png");
	//敵２
	m_enemy2tex.Load("Texture/Enemy/Enemy2/Enemy2Base.png");
	m_enemy2enginetex.Load("Texture/Enemy/Enemy2/Enemy2Engine.png");
	//敵３
	m_enemy3tex.Load("Texture/Enemy/Enemy3/Enemy3Base.png");
	m_enemy3enginetex.Load("Texture/Enemy/Enemy3/Enemy3Engine.png");


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
				m_spworntype[i].type = EnemyType::enemy3;
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
			m_enemys[i]->HitUpdate();
			m_enemys[i]->Update();
		}

		for (int i = 0; i < m_enemys.size(); i++)
		{
			if (COMMONAPI.OutOfScreenPlusMargin(m_enemys[i]->GetPos(), m_enemys[i]->GetSize()) ||
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
			m_skillenemys[i]->HitUpdate();
			m_skillenemys[i]->Update();
		}

		for (int i = 0; i < m_skillenemys.size(); i++)
		{
			if (COMMONAPI.OutOfScreenPlusMargin(m_skillenemys[i]->GetPos(), m_skillenemys[i]->GetSize()) ||
				!m_skillenemys[i]->GetAlive())
			{
				EFFECTMANAGER.AddEffect(EffectType::Explosion, m_skillenemys[i]->GetPos());
				m_skillenemys.erase(m_skillenemys.begin() + i);

				i--;

				continue;
			}
		}
	}

	// ボス
	if (m_boss && !m_boss->GetAlive())
	{
		m_boss = nullptr;
	}

	// サブボス
	for (int i = 0; i < m_subbosss.size(); i++)
	{
		if (!m_subbosss[i]->GetAlive())
		{
			m_subbosss.erase(m_subbosss.begin() + i);
			i--;
		}
	}

	for (auto& e : m_addenemylist)
	{
		m_enemys.push_back(e);
	}

	m_addenemylist.clear();

	for (auto& e : m_addskillenemylist)
	{
		m_skillenemys.push_back(e);
	}

	m_addskillenemylist.clear();
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

void C_EnemyManager::ImGui()
{
	ImGui::Text("\nEnemyNum : %d", m_enemys.size());

	if (!m_enemys.empty())
	{
		for (int i = 0; i < m_enemys.size(); i++)
		{
			// テキスト表示
			ImGui::Text("EnemyHp : %d", m_enemys[i]->GetHp());
		}
	}

	if (!m_skillenemys.empty())
	{
		for (int i = 0; i < m_skillenemys.size(); i++)
		{
			// テキスト表示
			ImGui::Text("SkillEnemyHp : %d", m_skillenemys[i]->GetHp());
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
			m_addenemylist.emplace_back(std::make_shared<C_EnemyMove1>());
			m_addenemylist.back()->SetOwner(m_owner);
			m_addenemylist.back()->SetHitManager(m_hitmanager);
			m_addenemylist.back()->SetSkillManager(m_skillmanager);

			m_addenemylist.back()->SetTexandRectandAnimMax(&GetEnemyTexture(m_spworntype[judgmentcount].type),
				{ 64,64 }, { 0,0 });
			m_addenemylist.back()->SetEngineTex(&m_enemy1enginetex);
			m_addenemylist.back()->Init(m_spworntype[judgmentcount].pospattern, m_spworntype[judgmentcount].movepattern,
				m_player,i);

		
		}
		break;
	case EnemyMoveType::Type2:
		m_addenemylist.emplace_back(std::make_shared<C_EnemyMove2>());
		m_addenemylist.back()->SetOwner(m_owner);
		m_addenemylist.back()->SetHitManager(m_hitmanager);
		m_addenemylist.back()->SetSkillManager(m_skillmanager);
		
		m_addenemylist.back()->SetTexandRectandAnimMax(&GetEnemyTexture(m_spworntype[judgmentcount].type),{ 64,64 }, { 0,0 });
		m_addenemylist.back()->SetEngineTex(&m_enemy2enginetex);
		
		m_addenemylist.back()->Init(m_spworntype[judgmentcount].pospattern, m_spworntype[judgmentcount].movepattern,
			m_player, NULL);
		
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
		auto sb = std::make_shared<C_SubBoss>();
		sb->SetOwner(m_owner);
		sb->SetHitManager(m_hitmanager);
		sb->SetSkillManager(m_skillmanager);
		sb->SetTexandRectandAnimMax(&GetEnemyTexture(EnemyType::SubBoss), { 128,128 }, { NULL,NULL });
		sb->SetMoveTex(&m_subbossmovetex);
		sb->SetEngineTex(&m_subbossenginetex);
		sb->SetDeathTex(&m_subbossdeathtex);
		sb->SetId(i);
		sb->Init({ 700,(float)0 - 80 + 200 - (i * 400) });

		m_subbosss.push_back(sb);
		m_addenemylist.push_back(sb);
	}

	//ボス
	m_boss = std::make_shared<C_Boss>();
	m_boss->SetOwner(m_owner);
	m_boss->SetHitManager(m_hitmanager);
	m_boss->SetSkillManager(m_skillmanager);
	m_boss->SetTexandRectandAnimMax(&GetEnemyTexture(EnemyType::Boss),{ 128,128 }, { NULL,NULL });
	m_boss->SetMoveTex(&m_bossmovetex);
	m_boss->SetEngineTex(&m_bossenginetex);
	m_boss->SetDeathTex(&m_bossdeathtex);
	m_boss->Init();

	m_addenemylist.push_back(m_boss);
}

void C_EnemyManager::SkillEnemySpworn(Math::Vector2 pos,UseType type,EnemyMoveType movetype)
{
	switch (type)
	{
	case UseType::Player:
		for (int i = 0; i < 4; i++)
		{
			std::shared_ptr<C_EnemyMove3> e = std::make_shared<C_EnemyMove3>();
			e->SetOwner(m_owner);
			e->SetHitManager(m_hitmanager);
			e->SetTexandRectandAnimMax(&GetEnemyTexture(EnemyType::enemy3),
				{ 64,64 }, { 0,0 });
			e->SetEngineTex(&m_enemy3enginetex);

			e->Init(pos, type, i);

			m_addskillenemylist.emplace_back(e);
		}
		break;
	case UseType::Enemy:

		switch (movetype)
		{
		case EnemyMoveType::Type1:
		
				if (rand() % 2 == 0)
				{
					for (int i = 0; i < 3; i++)
					{
						//
						m_addenemylist.emplace_back(std::make_shared<C_EnemyMove1>());
						m_addenemylist.back()->SetOwner(m_owner);
						m_addenemylist.back()->SetHitManager(m_hitmanager);
						m_addenemylist.back()->SetSkillManager(m_skillmanager);

						m_addenemylist.back()->SetTexandRectandAnimMax(&GetEnemyTexture(EnemyType::enemy1),
							{ 64,64 }, { 0,0 });
						m_addenemylist.back()->SetEngineTex(&m_enemy1enginetex);

						m_addenemylist.back()->Init(PosPattern::Pattern1, MovePattern::Pattern1,
							m_player, i);

						//
						m_addenemylist.emplace_back(std::make_shared<C_EnemyMove1>());
						m_addenemylist.back()->SetOwner(m_owner);
						m_addenemylist.back()->SetHitManager(m_hitmanager);
						m_addenemylist.back()->SetSkillManager(m_skillmanager);

						m_addenemylist.back()->SetTexandRectandAnimMax(&GetEnemyTexture(EnemyType::enemy1),
							{ 64,64 }, { 0,0 });
						m_addenemylist.back()->SetEngineTex(&m_enemy1enginetex);


						m_addenemylist.back()->Init(PosPattern::Pattern2, MovePattern::Pattern1,
							m_player, i);
					}
				}
				else
				{
					for (int i = 0; i < 3; i++)
					{
						//
						m_addenemylist.emplace_back(std::make_shared<C_EnemyMove1>());
						m_addenemylist.back()->SetOwner(m_owner);
						m_addenemylist.back()->SetHitManager(m_hitmanager);
						m_addenemylist.back()->SetSkillManager(m_skillmanager);

						m_addenemylist.back()->SetTexandRectandAnimMax(&GetEnemyTexture(EnemyType::enemy1),
							{ 64,64 }, { 0,0 });
						m_addenemylist.back()->SetEngineTex(&m_enemy1enginetex);


						m_addenemylist.back()->Init(PosPattern::Pattern3, MovePattern::Pattern4,
							m_player, i);

						//
						m_addenemylist.emplace_back(std::make_shared<C_EnemyMove1>());
						m_addenemylist.back()->SetOwner(m_owner);
						m_addenemylist.back()->SetHitManager(m_hitmanager);
						m_addenemylist.back()->SetSkillManager(m_skillmanager);

						m_addenemylist.back()->SetTexandRectandAnimMax(&GetEnemyTexture(EnemyType::enemy1),
							{ 64,64 }, { 0,0 });
						m_addenemylist.back()->SetEngineTex(&m_enemy1enginetex);

						m_addenemylist.back()->Init(PosPattern::Pattern4, MovePattern::Pattern5,
							m_player, i);
					}
				}
			
			break;
		case EnemyMoveType::Type2:
			m_addenemylist.emplace_back(std::make_shared<C_EnemyMove2>());
			m_addenemylist.back()->SetOwner(m_owner);
			m_addenemylist.back()->SetHitManager(m_hitmanager);
			m_addenemylist.back()->SetSkillManager(m_skillmanager);

			m_addenemylist.back()->SetTexandRectandAnimMax(&GetEnemyTexture(EnemyType::enemy2),
				{ 64,64 }, { 0,0 });
			m_addenemylist.back()->SetEngineTex(&m_enemy2enginetex);

			m_addenemylist.back()->Init(PosPattern::Pattern1,MovePattern::Pattern1,
				m_player, NULL);
			//
			m_addenemylist.emplace_back(std::make_shared<C_EnemyMove2>());
			m_addenemylist.back()->SetOwner(m_owner);
			m_addenemylist.back()->SetHitManager(m_hitmanager);
			m_addenemylist.back()->SetSkillManager(m_skillmanager);

			m_addenemylist.back()->SetTexandRectandAnimMax(&GetEnemyTexture(EnemyType::enemy2),
				{ 64,64 }, { 0,0 });
				m_addenemylist.back()->SetEngineTex(&m_enemy2enginetex);

			m_addenemylist.back()->Init(PosPattern::Pattern2,MovePattern::Pattern2,
				m_player, NULL);

			break;
		case EnemyMoveType::Type3:
			for (int i = 0; i < 4; i++)
			{
				m_addenemylist.emplace_back(std::make_shared<C_EnemyMove3>());
				m_addenemylist.back()->SetOwner(m_owner);
				m_addenemylist.back()->SetHitManager(m_hitmanager);
				m_addenemylist.back()->SetSkillManager(m_skillmanager);

				m_addenemylist.back()->SetTexandRectandAnimMax(&GetEnemyTexture(EnemyType::enemy3),
					{ 64,64 }, { 0,0 });
				m_addenemylist.back()->SetEngineTex(&m_enemy3enginetex);

				m_addenemylist.back()->Init(pos, type, i);


			}
			break;
		default:
			break;
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
	case EnemyType::enemy1:
		return m_enemy1tex;
	case EnemyType::enemy2:
		return m_enemy2tex;
	case EnemyType::enemy3:
		return m_enemy3tex;
	case EnemyType::SubBoss:
		return m_subbosstex;
	case EnemyType::Boss:
		return m_bosstex;
	default:
		return m_enemytex;
		break;
	}
}
