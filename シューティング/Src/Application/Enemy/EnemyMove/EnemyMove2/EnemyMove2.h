#pragma once
#include"Application/Enemy/EnemyMoveBase.h"

enum class InherentMove2
{
	Start,
	Stop,
	Shot,
	Stop2,
	ReStart,
};

class C_EnemyMove2:public C_EnemyMoveBase
{
public:
	C_EnemyMove2(){}
	~C_EnemyMove2() { Release(); }

	void Init(PosPattern pospattern, MovePattern movepattern, std::shared_ptr<C_Player> player, int i)override;
	void Update()	override;
	void Draw()		override;

	//ボス用なので使わない
	void Init()override{}
private:

	//解放処理
	void Release()override;

	//固有行動
	InherentMove2 m_inherentmove;

	//ストップカウント
	static const int m_stopcountmax = 1 * 60;
	int m_stopcount;

	//発射座標
	Math::Vector2 m_shotpos;

	//弾用
	float m_shotangle;

};