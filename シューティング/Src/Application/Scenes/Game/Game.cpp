#include "Game.h"
#include"Application/Scenes/SceneManager.h"
#include"Application/Ui/ScenesUi/GameUi.h"
#include"Application/Prayer/Player.h"
#include"Application/Enemy/EnemyManager.h"

void C_Game::TextureLoad()
{
	m_gameui->TextureLoad();
}

void C_Game::Init()
{
	m_gameui = new C_GameUi();

	m_player = new C_Player();

	m_enemymanager = new C_EnemyManager();

	TextureLoad();

	m_gameui->Init();

	m_player->Init();

	m_enemymanager->Init(m_player);

	//”»’èŠÔ
	m_JudgmentTime = 0;
	//”»’è‰½‰ñ–Ú‚©ƒJƒEƒ“ƒg
	m_JudgmenCount = 0;
}

void C_Game::Update()
{
	//ƒvƒŒƒCƒ„[
	m_player->Update();

	//“G
	m_enemymanager->Update();

	//Ui
	m_gameui->Update();

	if (m_JudgmentTime >= 0)
	{
		m_JudgmentTime--;
		if (m_JudgmentTime < 0)
		{
			//5•b•ªƒZƒbƒg
			m_JudgmentTime = m_JudgmentCoolTime;

			//5•b‚²‚Æ‚É“G¶¬
			SpwornMnager();
		}
	}

	/*if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		SceneManager->push(SceneType::Title, true);
	}*/
}

void C_Game::Draw()
{
	//”wŒiuÅ‰v
	m_gameui->BackGroundDraw();


	//“G•`‰æ
	m_enemymanager->Draw();

	//ƒvƒŒƒCƒ„[•`‰æ
	m_player->Draw();


	//UiuÅŒãv
	m_gameui->Draw();
}

void C_Game::SpwornMnager()
{
	//ˆê“x‚É10‰ñ“G¶¬‚ğs‚¤
	for (int i = 0; i < OnecountNum; i++)
	{
		m_enemymanager->EnemySpworn(m_JudgmenCount);
		//ŒÄ‚Ño‚³‚ê‚é‚½‚Ñ‚É{‚P
		m_JudgmenCount++;
	}
}


void C_Game::Release()
{
	if (m_player)
	{
		delete m_player;
		m_player = nullptr;
	}

	if (m_enemymanager)
	{
		delete m_enemymanager;
		m_enemymanager = nullptr;
	}

	if (m_gameui)
	{
		delete m_gameui;
		m_gameui = nullptr;
	}
}
