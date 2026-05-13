#include "Game.h"
#include"Application/Scenes/SceneManager.h"
#include"Application/Ui/ScenesUi/GameUi.h"
#include"../../Player/Player.h"
#include"Application/Enemy/EnemyManager.h"
#include"Application/Skill/SkillManager.h"
#include"Application/Skill/SkillBase.h"
#include"../../Hit/HitManager.h"
#include"../../Effect/EffectManager.h"
#include"../../Skill/Shot/Shot.h"
#include"../../Enemy/Boss/Boss/Boss.h"
#include"../../Input/Input.h"
#include"../../Info.h"
#include"../../Common/CommonTexture.h"

std::shared_ptr<C_Boss> C_Game::GetBoss()
{
	return m_enemymanager->GetBoss();
}

std::vector<std::shared_ptr<C_SubBoss>> C_Game::GetSubBoss()
{
	return m_enemymanager->GetSubBoss();
}

void C_Game::ResultPush()
{
	auto s = std::make_shared<Score>();
	if (s)
	{
		if (!m_enemymanager->GetBoss())
		{
			s->clear = true;
		}
		else
		{
			s->clear = false;
		}
		s->playerlife = m_player->GetHp();
		s->score = SCENEMANAGER.GetScore();
		s->time = (int)m_time;

		SCENEMANAGER.SetScoreData(s);
	}

	SCENEMANAGER.push(SceneType::Result, true);
	return;
}

void C_Game::Init()
{
	//Ui
	m_gameui =std::make_shared<C_GameUi>();

	//プレイヤー
	m_player = std::make_shared<C_Player>();

	//敵管理
	m_enemymanager = std::make_shared<C_EnemyManager>();

	//スキル管理作成
	m_skillmanager = std::make_shared<C_SkillManager>();

	//当たり判定管理
	m_hitmanager = std::make_shared<C_HitManager>();

	//オーナーセット
	m_gameui->SetOwner(shared_from_this());
	m_enemymanager->SetOwner(shared_from_this());
	m_player->SetOwner(shared_from_this());
	m_skillmanager->SetOwner(shared_from_this());

	//スキル管理取得
	m_hitmanager->SetSkillManager(m_skillmanager);
	m_enemymanager->SetSkillManager(m_skillmanager);

	//当たり判定管理セット
	m_player->SetHitManager(m_hitmanager);
	m_enemymanager->SetHitManager(m_hitmanager);
	m_skillmanager->SetHitManager(m_hitmanager);

	//ゲームUiセット
	m_skillmanager->SetGameUi(m_gameui);

	//プレイヤーエンジン
	m_player->SetEngineTex(CommonTex.GetPlayerEnginetex());

	//ボス生成用（仮）
	m_enemymanager->BossSpworn();

	m_gameui->Init();

	m_player->Init();

	m_enemymanager->Init(m_player);

	m_skillmanager->SetEnemyManager(m_enemymanager);
	m_skillmanager->SetPlayer(m_player);
	m_skillmanager->Init();

	//判定時間
	m_JudgmentTime = 0;
	//判定何回目かカウント
	m_JudgmenCount = 0;

	m_gamestartdirectiontime = GameStartDirectionTime;

	m_gamestartpattern = GameStartPattern::GameStartDirection;

	m_startflg = false;
	m_startscale = { 5,5 };
}

