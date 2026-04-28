#pragma once
#include"Application/Enemy/EnemyMoveBase.h"

enum class Pattern
{
	Start,
	Loop,
	Death

};

class C_BossBase :public C_EnemyMoveBase
{
public:
	C_BossBase() {}
	virtual ~C_BossBase()override{}

	virtual void Init()		override;
	virtual void Init(Math::Vector2 pos,UseType type,int i)		override{}
	virtual void Update()						override;
	virtual void Draw()							override;


private:

	virtual void Release()	override;

	

};