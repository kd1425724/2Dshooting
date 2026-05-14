#include "GamePause.h"
#include"../../Ui/ScenesUi/GamePauseUi.h"
#include"../../Input/Input.h"
#include"../SceneManager.h"
void C_GamePause::Init()
{
	m_gamepauseui = std::make_shared<C_GamePauseUi>();

	m_gamepauseui->Init();
}

void C_GamePause::Update()
{
	m_gamepauseui->Update();

	if (Input.GetUserKey(UserKeyType::ESCAPE) && !Input.GetUserKeyFlg(UserKeyType::ESCAPE))
	{
		SCENEMANAGER.pop();
		return;
	}
}

void C_GamePause::Draw()
{
	m_gamepauseui->BackGroundDraw();
	m_gamepauseui->Draw();
}

void C_GamePause::Release()
{
	m_gamepauseui.reset();
}