#pragma once
#include"Application/Enemy/Boss/BossBase.h"

enum class SubBossActionPattern
{
	p1_Laser,
	p2_Barrier,
	SubBossActionPatternNum
};

class C_SubBoss :public C_BossBase, public std::enable_shared_from_this<C_SubBoss>
{
public:
	C_SubBoss() {}
	~C_SubBoss() { Release(); }

	void Init(Math::Vector2 pos)		override;
	void Update()	override;
	void Draw()		override;


private:

	void Release()	override;

	//ボスパターン
	Pattern m_pattern;

	//ボス行動パターン
	SubBossActionPattern m_actionpattern;

	//止まる座標
	Math::Vector2 m_stoppos;

	float m_texangle;

	KdTexture tex;

	//一行動の時間
	//レーザー
	static const int LaserTime = 300;
	int m_lasertime;
	//バリア
	static const int BarrierTime = 300;
	int m_barriertime;
	
	//スタート
	void StartUpdate();
	void StartDraw();
	//ループ更新
	void LoopUpdate();
	void LoopDraw();
	//デス中更新
	void DeathUpdate();
	void DeathDraw();

	//ループ中行動パターン初期化
	void p1_LaserInit();
	void p2_BarrierInit();
	

	//ループ中行動パターン更新
	void p1_LaserUpdate();
	void p2_BarrierUpdate();

	//ループ中行動パターン描画
	void p1_LaserDrawSprite();
	void p2_BarrierDrawSprite();

	//行動パターンセット
	void SetActionPattern(SubBossActionPattern pattern);

	//指定したもの以外の値を返す
	SubBossActionPattern GetRandomPatternExclude(SubBossActionPattern exclude);

};
