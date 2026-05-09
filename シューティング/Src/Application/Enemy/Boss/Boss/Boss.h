#pragma once
#include"Application/Enemy/Boss/BossBase.h"

enum class BossActionPattern
{
	None,
	p1_EnemyGenerate,
	p2_Laser,
	p3_Barrier,
	p4_SpiralShot,
	p5_Shot2,
	BossActionPatternNum,
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

	bool m_moveflg = false;

	//何もしない時間
	static const int NoneTime = 60;
	int m_nonetime;

	//ボスパターン
	Pattern m_pattern;

	//ボス行動パターン
	BossActionPattern m_actionpattern;
	BossActionPattern m_nextactionpattern;

	//止まる座標
	Math::Vector2 m_stoppos;

	float m_texangle;

	//螺旋状に放つ弾用
	float m_spiralshotangle;
	static const int SpiralShotInterval = 3;
	int m_spiralshotinterval;

	//一行動の時間
	//敵生成
	static const int EnemyGenerateTime = 60;
	int m_enemygeneratetime=0;
	//レーザー
	static const int LaserTime = 300;
	int m_lasertime=0;
	//バリア
	static const int BarrierTime = 300;
	int m_barriertime=0;
	//螺旋
	static const int SpiralTime = 300;
	int m_spiraltime=0;

	//弾
	static const int Shot2Time = 120;
	int m_shot2time=0;

	static const int Shot2Interval = 20;
	int m_shot2interval;



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
	void NoneInit(BossActionPattern pattern);
	void p1_EnemyGenerateInit();
	void p2_LaserInit();
	void p3_BarrierInit();
	void p4_SpiralInit();
	void p5_Shot2Init();

	//ループ中行動パターン更新
	void NoneUpdate();
	void p1_EnemyGenerateUpdate();
	void p2_LaserUpdate();
	void p3_BarrierUpdate();
	void p4_SpiralUpdate();
	void p5_Shot2Update();

	//行動パターンセット
	void SetActionPattern(BossActionPattern pattern);

	//指定したもの以外の値を返す
	BossActionPattern GetRandomPatternExclude(BossActionPattern exclude);

	SkillType C_Boss::GetRandomSkillType();
};
