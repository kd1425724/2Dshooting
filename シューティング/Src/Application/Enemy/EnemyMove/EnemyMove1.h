#pragma once
#include"Application/Enemy/EnemyMoveBase.h"
#include"Application/Attack/Shot.h"

class C_EnemyMove1:public C_EnemyMoveBase

{
public:
	C_EnemyMove1(){}
	~C_EnemyMove1(){}

	void Init(KdTexture* tex, Math::Vector2 rect, Math::Vector2 animmaxnum)override;
	void Update()override;
	void Draw()override;

	void Release()override;

private:

	C_Shot m_shot;
};
