#include "Title.h"
#include"Application/Scenes/SceneManager.h"
#include"../../Ui/ScenesUi/TitleUi.h"
#include"../../main.h"
#include"../../Input/Input.h"

void C_Title::Release()
{
	m_starttex->Release();
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

	if (Input.GetUserKey(UserKeyType::ENTER) && !Input.GetUserKeyFlg(UserKeyType::ENTER))
	{
		SCENEMANAGER.push(SceneType::Game, true);
		return;
	}

	if (Input.GetUserKey(UserKeyType::ESCAPE) && !Input.GetUserKeyFlg(UserKeyType::ESCAPE))
	{
		APP.End();
		return;
	}

}

void C_Title::Draw()
{
	m_titleui->Draw();
}