#pragma once
#include"Application/Scenes/SceneBase.h"

class C_GameUi;
class C_Player;
class C_EnemyManager;
class C_SkillManager;
class C_HitManager;
class C_Boss;
class C_SubBoss;
class C_Shot;

enum class GameMode
{
	Stage1,
	Stage2,
};

class C_Game:public C_SceneBase, public std::enable_shared_from_this<C_Game>
{
public:
	C_Game() { Release(); }
	~C_Game()override{}

	void Init()override;
	void Update()override;
	void Draw()override;

	void ImGui()override;

	//プレイヤーゲッター
	std::shared_ptr<C_Player> GetPlayer() { return m_player; }

	//ボスゲッター
	std::shared_ptr<C_Boss> GetBoss();
	//サブボスゲッター
	std::vector<std::shared_ptr<C_SubBoss>> C_Game::GetSubBoss();

	void SetShot(std::shared_ptr<C_Shot> shot) { m_shot.push_back(shot); }

private:

	//時間カウント
	float m_time = 0;

	//一回の呼出し回数
	static const int OnecountNum = 10;
	//敵スポーン判定時間
	int m_JudgmentTime;
	//この値ごとに判定（5秒に一回）
	static const int m_JudgmentCoolTime = 60 * 5;
	//判定何回目かカウント
	int m_JudgmenCount;

	void SpwornMnager();

	//解放処理
	void Release()override;

	//弾
	std::vector<std::shared_ptr<C_Shot>> m_shot;

	//Ui
	std::shared_ptr<C_GameUi> m_gameui=nullptr;

	//プレイヤー
	std::shared_ptr<C_Player> m_player = nullptr;

	//敵
	std::shared_ptr<C_EnemyManager> m_enemymanager=nullptr;

	//スキル管理
	std::shared_ptr<C_SkillManager> m_skillmanager = nullptr;

	//当たり判定管理
	std::shared_ptr<C_HitManager> m_hitmanager = nullptr;

	////////
	//テクスチャ
	////////

	//プレイヤーエンジン
	std::vector<std::shared_ptr<KdTexture>> m_playerenginetexs;

};