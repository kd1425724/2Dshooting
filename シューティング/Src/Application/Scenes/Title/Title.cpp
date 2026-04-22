#include "Title.h"
#include"Application/Scenes/SceneManager.h"

void C_Title::TextureLoad()
{
	//テクスチャロード
	m_titleui.TextureLoad();
}

void C_Title::Release()
{

}

void C_Title::Init()
{
	//テクスチャロード
	TextureLoad();

	m_titleui.Init();

	//indexと何をするか入れる
	m_titleui.SetAction(START, [this]() {
		StartButtonProcess();
		});
}

void C_Title::Update()
{
	m_titleui.Update();

	//ボタン
	m_titleui.ClickableUi();
}

void C_Title::Draw()
{
	m_titleui.Draw();
}

void C_Title::StartButtonProcess()
{
	SCENEMANAGER.push(SceneType::Game, true);
}
