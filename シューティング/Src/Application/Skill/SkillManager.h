#pragma once

enum class SkillType
{
	None,			//なし
	CopyShot,		//コピー
	EnemyGenerate,	//敵生成
	Barrier,		//バリア
	Laser,			//レーザー
};

class C_EnemyGenerate;
class C_SkillBase;
class C_EnemyManager;
class C_Player;
class C_EnemyMoveBase;
class C_HitManager;
class C_GameUi;

class C_SkillManager
{
public:
	C_SkillManager() {}
	~C_SkillManager() {}

	void Init();
	void Update();
	void Draw();
	void TopDraw();
	void MidDraw();

	void Release();

	//プレイヤースキルセット用
	void SetPlayerSkill(SkillType skilltype);

	//敵管理取得用
	void SetEnemyManager(std::shared_ptr<C_EnemyManager> manager)
	{
		m_enemymanager = manager;
	}

	//敵スキル発動用
	void SetEnemySkill(
		SkillType skilltype,
		std::shared_ptr<C_EnemyMoveBase> enemybase
	);

	void SetPlayer(std::shared_ptr<C_Player> player)
	{
		m_player = player;
	}

	//当たり判定用
	void SetHitManager(std::shared_ptr<C_HitManager> hitmanager)
	{
		m_hitmanager = hitmanager;
	}

	//モザイク用
	void SetGameUi(std::shared_ptr<C_GameUi> gameui)
	{
		m_gameui = gameui;
	}

	bool GetPlayerSkillFlg();

private:

	//プレイヤースキルまとめ
	std::shared_ptr<C_SkillBase> m_playerskills = nullptr;

	//敵スキルまとめ
	std::vector<std::shared_ptr<C_SkillBase>> m_enemyskills;
	std::vector<std::shared_ptr<C_SkillBase>> m_addenemyskill;
	
	//敵管理取得用
	std::weak_ptr<C_EnemyManager> m_enemymanager;

	//敵用
	std::weak_ptr<C_EnemyMoveBase> m_enemys;

	//プレイヤーインスタンス取得用
	std::weak_ptr<C_Player> m_player;

	//当たり判定
	std::weak_ptr<C_HitManager> m_hitmanager;

	//ゲームUi
	std::weak_ptr<C_GameUi> m_gameui;

	//画像読み込み用（本体）

	//レーザー
	std::shared_ptr<KdTexture> m_lasertex = nullptr;

	//スキル
	std::shared_ptr<KdTexture> m_barriertex = nullptr;
};