#pragma once
#include"Application/Enemy/Boss/BossBase.h"

enum class Pattern
{
	Start,
	Loop,
	Death

};

enum class ActionPattern
{
	p1_EnemyGenerate,
	p2_Laser,
	p3_Barrier,
};
class C_Boss:public C_BossBase
{
public:
	C_Boss(){}
	~C_Boss() { Release(); }

	//雑魚敵用なので使わない
	void Init(PosPattern pospattern, MovePattern movepattern, std::shared_ptr<C_Player> player, int i)override {}

	void Init()		override;
	void Update()	override;
	void Draw()		override;


private:

	void Release()	override;

	//ボスパターン
	Pattern m_pattern;

	//ボス行動パターン
	ActionPattern m_actionpattern;

	//止まる座標
	Math::Vector2 m_stoppos;

	float m_texangle;

	KdTexture tex;

	//スタート
	void StartUpdate();
	void StartDraw();
	//ループ更新
	void LoopUpdate();
	void LoopDraw();
	//デス中更新
	void DeathUpdate();
	void DeathDraw();

	//ループ中行動パターン更新
	void p1_EnemyGenerateUpdate();
	void p2_LaserUpdate();
	void p3_BarrierUpdate();

};
