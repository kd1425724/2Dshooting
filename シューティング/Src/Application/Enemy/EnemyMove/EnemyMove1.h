#pragma once
#include"Application/Enemy/EnemyMoveBase.h"

enum class MovePatternDefault;

class C_EnemyMove1:public C_EnemyMoveBase

{
public:
	C_EnemyMove1(){}
	~C_EnemyMove1(){}

	void Init(KdTexture* tex, Math::Vector2 rect, Math::Vector2 animmaxnum, Math::Vector2 enemypos, MovePatternDefault default, C_Player* player)override;
	void Update()override;
	void Draw()override;

	void Release()override;

private:

	C_Player* m_player;
};
