#include "EnemyManager.h"
#include"Application/Enemy/EnemyMove/EnemyMove1.h"

void C_EnemyManager::Init(C_Player* player)
{
	m_player = player;

	SpwornEnemyLoad();
}
void C_EnemyManager::Release()
{
	if (m_player)
	{
		delete m_player;
		m_player = nullptr;
	}

	if (&m_enemys)
	{
		delete &m_enemys;
		m_player = nullptr;
	}
}

void C_EnemyManager::SpwornEnemyLoad()
{
	FILE* fp;

	if (fopen_s(&fp, "Data/EnemyData/StageEnemyData.csv", "r") == 0)
	{
		char dummy[255];

		int setenemytype[JudgmentNum] = {};
		int setmovepattern[JudgmentNum] = {};
		int setdefault[JudgmentNum] = {};

		fgets(dummy, 255, fp);				//1行飛ばす

		for (int i = 0; i < JudgmentNum; i++)
		{
			fscanf_s(fp, "%*[^,],%*[^,],%d,%d,%d",&setenemytype[i],&setmovepattern[i],&setdefault[i]);

			switch (setenemytype[i])
			{
			case 1:
				m_spworntype[i].type = EnemyType::s;
				break;
			default:
				break;
			}

			switch (setmovepattern[i])
			{
			case 1:
				m_spworntype[i].movepattern = EnemyMovePattern::Pattern1;
				break;
			case 2:
				m_spworntype[i].movepattern = EnemyMovePattern::Pattern2;
				break;
				
			default:
				break;
			}

			switch (setdefault[i])
			{
			case 1:
				m_spworntype[i].Default = MovePatternDefault::p1Default1_Right;
				break;
			case 2:
				m_spworntype[i].Default = MovePatternDefault::p1Default2_Left;
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

Math::Vector2 C_EnemyManager::GetEnemyPos(MovePatternDefault enemypostype,int i)
{
	switch (enemypostype)
	{
	case MovePatternDefault::p1Default1_Right:
		return { 200,(float)(i * 60) + 400 };
		break;
	case MovePatternDefault::p1Default2_Left:
		return { -200,(float)(i * 60) + 400 };
		break;
	case MovePatternDefault::p2Default1:
		break;
	case MovePatternDefault::p2Default2:
		break;
	default:
		break;
	}
}

void C_EnemyManager::Update()
{
	if (!m_enemys.empty())
	{
		for (int i = 0; i < m_enemys.size(); i++)
		{
			m_enemys[i]->Update();
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
}
void C_EnemyManager::EnemySpworn(int judgmentcount)
{
	switch (m_spworntype[judgmentcount].movepattern)
	{
	case EnemyMovePattern::Pattern1:
		for (int i = 0; i < 3; i++)
		{
			m_enemys.emplace_back(new C_EnemyMove1());
			m_enemys.back()->Init(&GetEnemyTexture(m_spworntype[judgmentcount].type), { 64,64 }, { 0,0 }, GetEnemyPos(m_spworntype[judgmentcount].Default, i),m_spworntype[judgmentcount].Default,m_player);
		}
		break;
	case EnemyMovePattern::Pattern2:
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
		m_enemytex.Load("Texture/Enemy/Fighter.png");
		break;
	default:
		break;
	}

	return m_enemytex;
}
