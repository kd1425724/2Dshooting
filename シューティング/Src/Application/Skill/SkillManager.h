#pragma once

enum class SkillType
{
	None,			//なし
	CopyShot,		//コピー
	EnemyGenerate,	//敵生成
	Barrier,		//バリア
	Laser,		//レーザー
};
class C_EnemyGenerate;
class C_SkillBase;
class C_EnemyManager;
class C_Player;
class C_EnemyMoveBase;

class C_SkillManager
{
public:
	C_SkillManager(){}
	~C_SkillManager(){}

	void Init();
	void Update();
	void Draw();
	void TopDraw();

	//プレイヤースキルセット用
	void SetPlayerSkill(SkillType skilltype);

	//敵管理取得用
	void SetEnemyManager(std::shared_ptr<C_EnemyManager> manager) { m_enemymanager = manager; }
	//敵スキル発動用
	void SetUseSkill(SkillType skilltype, std::shared_ptr<C_EnemyMoveBase> enemybase);

	void SetPlayer(std::shared_ptr<C_Player> player) { m_player = player; }

private:

	//プレイヤースキルまとめ
	std::shared_ptr<C_SkillBase> m_playerskills = nullptr;

	//敵スキルまとめ
	std::vector<std::shared_ptr<C_SkillBase>> m_enemyskills;

	//敵管理取得用
	std::shared_ptr<C_EnemyManager> m_enemymanager=nullptr;

	//敵用
	std::shared_ptr<C_EnemyMoveBase> m_enemys=nullptr;

	//プレイヤーインスタンス取得用
	std::shared_ptr<C_Player> m_player=nullptr;

	//画像読み込み用
	//レーザー
	std::shared_ptr<KdTexture> m_lasertex;
	//スキル
	std::shared_ptr<KdTexture> m_barriertex;
};
