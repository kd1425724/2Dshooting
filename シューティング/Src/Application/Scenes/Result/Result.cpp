#include "Result.h"
#include"../SceneManager.h"
#include"../../Ui/ScenesUi/ResultUi.h"
#include"../../Common/CommonAPI.h"

void C_Result::Init()
{
	m_resultui = std::make_shared<C_ResultUi>();

	m_resultui->Init();
}

void C_Result::Update()
{
	m_resultui->Update();

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SCENEMANAGER.push(SceneType::Title, true);
	}
}

void C_Result::Draw()
{
	m_resultui->Draw();

	COMMONAPI.NumDraw(1234567890, { 600,0 }, { 0.5f,0.5f });
}

void C_Result::Release()
{
}
