#pragma once
#include<vector>

using namespace std;

class C_EnemyMoveBase;

enum class EnemyType
{
	s,
};

enum class EnemyMovePattern
{
	Pattern1,
	Pattern2
};

enum class MovePatternDefault
{
	p1Default1_Right,
	p1Default2_Left,
	p1Default3_Left,
	p2Default1,
	p2Default2,
};

struct Enemy
{
	EnemyType type;
	EnemyMovePattern movepattern;
	MovePatternDefault Default;
};


class C_Player;

class C_EnemyManager
{
public:
	C_EnemyManager() {}
	~C_EnemyManager() { Release(); }

	void Init(C_Player* player);
	void Update();
	void Draw();

	//敵生成
	//type 
	void EnemySpworn(int judgmentcount);

private:

	//解放処理
	void Release();

	//判定回数
	static const int JudgmentNum = 120 / 5 * 10;
	
	//保存用
	Enemy m_spworntype[JudgmentNum];

	void SpwornEnemyLoad();

	//敵座標設定
	Math::Vector2 GetEnemyPos(MovePatternDefault enemypostype,int i);

	//インスタンス取得用
	C_Player* m_player;

	//敵まとめ
	vector<C_EnemyMoveBase*> m_enemys;

	//敵画像セット
	KdTexture& GetEnemyTexture(EnemyType type);
	//画像セット用
	KdTexture m_enemytex;
};

