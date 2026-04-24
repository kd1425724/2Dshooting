#pragma once
#include"Application/Enemy/EnemyMoveBase.h"

class C_EnemyMove1:public C_EnemyMoveBase

{
public:
	C_EnemyMove1(){}
	~C_EnemyMove1() { Release(); }

	void Init(PosPattern pospattern, MovePattern movepattern, std::shared_ptr<C_Player> player,int i)override;
	void Update()override;
	void Draw()override;

	//ボス用なので使わない
	void Init()override {}

private:

	//解放処理
	void Release()override;
};
