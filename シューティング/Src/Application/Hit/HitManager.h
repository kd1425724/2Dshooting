#pragma once

class C_Player;
class C_EnemyMoveBase;
struct Shot;

class C_SkillBase;
class C_Laser;
class C_Barrier;
class C_SkillManager;
class C_Boss;

enum class SkillType;

enum class HitType
{
	Player,
	Enemy,
	PlayerShot,
	EnemyShot,
	PlayerLaser,
	EnemyLaser,
	PlayerBarrier,
	EnemyBarrier
};

class C_HitManager
{
public:
	C_HitManager();
	~C_HitManager() { Release(); }

	void Init();
	void Update();
	void Draw();

	void ImGui();

	// 登録・解除
	void Clear();

	//スキル管理取得
	void SetSkillManager(std::shared_ptr<C_SkillManager> skillmanager) { m_skillmanager = skillmanager; }

	
	//プレイヤー
	void SetPlayer(std::shared_ptr<C_Player> player) { m_player = player; }

	//敵
	void SetEnemy(std::shared_ptr<C_EnemyMoveBase> enemy) { m_enemys.push_back(enemy); }

	//プレイヤースキルEnemyGenerate
	void SetGenerateEnemy(std::shared_ptr<C_EnemyMoveBase> playerenemy) { m_playerenemys.push_back(playerenemy); }

	//プレイヤーの弾
	void SetPlayerShot(std::shared_ptr<Shot> shot) { m_playershot.push_back(shot); }
	//敵の弾
	void SetEnemyShot(std::shared_ptr<Shot> shot) { m_enemyshot.push_back(shot); }

	//プレイヤーのレーザー
	void SetPlayerLaser(std::shared_ptr<C_Laser> laser) { m_playerlaser.push_back(laser); }
	//敵のレーザー
	void SetEnemyLaser(std::shared_ptr<C_Laser> laser) { m_enemylaser.push_back(laser); }

	//プレイヤーのバリア
	void SetPlayerBarrier(std::shared_ptr<C_Barrier> barrier) { m_playerbarrier.push_back(barrier); }
	//敵のバリア
	void SetEnemyBarrier(std::shared_ptr<C_Barrier> barrier) { m_enemybarrier.push_back(barrier); }

	//コピー
	void SetCopyShot(std::shared_ptr<Shot> copyshot) { m_copyshot.push_back(copyshot); }

	void SetCopyBackShot(std::shared_ptr<Shot> copybackshot) { m_copybackshot.push_back(copybackshot); }

	//ボス用
	void SetBoss(std::shared_ptr<C_Boss> boss) { m_boss = boss; }

	//デバッグ用
	void DrawCircle(Math::Vector2 pos, float radius, Math::Color col);

private:

	SkillType m_skilltype = (SkillType)0;

	void Release();

	//ボス用
	std::weak_ptr<C_Boss> m_boss;

	//攻撃力
	static const int PlayerShotAtk = 30;
	static const int PlayerLaserAtk = 100;
	static const int PlayerGenerateEnemyAtk = 20;

	static const int EnemyShotAtk = 10;
	static const int EnemyLaserAtk = 100;

	//スコア
	static const int ShotDeleteScoreNum = 25000;

	//デバッグ用
	bool m_DrawHitdebugflg = false;

	//プレイヤー
	std::weak_ptr<C_Player> m_player;

	//敵
	std::vector<std::weak_ptr<C_EnemyMoveBase>> m_enemys;

	//EnemyGerate用
	std::vector<std::weak_ptr<C_EnemyMoveBase>> m_playerenemys;

	//プレイヤーの弾
	std::vector<std::weak_ptr<Shot>> m_playershot;
	//敵の弾
	std::vector<std::weak_ptr<Shot>> m_enemyshot;

	//プレイヤーのレーザー
	std::vector<std::weak_ptr<C_Laser>> m_playerlaser;
	//敵のレーザー
	std::vector<std::weak_ptr<C_Laser>> m_enemylaser;

	//プレイヤーのバリア
	std::vector<std::weak_ptr<C_Barrier>> m_playerbarrier;
	//敵のバリア
	std::vector<std::weak_ptr<C_Barrier>> m_enemybarrier;

	//コピー
	std::vector<std::weak_ptr<Shot>> m_copyshot;
	//コピー変換
	std::vector<std::weak_ptr<Shot>> m_copybackshot;

	//プレイヤースキル設定用
	std::weak_ptr<C_SkillManager> m_skillmanager;

	// 円 vs 円
	bool IsHit(Math::Vector2 pos1, float r1,Math::Vector2 pos2, float r2);
	// 矩形 vs 矩形（AABB）
	bool IsHit(Math::Vector2 pos1, Math::Vector2 halfSize1,Math::Vector2 pos2, Math::Vector2 halfSize2);
	
	bool IsHitLaser(Math::Vector2 start,Math::Vector2 end,float laserthickness,Math::Vector2 pos,float radius);

	void PlayerHit();

	void PlayerShotHit();

	void CopyHit();

	void EnemyHit();

	void EnemyShotHit();
};