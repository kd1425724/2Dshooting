#pragma once

class C_EnemyBase
{
public:
	C_EnemyBase(){}
	~C_EnemyBase(){}

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	virtual void Release();

protected:

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

private:

	

};