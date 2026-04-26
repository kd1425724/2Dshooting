#pragma once

class C_Player;
enum class MovePatternDefault;
class C_Shot;
class C_SkillManager;

enum class UseType;
enum class SkillType;

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

class C_EnemyMoveBase
{
public:
	C_EnemyMoveBase()
	{
		m_tex = nullptr;
		m_enginetex = nullptr;
		m_movetex = nullptr;
		m_deathtex = nullptr;

		m_alive = true;

		m_pos = { 0, 0 };
		m_move = { 0, 0 };
		m_movespeed = { 0, 0 };
		m_scale = { 1, 1 };

		m_anim = { 0, 0 };
		m_animmaxnum = { 0, 0 };

		m_engineanim = { 0, 0 };
		m_deathanim = { 0, 0 };
		m_moveanim = { 0, 0 };

		m_shotinterval = 0;
		m_shotintervaltime = 0;

		m_angle = 0.0f;

		m_skilltype = (SkillType)0;
		m_usetype = (UseType)0;

		m_skillmanager = nullptr;
	}
	~C_EnemyMoveBase(){}

	virtual void Init(PosPattern pospattern,MovePattern movepattern ,std::shared_ptr<C_Player> player,int i){}
	virtual void Update();
	virtual void Draw();

	void SetTexandRectandAnimMax(KdTexture* tex, Math::Vector2 rect,
		Math::Vector2 animmaxnum)
	{
		m_tex = tex;
		m_rect = rect;
		m_animmaxnum = animmaxnum;
	}

	//ボス用
	virtual void Init(){}
	virtual void Init(Math::Vector2 pos){}
	virtual void Init(Math::Vector2 pos,UseType type,int i){}


	//座標取得用
	Math::Vector2 GetPos() { return m_pos; }

	//画像半径取得用
	Math::Vector2 GetRadius() { return m_rect * m_scale / 2; }

	//生存フラグ取得用
	bool GetAlive() { return m_alive; }

	//エンジンテクスチャ
	void SetEngineTex(KdTexture* tex) { m_enginetex = tex; }
	//死亡演出用テクスチャ
	void SetDeathTex(KdTexture* tex) { m_deathtex = tex; }
	//行動用テクスチャ
	void SetMoveTex(KdTexture* tex) { m_movetex = tex; }

	//スキル用
	SkillType GetSkillType() { return m_skilltype; }

	void SetSkillManager(std::shared_ptr<C_SkillManager> skillmanager) { m_skillmanager = skillmanager; }

protected:

	//解放処理
	virtual void Release();

	//テクスチャ
	KdTexture* m_tex;
	//切り取り範囲
	Math::Vector2 m_rect;
	//座標
	Math::Vector2 m_pos;
	//移動量
	Math::Vector2 m_move;
	Math::Vector2 m_movespeed;
	//サイズ
	Math::Vector2 m_scale;
	//行列
	Math::Matrix m_scalemat;
	Math::Matrix m_rotatemat;
	Math::Matrix m_transmat;
	Math::Matrix m_mat;
	//カラー
	Math::Color m_color;
	//生存フラグ
	bool m_alive;
	//アニメーション用
	Math::Vector2 m_anim;
	Math::Vector2 m_animmaxnum;
	//攻撃間隔
	int m_shotinterval;
	//攻撃間隔時間
	int m_shotintervaltime;
	//移動方向用
	float m_angle;

	//ショット用
	std::shared_ptr<C_Shot> m_shot;

	//プレイヤーインスタンス受け取り用
	std::shared_ptr<C_Player> m_player;

	KdTexture* m_enginetex;
	KdTexture* m_movetex;
	KdTexture* m_deathtex;

	Math::Vector2 m_engineanimmaxnum;
	Math::Vector2 m_deathanimmaxnum;
	Math::Vector2 m_moveanimmaxnum;

	Math::Vector2 m_engineanim;
	Math::Vector2 m_deathanim;
	Math::Vector2 m_moveanim;

	//スキル用
	std::shared_ptr<C_SkillManager> m_skillmanager;

	SkillType m_skilltype;

	UseType m_usetype;

private:

	

};