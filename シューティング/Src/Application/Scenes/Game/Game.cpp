#include "Game.h"
#include"Application/Scenes/SceneManager.h"
#include"Application/Ui/ScenesUi/GameUi.h"
#include"../../Player/Player.h"
#include"Application/Enemy/EnemyManager.h"
#include"Application/Skill/SkillManager.h"
#include"Application/Skill/SkillBase.h"
#include"../../Hit/HitManager.h"

void C_Game::TextureLoad()
{
	m_gameui->TextureLoad();
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

	//当たり判定管理セット
	m_player->SetHitManager(m_hitmanager);
	m_enemymanager->SetHitManager(m_hitmanager);



	m_enemymanager->SetSkillManager(m_skillmanager);

	//初期化
	TextureLoad();

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


	//ボス生成用（仮）
	m_enemymanager->BossSpworn();
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

	/*if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		SceneManager->push(SceneType::Title, true);
	}*/
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


	//スキル描画（プレイヤーや敵の上に描画されるもの）
	m_skillmanager->TopDraw();


	//Ui「最後」
	m_gameui->Draw();
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
}
