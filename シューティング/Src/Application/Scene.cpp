#include "main.h"
#include "Scene.h"
#include"Application/Info.h"
#include"Application/Ui/Feed.h"
#include"Application/Input/Input.h"

void Scene::Init()
{
	//フェード処理
	FEED.FeedInInit(30);

	//キー初期化
	Input.Init();
	
	//仮
	INFO.PlayerInfoSave();
}

void Scene::Update()
{
	//フェード処理
	FEED.Update();
	//シーン処理
	SCENEMANAGER.Update();

	Input.Update(APP.m_window.GetWndHandle());
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
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}
