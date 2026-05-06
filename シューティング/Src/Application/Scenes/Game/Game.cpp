#include "Game.h"
#include"Application/Scenes/SceneManager.h"
#include"Application/Ui/ScenesUi/GameUi.h"
#include"../../Player/Player.h"
#include"Application/Enemy/EnemyManager.h"
#include"Application/Skill/SkillManager.h"
#include"Application/Skill/SkillBase.h"
#include"../../Hit/HitManager.h"
#include"../../Effect/EffectManager.h"

std::shared_ptr<C_Boss> C_Game::GetBoss()
{
	return m_enemymanager->GetBoss();
}

std::vector<std::shared_ptr<C_SubBoss>> C_Game::GetSubBoss()
{
	return m_enemymanager->GetSubBoss();
}

void C_Game::Init()
{
	EFFECTMANAGER.Init();

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
	std::shared_ptr<KdTexture> playerenginetex = std::make_shared<KdTexture>();
	playerenginetex->Load("Texture/Player/PlayerEngine_01.png");
	m_playerenginetexs.push_back(playerenginetex);
	playerenginetex = std::make_shared<KdTexture>();
	playerenginetex->Load("Texture/Player/PlayerEngine_02.png");
	m_playerenginetexs.push_back(playerenginetex);
	playerenginetex = std::make_shared<KdTexture>();
	playerenginetex->Load("Texture/Player/PlayerEngine_03.png");
	m_playerenginetexs.push_back(playerenginetex);

	m_player->SetEngineTex(m_playerenginetexs);

	//スコア表示
	std::shared_ptr<KdTexture> scoretex = std::make_shared<KdTexture>();
	scoretex->Load("Texture/Ui/Font/SCORE.png");
	m_gameui->SetScoreTex(scoretex);

	//スキル
	std::shared_ptr<KdTexture> skilltex = std::make_shared<KdTexture>();
	skilltex->Load("Texture/Ui/Font/SKILL.png");
	m_gameui->SetSkillTex(skilltex);

	//LIFE
	std::shared_ptr<KdTexture> lifetex = std::make_shared<KdTexture>();
	lifetex->Load("Texture/Ui/Font/LIFE.png");
	m_gameui->SetLifeTex(lifetex);

	//Hpバー
	std::shared_ptr<KdTexture> hpbartex = std::make_shared<KdTexture>();
	hpbartex->Load("Texture/Ui/HUD/HPBar.png");
	m_gameui->SetHpBarTex(hpbartex);
	//枠
	std::shared_ptr<KdTexture> hpbarframetex = std::make_shared<KdTexture>();
	hpbarframetex->Load("Texture/Ui/HUD/HPBarFrame.png");
	m_gameui->SetHpBarFrameTex(hpbarframetex);

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



}

void C_Game::Update()
{
	

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
	
	if (m_JudgmentTime >= 0)
	{
		m_JudgmentTime--;
		if (m_JudgmentTime < 0)
		{
			//5秒分セット
			m_JudgmentTime = m_JudgmentCoolTime;

			//5秒ごとに敵生成
			//SpwornMnager();
		}
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SCENEMANAGER.push(SceneType::Result, true);
	}
}

void C_Game::Draw()
{
	//背景「最初」
	m_gameui->BackGroundDraw();

	//スキル描画
	m_skillmanager->Draw();

	//敵描画
	m_enemymanager->Draw();

	//プレイヤー描画
	m_player->Draw();

	//エフェクト描画
	EFFECTMANAGER.Draw();

	//スキル描画（プレイヤーや敵の上に描画されるもの）
	m_skillmanager->TopDraw();

	//当たり判定描画
	m_hitmanager->Draw();


	//Ui「最後」
	m_gameui->Draw();
}

void C_Game::ImGui()
{
	m_hitmanager->ImGui();

	m_player->ImGui();

	m_enemymanager->ImGui();

	
}

void C_Game::SpwornMnager()
{
	//一度に10回敵生成を行う
	for (int i = 0; i < OnecountNum; i++)
	{
		m_enemymanager->EnemySpworn(m_JudgmenCount);
		//呼び出されるたびに＋１
		m_JudgmenCount++;
	}
}


void C_Game::Release()
{
	EFFECTMANAGER.Release();
}