void C_Game::Update()
{

	switch (m_gamemode)
	{
	case GameMode::Start:
		switch (m_gamestartpattern)
		{
		case GameStartPattern::GameStartDirection:
			m_gamestartdirectiontime--;
			if (m_gamestartdirectiontime <= 0)
			{
				m_gamestartpattern = GameStartPattern::StartDirection;
				m_startflg = true;
			}
			break;
		case GameStartPattern::StartDirection:
			m_startscale *= 0.85f;
			if (m_startscale.x <= 1.0f)
			{
				m_startscale = { 1,1 };
				m_startalpha -= 0.02f;
				if (m_startalpha <= 0.3f)
				{
					m_startflg = false;
					m_gamestartpattern = GameStartPattern::GameStart;
				}
			}
			
			break;
		case GameStartPattern::GameStart:
			m_gamemode = GameMode::Loop;
			break;
		default:
			break;
		}

		m_player->StartUpdate();
		//敵
		m_enemymanager->StartUpdate();
		//スキル管理
		m_skillmanager->Update();
		EFFECTMANAGER.Update();

		//Ui
		m_gameui->Update();

		//当たり判定管理
		m_hitmanager->Update();

		break;
	case GameMode::Loop:
		//時間
		m_time += 1.0f / 60.0f;

		//弾
		for (auto& s : m_shot)
		{
			s->Update();
		}

		//プレイヤー
		m_player->Update();

		//敵
		m_enemymanager->Update();

		//スキル管理
		m_skillmanager->Update();

		//Ui
		m_gameui->Update();

		//当たり判定管理
		m_hitmanager->Update();

		EFFECTMANAGER.Update();

		//if (m_JudgmentTime >= 0)
		//{
		//	m_JudgmentTime--;
		//	if (m_JudgmentTime < 0)
		//	{
		//		//5秒分セット
		//		m_JudgmentTime = m_JudgmentCoolTime;
		//	}
		//}

		break;
	default:
		break;
	}
	


	if (Input.GetUserKey(UserKeyType::ESCAPE) && !Input.GetUserKeyFlg(UserKeyType::ESCAPE))
	{
		SCENEMANAGER.NoFeedpush(SceneType::GamePause,false);
		return;
	}

	if (!m_player ||
		!m_enemymanager ||
		!m_player->GetAlive() ||
		!m_enemymanager->GetBoss())
	{
		ResultPush();
		return;
	}

	if (Input.GetDebugKey(DebugKeyType::Ukey) && !Input.GetDebugKeyFlg(DebugKeyType::Ukey))
	{
		ResultPush();
		return;
	}
}

void C_Game::Draw()
{

	//背景「最初」
	m_gameui->BackGroundDraw();

	EFFECTMANAGER.IsBottomDraw();

	//弾描画
	for (auto& it : m_shot)
	{
		it->Draw();
	}

	//スキル描画
	m_skillmanager->Draw();

	//プレイヤー描画
	m_player->Draw();

	m_skillmanager->MidDraw();

	//敵描画
	m_enemymanager->Draw();

	
	//スキル描画（プレイヤーや敵の上に描画されるもの）
	m_skillmanager->TopDraw();

	//当たり判定描画
	m_hitmanager->Draw();

	//エフェクト描画
	EFFECTMANAGER.Draw();

	//最後
	//Ui
	m_gameui->Draw();

	EFFECTMANAGER.IsTopDraw();

	if (m_startflg)
	{
		Math::Matrix s = Math::Matrix::CreateScale(m_startscale.x, m_startscale.y, 1);
		Math::Matrix t = Math::Matrix::CreateTranslation(0,-INFO.HUDAreaHeight / 2, 0);
		Math::Matrix mat = s * t;

		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
		Math::Rectangle rect = { 0,0,480,100 };
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(&CommonTex.GetSTARTTEXTtex(), rect, m_startalpha);
	}
}

void C_Game::ImGui()
{
	m_hitmanager->ImGui();

	m_player->ImGui();

	m_enemymanager->ImGui();

	
}

//void C_Game::SpwornMnager()
//{
//	//一度に10回敵生成を行う
//	for (int i = 0; i < OnecountNum; i++)
//	{
//		m_enemymanager->EnemySpworn(m_JudgmenCount);
//		//呼び出されるたびに＋１
//		m_JudgmenCount++;
//	}
//}


void C_Game::Release()
{
	EFFECTMANAGER.Release();
}
