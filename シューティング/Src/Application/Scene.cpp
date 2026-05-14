#include "main.h"
#include "Scene.h"
#include"Application/Info.h"
#include"Application/Ui/Feed.h"
#include"Application/Input/Input.h"
#include"Effect/EffectManager.h"
#include"Sound/Sound.h"

void Scene::Init()
{
	//AUDIO.Init();

	SOUND.Init();

	//マウス消去
	ShowCursor(false);

	//フェード処理
	FEED.FeedInInit(30);

	EFFECTMANAGER.Init();

	//キー初期化
	Input.Init();
	
	//仮
	INFO.PlayerInfoSave();

	SCENEMANAGER.Init();
}

void Scene::Update()
{
	//フェード処理
	FEED.Update();
	//シーン処理
	SCENEMANAGER.Update();

	Input.Update(APP.m_window.GetWndHandle());

	SOUND.Update();
}

void Scene::Draw2D()
{
	//シーン処理
	SCENEMANAGER.Draw();
	//フェード処理
	FEED.Draw();
}

void Scene::Release()
{
}
void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 600), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);

		SCENEMANAGER.ImGui();
	}
	ImGui::End();
}
