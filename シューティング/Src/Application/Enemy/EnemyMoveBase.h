#pragma once

class C_Player;
enum class MovePatternDefault;
class C_SkillManager;

class C_HitBase;
class C_HitManager;

enum class UseType;
enum class SkillType;

class C_Game;

enum class PosPattern
{
	Pattern1,
	Pattern2,
	Pattern3,
	Pattern4
};

enum class MovePattern
{
	Pattern1,
	Pattern2,
	Pattern3,
	Pattern4,
	Pattern5
};

enum class EnemySType
{
	Normal,
	SubBoss,
	Boss
};

class C_EnemyMoveBase
{
public:
	C_EnemyMoveBase() {}
	virtual ~C_EnemyMoveBase() {}

	virtual void Init(PosPattern pospattern, MovePattern movepattern, std::shared_ptr<C_Player> player, int i) {}
	virtual void Update();
	virtual void Draw();

	virtual void StartDirectionUpdate(){}

	void SetTexandRectandAnimMax(KdTexture* tex, Math::Vector2 rect,
		Math::Vector2 animmaxnum = { 0,0 })
	{
		m_tex = tex;
		m_rect = rect;
		m_animmaxnum = animmaxnum;
	}

	//ボス用
	virtual void Init() {}
	virtual void Init(Math::Vector2 pos) {}
	virtual void Init(Math::Vector2 pos, UseType type, int i) {}

	//座標取得用
	Math::Vector2 GetPos() { return m_pos; }

	//半径x,y別（矩形）
	Math::Vector2 GetSize() { return m_halfsize; }

	//半径（円判定）
	float GetRadius() { return m_radius; }

	//生存フラグ取得用
	bool GetAlive() { return m_alive; }

	//体力
	int GetHp() { return m_hp; }

	//最大体力
	int GetMaxHp() { return m_maxhp; }

	//エンジンテクスチャ
	void SetEngineTex(KdTexture* tex) { m_enginetex = tex; }

	//死亡演出用テクスチャ
	void SetDeathTex(KdTexture* tex) { m_deathtex = tex; }

	//行動用テクスチャ
	void SetMoveTex(KdTexture* tex) { m_movetex = tex; }

	//スキル用
	SkillType GetSkillType() { return m_skilltype; }

	//スキル管理用
	void SetSkillManager(std::shared_ptr<C_SkillManager> skillmanager)
	{
		m_skillmanager = skillmanager;
	}

	//当たり判定管理用
	void SetHitManager(std::shared_ptr<C_HitManager> hitmanager)
	{
		m_hitmanager = hitmanager;
	}

	//ダメージ処理
	void Damage(int value);

	//ヒット演出用
	void HitUpdate();

	EnemySType GetEnemyType() { return m_enemytype; }

	void SetOwner(std::weak_ptr<C_Game> owner)
	{
		m_owner = owner;
	}

	bool GetDeathFlg() { return m_deathflg; }

protected:

	//オーナー
	std::weak_ptr<C_Game> m_owner;

	//解放処理
	virtual void Release();

	//スコア用
	int m_score = 1000;

	EnemySType m_enemytype = EnemySType::Normal;

	//ステータス
	int m_maxhp = 1;
	int m_hp = 1;

	//テクスチャ
	KdTexture* m_tex = nullptr;

	//切り取り範囲
	Math::Vector2 m_rect = { 0,0 };

	//座標
	Math::Vector2 m_pos = { 0,0 };

	//移動量
	Math::Vector2 m_move = { 0,0 };
	Math::Vector2 m_movespeed = { 0,0 };

	//サイズ
	Math::Vector2 m_scale = { 1,1 };

	//行列
	Math::Matrix m_scalemat = Math::Matrix::Identity;
	Math::Matrix m_rotatemat = Math::Matrix::Identity;
	Math::Matrix m_transmat = Math::Matrix::Identity;
	Math::Matrix m_mat = Math::Matrix::Identity;

	//カラー
	Math::Color m_color = { 1,1,1,1 };

	//生存フラグ
	bool m_alive = true;

	//アニメーション用
	Math::Vector2 m_anim = { 0,0 };
	Math::Vector2 m_animmaxnum = { 0,0 };

	//攻撃間隔
	int m_shotinterval = 0;

	//攻撃間隔時間
	int m_shotintervaltime = 0;

	//移動方向用
	float m_angle = 0.0f;

	//半径
	float m_radius = 0.0f;

	Math::Vector2 m_halfsize = { 0,0 };

	//プレイヤーインスタンス受け取り用
	std::weak_ptr<C_Player> m_player;

	//テクスチャ
	KdTexture* m_enginetex = nullptr;
	KdTexture* m_movetex = nullptr;
	KdTexture* m_deathtex = nullptr;

	Math::Vector2 m_engineanimmaxnum = { 0,0 };
	Math::Vector2 m_deathanimmaxnum = { 0,0 };
	Math::Vector2 m_moveanimmaxnum = { 0,0 };

	Math::Vector2 m_engineanim = { 0,0 };
	Math::Vector2 m_deathanim = { 0,0 };
	Math::Vector2 m_moveanim = { 0,0 };

	//スキル用
	std::weak_ptr<C_SkillManager> m_skillmanager;

	//当たり判定管理用
	std::weak_ptr<C_HitManager> m_hitmanager;

	static const int HitTimer = 10;

	int m_hittimer = 0;

	SkillType m_skilltype = (SkillType)0;

	UseType m_usetype = (UseType)0;

	//死んだかどうか
	bool m_deathflg = false;

private:

};