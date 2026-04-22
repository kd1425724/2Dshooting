#pragma once
#include<stack>
#include<memory>
#include"SceneBase.h"

using namespace std;

enum class SceneType
{
	Title,	//タイトル
	Game,	//ゲーム
	Result	//リザルト
};

class C_SceneManager
{
public:
	~C_SceneManager();

	void Update();
	void Draw();

	//指定したシーンを上に被せる
	//popflg...push時popするかどうか
	void push(SceneType type,bool popflg);
	//今のシーンを終了
	void pop();

	//指定したシーンを作る
	//push関数で使ってる
	unique_ptr<C_SceneBase> CreateScene(SceneType type);

private:

	stack<unique_ptr<C_SceneBase>> scenes;

	


//シングルトン
private:
	
	C_SceneManager() 
	{
		scenes.push(CreateScene(SceneType::Game));
		scenes.top()->Init();
	}

public:
	
	static C_SceneManager& GetInstans()
	{
		static C_SceneManager instans;
		return instans;
	}
};
//シーン管理
#define SCENEMANAGER C_SceneManager::GetInstans()
