#pragma once
#include"Application/Enemy/EnemyMoveBase.h"

enum class  InherentMove3
{
	Start,
	Stop,
};

class C_EnemyMove3 :public C_EnemyMoveBase, public std::enable_shared_from_this<C_EnemyMove3>

{
public:
	C_EnemyMove3() { }
	~C_EnemyMove3() override{ Release(); }

	void Init(Math::Vector2 pos, UseType type, int i)override;
	void Update()override;
	void Draw()override;

private:

	//‰ğ•úˆ—
	void Release()override;

	Math::Vector2 m_stoppos;

	InherentMove3 m_inherentmove;
};
