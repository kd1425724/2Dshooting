#pragma once
#include"Application/Enemy/EnemyMoveBase.h"
#include<vector>

using namespace std;

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
	p1Default,
	p2Default,
};

class C_EnemyManager
{
public:
	~C_EnemyManager(){}

	void Init();
	void Update();
	void Draw();

	//“G¶¬
	//type 
	void EnemySpworn(EnemyType type,EnemyMovePattern movepattern,int num);

private:

	//“G‚Ü‚Æ‚ß
	vector<C_EnemyMoveBase> m_enemys;


//ƒVƒ“ƒOƒ‹ƒgƒ“
private:
	C_EnemyManager() {}

public:

	static C_EnemyManager& GetInstans()
	{
		static C_EnemyManager instans;
		return instans;
	}
};
//“GŠÇ—
#define ENEMYMANAGER C_EnemyManager::GetInstans()


