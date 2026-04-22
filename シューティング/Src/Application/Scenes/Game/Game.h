#pragma once
#include"Application/Scenes/SceneBase.h"

class C_GameUi;
class C_Player;
class C_EnemyManager;

enum class GameMode
{
	Stage1,
	Stage2,
};

class C_Game:public C_SceneBase
{
public:
	C_Game() { Release(); }
	~C_Game(){}

	void Init()override;
	void Update()override;
	void Draw()override;



private:

	//一回の呼出し回数
	static const int OnecountNum = 10;
	//敵スポーン判定時間
	int m_JudgmentTime;
	//この値ごとに判定（5秒に一回）
	static const int m_JudgmentCoolTime = 60 * 5;
	//判定何回目かカウント
	int m_JudgmenCount;

	void SpwornMnager();

	//画像ロード
	void TextureLoad()override;

	//解放処理
	void Release()override;

	//Ui
	C_GameUi* m_gameui=nullptr;

	//プレイヤー
	C_Player* m_player=nullptr;

	//敵
	C_EnemyManager* m_enemymanager=nullptr;

};