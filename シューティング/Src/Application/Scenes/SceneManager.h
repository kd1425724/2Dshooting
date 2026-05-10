#pragma once
#include"SceneBase.h"

enum class SceneType
{
	Title,	//タイトル
	Game,	//ゲーム
	GamePause,	//ゲーム一時停止
	Result	//リザルト
};

struct Score
{
	//スコア保存用
	//クリア
	bool clear = false;
	//スコア
	int score = 0;
	//残機
	int playerlife = 0;
	//時間
	int time = 0;
};


class C_SceneManager
{
public:
	~C_SceneManager();

	void Init();
	void Update();
	void Draw();

	void ImGui();

	//指定したシーンを上に被せる
	//popflg...push時popするかどうか
	void push(SceneType type, bool popflg, bool Allpopflg=false);
	void NoFeedpush(SceneType type, bool popflg, bool Allpopflg = false);
	//今のシーンを終了
	void pop();

	//指定したシーンを作る
	//push関数で使ってる
	std::shared_ptr<C_SceneBase> CreateScene(SceneType type);

	void SetScoreData(std::shared_ptr<Score> data){m_scoredata = data;}

	std::shared_ptr<Score> GetScoreData(){return m_scoredata;}

	void SetScore(int value);

	int GetScore() { return m_score; }

	void ResetScoreData() { m_scoredata = std::make_shared<Score>(); m_score = 0; }

private:

	std::vector<std::shared_ptr<C_SceneBase>> scenes;

	std::shared_ptr<Score> m_scoredata = nullptr;

	//スコア用
	int m_score = 0;

//シングルトン
private:
	
	C_SceneManager()
	{
	
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
