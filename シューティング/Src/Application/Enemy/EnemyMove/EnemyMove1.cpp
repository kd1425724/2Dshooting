#include "EnemyMove1.h"

void C_EnemyMove1::Init(KdTexture* tex, Math::Vector2 rect,Math::Vector2 animmaxnum)
{
	//テクスチャ
	m_tex = tex;
	
	//アニメーション用
	m_anim = { 0,0 };
	//最大値
	m_animmaxnum = animmaxnum;

	//座標
	m_pos = { 0,0 };
	//移動量
	m_movespeed = { 5,5 };
	m_move = m_movespeed;
	//サイズ
	m_scale = { 1,1 };
	//カラー
	m_color = { 1,1,1,1 };
	//生存フラグ
	m_alive = false;

	m_shotintervaltime = 30;

	m_shotinterval = 0;
}

void C_EnemyMove1::Update()
{
	if (m_shotinterval <= 0)
	{
		m_shot.ShotManager(ShotType::NormalShot,ShotTextureType::Bolt, { 4,0 }, { 48,32 },
			m_pos, { m_pos.x,m_pos.y + 100 });
		m_shotinterval = m_shotintervaltime;
	}

	m_pos.x += m_move.x;

	m_anim.x += 0.1f;
	//マックス以上になったら,4コマなら4
	if (m_anim.x >= m_animmaxnum.x)
	{
		m_anim.x = 0;
		if (m_animmaxnum.y != 0)
		{
			m_anim.y++;
		}
	}
	if (m_animmaxnum.y != 0)
	{
		if (m_anim.y > m_animmaxnum.y)
		{
			m_anim = { 0,0 };
		}
	}
}

void C_EnemyMove1::Draw()
{
	//発生中なら
	if (m_alive)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_tex, 0, 0,
			&Math::Rectangle((int)m_anim.x * m_rect.x, (int)m_anim.y * m_rect.y, m_rect.x,m_rect.y),
			&m_color);
	}
}

void C_EnemyMove1::Release()
{
	
}

