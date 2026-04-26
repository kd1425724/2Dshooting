#pragma once
#include<vector>

using namespace std;

class C_EnemyMoveBase;
class C_SkillManager;

enum class PosPattern;
enum class MovePattern;
enum class UseType;

enum class EnemyType
{
	s,
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

	//スキル管理取得用
	void SetSkillManager(std::shared_ptr<C_SkillManager> skillmanager) { m_skillmanager = skillmanager; }

	//敵生成
	void EnemySpworn(int judgmentcount);

	//ボス生成
	void BossSpworn();

	//スキル敵生成用
	void SkillEnemySpworn(Math::Vector2 pos,UseType type);

private:

	//解放処理
	void Release();

	//判定回数
	static const int JudgmentNum = 5;// 120 / 5 * 10;
	
	//保存用
	Enemy m_spworntype[JudgmentNum];

	void SpwornEnemyLoad();

	//インスタンス取得用
	std::shared_ptr<C_Player> m_player;

	//敵まとめ
	vector<std::shared_ptr<C_EnemyMoveBase>> m_enemys;

	//スキル用
	vector<std::shared_ptr<C_EnemyMoveBase>> m_skillenemys;

	std::shared_ptr<C_SkillManager> m_skillmanager;

	//敵画像セット
	KdTexture& GetEnemyTexture(EnemyType type);
	//画像セット用
	KdTexture m_enemytex;

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

