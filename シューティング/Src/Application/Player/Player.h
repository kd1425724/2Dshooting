#pragma once

class C_Shot;
class C_HitManager;

enum class PlayerShotInterval
{
	NormalShot=5,	//通常攻撃
	Num
};

class C_Player:public std::enable_shared_from_this<C_Player>
{
public:
	C_Player(){}
	~C_Player(){}

	void Init();
	void Update();
	void Draw();

	void Release();

	void ImGui();

	void ShotInit();
	void ShotUpdate();

	Math::Vector2 GetPos() { return m_pos; }

	//半径x,y別（矩形）
	Math::Vector2 GetSize() { return m_halfsize; }

	//半径（円判定）
	float GetRadius() { return m_radius; }

	void SetHitManager(std::shared_ptr<C_HitManager> hitmanager) { m_hitmanager = hitmanager; }

	//ダメージ処理
	void Damage() { m_Hp--; };

private:

	//ステータス
	int m_Hp = 3;

	//当たり判定用
	std::shared_ptr<C_HitManager> m_hitmanager;

	//座標
	Math::Vector2 m_pos;
	//移動量
	Math::Vector2 m_move;
	Math::Vector2 m_movespeed;
	//サイズ
	Math::Vector2 m_scale;
	//行列
	Math::Matrix m_scalemat;
	Math::Matrix m_transmat;
	Math::Matrix m_mat;
	//カラー
	Math::Color m_color;
	//生存フラグ
	bool m_alive;
	//切り取り範囲
	Math::Vector2 m_rect;
	//半径
	float m_radius;
	Math::Vector2 m_halfsize;

	//弾
	std::shared_ptr<C_Shot> m_shot;
	//発射間隔
	int m_shotinterval;
};

