#pragma once
#include"Application/Enemy/EnemyMoveBase.h"

class C_BossBase :public C_EnemyMoveBase
{
public:
	C_BossBase() {}
	~C_BossBase() {}

	//ŽG‹›“G—p‚È‚Ì‚ÅŽg‚í‚È‚¢
	virtual void Init(PosPattern pospattern, MovePattern movepattern, std::shared_ptr<C_Player> player, int i)override {}


	virtual void Init()		override;
	virtual void Init(Math::Vector2 pos)		override;
	virtual void Update()						override;
	virtual void Draw()							override;


private:

	virtual void Release()	override;

	

};