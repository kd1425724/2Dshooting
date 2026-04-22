#include "Player.h"
#include"Application/Common/CommonTexture.h"
#include"Application/Input/Input.h"
#include"Application/Attack/Shot.h"

void C_Player::Init()	
{
	ShotInit();

	//座標
	m_pos = { 0,0 };
	//移動量
	m_move = { 0.0f,0.0f };
	m_movespeed = { 5.0f,5.0f };
	//サイズ
	m_scale = { 1.5f,1.5f };
	//カラー
	m_color = { 1,1,1,1 };
}
void C_Player::Update()
{
	ShotUpdate();

	m_move = { 0,0 };

	if (Input.GetPlayerKey(PlayerKeyType::Top))
	{
		m_move.y = m_movespeed.y;
	}
	else if (Input.GetPlayerKey(PlayerKeyType::Bottom))
	{
		m_move.y = -m_movespeed.y;
	}
	if (Input.GetPlayerKey(PlayerKeyType::Left))
	{
		m_move.x = -m_movespeed.x;
	}
	else if (Input.GetPlayerKey(PlayerKeyType::Right))
	{
		m_move.x = m_movespeed.x;
	}

	m_pos += m_move;
	
	m_scalemat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1);
	m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scalemat * m_transmat;
}
void C_Player::Draw()
{
	m_shot->Draw();

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&CommonTex.GetPlayerTex(), 0, 0, &CommonTex.GetPlayerRect(), &m_color);
}

void C_Player::Release()
{
	if (m_shot)
	{
		delete m_shot;
		m_shot = nullptr;
	}
}

void C_Player::ShotInit()
{
	m_shot = new C_Shot();

	m_shotinterval = 0;
}

void C_Player::ShotUpdate()
{
	//攻撃Update
	m_shot->Update();

	//通常攻撃
	if (m_shotinterval <= 0)
	{
		if (Input.GetPlayerKey(PlayerKeyType::NormalShot))
		{
			m_shot->ShotManager(ShotType::NormalShot,ShotTextureType::Bolt, { 4,0 }, { 48,32 },
				m_pos, { m_pos.x,m_pos.y + 100 });
			m_shotinterval = (int)PlayerShotInterval::NormalShot;
		}
	}

	//通常攻撃発射間隔減少
	if (m_shotinterval > 0)
	{
		m_shotinterval--;
		if (m_shotinterval <= 0)
		{
			m_shotinterval = 0;
		}
	}
}
