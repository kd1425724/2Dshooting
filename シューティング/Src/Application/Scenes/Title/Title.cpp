#include "Title.h"
#include"Application/Scenes/SceneManager.h"
#include"../../Ui/ScenesUi/TitleUi.h"

void C_Title::Release()
{

}

void C_Title::Init()
{
	m_titleui = std::make_shared<C_TitleUi>();

	m_starttex = std::make_shared<KdTexture>();
	m_starttex->Load("Texture/Ui/Font/PRESSENTERTOSTART.png");

	m_titleui->SetStartTex(m_starttex);

	m_titleui->Init();
}

void C_Title::Update()
{
	m_titleui->Update();

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SCENEMANAGER.push(SceneType::Game, true);
	}

}

void C_Title::Draw()
{
	m_titleui->Draw();
}