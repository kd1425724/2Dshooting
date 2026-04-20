#pragma once
#include"Application/Enemy/EnemyBase.h"
#include<vector>

using namespace std;

class C_EnemyManager
{
public:
	~C_EnemyManager(){}

	void Init();
	void Update();
	void Draw();

private:

	//“G‚Ü‚Æ‚ß
	vector<C_EnemyBase> m_enemys;


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


