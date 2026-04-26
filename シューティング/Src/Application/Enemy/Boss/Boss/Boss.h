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
	p4_SpiralShot,
	ActionPatternNum
};
class C_Boss:public C_BossBase, public std::enable_shared_from_this<C_Boss>
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

	//螺旋状に放つ弾用
	float m_spiralshotangle;
	static const int SpiralShotInterval = 3;
	int m_spiralshotinterval;

	//一行動の時間
	//敵生成
	static const int EnemyGenerateTime = 300;
	int m_enemygeneratetime;
	//レーザー
	static const int LaserTime = 300;
	int m_lasertime;
	//バリア
	static const int BarrierTime = 300;
	int m_barriertime;
	//螺旋
	static const int SpiralTime = 300;
	int m_spiraltime;


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
	void p1_EnemyGenerateInit();
	void p2_LaserInit();
	void p3_BarrierInit();
	void p4_SpiralInit();

	//ループ中行動パターン更新
	void p1_EnemyGenerateUpdate();
	void p2_LaserUpdate();
	void p3_BarrierUpdate();
	void p4_SpiralUpdate();

	//ループ中行動パターン描画
	void p1_EnemyGenerateDrawSprite();
	void p2_LaserDrawSprite();
	void p3_BarrierDrawSprite();
	void p4_SpiralDrawSprite();

	//行動パターンセット
	void SetActionPattern(ActionPattern pattern);

	//指定したもの以外の値を返す
	ActionPattern GetRandomPatternExclude(ActionPattern exclude);

};
