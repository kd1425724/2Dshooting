#pragma once

class C_HitManager;
class C_Game;

enum class PlayerShotInterval
{
	NormalShot = 5,	//通常攻撃
	Num
};

class C_Player : public std::enable_shared_from_this<C_Player>
{
public:
	C_Player()
	{
		m_engineanim = 0.0f;

		m_Hp = 0;

		m_hitmanager = nullptr;

		m_hittimer = 0;

		m_pos = { 0,0 };
		m_move = { 0,0 };
		m_movespeed = { 0,0 };

		m_scale = { 1,1 };

		m_scalemat = Math::Matrix::Identity;
		m_transmat = Math::Matrix::Identity;
		m_mat = Math::Matrix::Identity;

		m_color = { 1,1,1,1 };

		m_alive = true;

		m_rect = { 0,0 };

		m_radius = 0.0f;

		m_halfsize = { 0,0 };

		m_shotinterval = 0;
	}

	~C_Player() {}

	void Init();
	void Update();
	void Draw();

	void ResultInit();
	void ResultUpdate();
	void ResultDraw();

	void TitleInit();
	void TitleUpdate();
	void TitleDraw();

	void Release();

	void ImGui();

	void ShotInit();
	void ShotUpdate();

	bool GetAlive()
	{
		return m_alive;
	}

	Math::Vector2 GetPos()
	{
		return m_pos;
	}

	//半径x,y別（矩形）
	Math::Vector2 GetSize()
	{
		return m_halfsize;
	}

	//半径（円判定）
	float GetRadius()
	{
		return m_radius;
	}

	//Hpゲッター
	int GetHp()
	{
		return m_Hp;
	}

	void SetHitManager(std::shared_ptr<C_HitManager> hitmanager)
	{
		m_hitmanager = hitmanager;
	}

	//ダメージ処理
	void Damage();

	void HitUpdate();

	//エンジン用
	void SetEngineTex(std::vector<std::shared_ptr<KdTexture>> tex)
	{
		m_enginetexs = tex;
	}

	void SetOwner(std::shared_ptr<C_Game> owner)
	{
		m_owner = owner;
	}

private:

	//オーナー
	std::weak_ptr<C_Game> m_owner;

	//エンジン
	std::vector<std::shared_ptr<KdTexture>> m_enginetexs;

	//アニメーション用
	float m_engineanim = 0.0f;

	//ステータス
	int m_Hp = 0;

	//当たり判定用
	std::shared_ptr<C_HitManager> m_hitmanager = nullptr;

	static const int HitTime = 180;

	int m_hittimer = 0;

	//座標
	Math::Vector2 m_pos = { 0,0 };

	//移動量
	Math::Vector2 m_move = { 0,0 };

	Math::Vector2 m_movespeed = { 0,0 };

	//サイズ
	Math::Vector2 m_scale = { 1,1 };

	//行列
	Math::Matrix m_scalemat = Math::Matrix::Identity;

	Math::Matrix m_transmat = Math::Matrix::Identity;

	Math::Matrix m_mat = Math::Matrix::Identity;

	//カラー
	Math::Color m_color = { 1,1,1,1 };

	//生存フラグ
	bool m_alive = true;

	//切り取り範囲
	Math::Vector2 m_rect = { 0,0 };

	//半径
	float m_radius = 0.0f;

	Math::Vector2 m_halfsize = { 0,0 };

	//発射間隔
	int m_shotinterval = 0;
};