#pragma once
#include"Application/Attack/Shot.h"

enum class PlayerShotInterval
{
	NormalShot=10,	//通常攻撃
	Num
};

class C_Player
{
public:
	C_Player(){}
	~C_Player(){}

	void Init();
	void Update();
	void Draw();

	void Release();

	void ShotInit();
	void ShotUpdate();

private:

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

	//弾
	C_Shot m_shot;
	//発射間隔
	int m_shotinterval;

};

