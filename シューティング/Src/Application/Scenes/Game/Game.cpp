#include "Game.h"
#include"Application/Scenes/SceneManager.h"

void C_Game::TextureLoad()
{
	m_gameui.TextureLoad();
}

void C_Game::Init()
{
	TextureLoad();

	m_gameui.Init();

	m_player.Init();
}

void C_Game::Update()
{
	m_gameui.Update();

	m_player.Update();

	/*if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		SceneManager.push(SceneType::Title, true);
	}*/
}

void C_Game::Draw()
{
	m_gameui.Draw();

	m_player.Draw();
}
