#pragma once
#include<vector>

class C_EnemyMoveBase;
class C_SkillManager;
class C_HitManager;

enum class PosPattern;
enum class MovePattern;
enum class UseType;

class C_Boss;
class C_SubBoss;

class C_Game;

enum class EnemyType
{
	enemy3,
	SubBoss,
	Boss
};
enum class EnemyMoveType
{
	Type1,
	Type2,
	Type3
};

struct Enemy
{
	EnemyType type;
	EnemyMoveType movetype;
	PosPattern pospattern;
	MovePattern movepattern;
};


class C_Player;

class C_EnemyManager
{
public:
	C_EnemyManager() {}
	~C_EnemyManager() { Release(); }

	void Init(std::shared_ptr<C_Player> player);
	void Update();
	void Draw();

	void ImGui();

	//スキル管理取得用
	void SetSkillManager(std::shared_ptr<C_SkillManager> skillmanager) { m_skillmanager = skillmanager; }

	//敵生成
	void EnemySpworn(int judgmentcount);

	//ボス生成
	void BossSpworn();

	//スキル敵生成用
	void SkillEnemySpworn(Math::Vector2 pos, UseType type, EnemyMoveType movetype = EnemyMoveType::Type3);

	//当たり判定管理セット
	void SetHitManager(std::shared_ptr<C_HitManager> hitmanager) { m_hitmanager = hitmanager; }

	//ボスゲッター
	std::shared_ptr<C_Boss> GetBoss() { return m_boss; }

	//サブボスゲッター
	std::vector<std::shared_ptr<C_SubBoss>> GetSubBoss() { return m_subbosss; }

	void SetOwner(std::shared_ptr<C_Game> owner) { m_owner = owner; }

private:

	//オーナー
	std::weak_ptr<C_Game> m_owner;

	//解放処理
	void Release();

	//判定回数
	static const int JudgmentNum = 5;// 120 / 5 * 10;
	
	//保存用
	Enemy m_spworntype[JudgmentNum];

	void SpwornEnemyLoad();

	//インスタンス取得用
	std::shared_ptr<C_Player> m_player=nullptr;

	//敵まとめ
	std::vector<std::shared_ptr<C_EnemyMoveBase>> m_enemys;
	//ボス
	std::shared_ptr<C_Boss> m_boss;
	//サブボス
	std::vector<std::shared_ptr<C_SubBoss>> m_subbosss;

	//スキル用
	std::vector<std::shared_ptr<C_EnemyMoveBase>> m_skillenemys;

	//スキル管理用
	std::shared_ptr<C_SkillManager> m_skillmanager = nullptr;

	//当たり判定管理用
	std::shared_ptr<C_HitManager> m_hitmanager = nullptr;

	//敵画像セット
	KdTexture& GetEnemyTexture(EnemyType type);
	//画像セット用
	KdTexture m_enemytex;

	//敵３用
	KdTexture m_enemy3tex;
	KdTexture m_enemy3movetex;
	KdTexture m_enemy3enginetex;
	KdTexture m_enemy3deathtex;

	//サブボス用
	KdTexture m_subbosstex;
	KdTexture m_subbossmovetex;
	KdTexture m_subbossenginetex;
	KdTexture m_subbossdeathtex;


	//ボス用
	KdTexture m_bosstex;
	KdTexture m_bossmovetex;
	KdTexture m_bossenginetex;
	KdTexture m_bossdeathtex;
};

