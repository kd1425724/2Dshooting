#pragma once

class C_EnemyMoveBase
{
public:
	C_EnemyMoveBase();
	~C_EnemyMoveBase(){}

	virtual void Init(KdTexture* tex,Math::Vector2 rect, Math::Vector2 animmaxnum);
	virtual void Update();
	virtual void Draw();

	virtual void Release();

protected:

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

private:

	

};