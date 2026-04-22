#include "EnemyMove1.h"
#include"Application/Prayer/Player.h"
#include"Application/Enemy/EnemyManager.h"
#include"Application/Attack/Shot.h"

void C_EnemyMove1::Init(KdTexture* tex, Math::Vector2 rect,Math::Vector2 animmaxnum, Math::Vector2 enemypos,MovePatternDefault default,C_Player* player)
{
	m_shot = new C_Shot();

	//テクスチャ
	m_tex = tex;
	//アニメーション用
	m_anim = { 0,0 };
	//最大値
	m_animmaxnum = animmaxnum;

	//切り取り範囲
	m_rect = rect;

	//座標
	m_pos = enemypos;
	//移動量
	m_movespeed = { -2,-2 };
	m_move = m_movespeed;
	//サイズ
	m_scale = { 1,1 };
	//カラー
	m_color = { 1,1,1,1 };
	//生存フラグ
	m_alive = true;
	//発射間隔時間
	m_shotintervaltime = 120;
	//発射間隔
	m_shotinterval = 0;

	//プレイヤーのインスタンス
	m_player = player;
	m_player->GetPlayerPos();
}

void C_EnemyMove1::Update()
{
	if (m_shotinterval <= 0)
	{
		m_shot->ShotManager(ShotType::NormalShot, ShotTextureType::Bolt, { 4,0 }, { 48,32 },
			m_pos,m_player->GetPlayerPos());//{ m_pos.x,m_pos.y - 100 });

		m_shotinterval = m_shotintervaltime;
	}

	//弾更新
	m_shot->Update();

	//発射間隔減少
	if (m_shotinterval > 0)
	{
		m_shotinterval--;
		if (m_shotinterval <= 0)
		{
			m_shotinterval = 0;
		}
	}

	//アニメーション用
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

	//移動
	m_pos.y += m_move.y;

	//行列
	m_scalemat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1);
	m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scalemat * m_transmat;
}

void C_EnemyMove1::Draw()
{
	//弾描画
	m_shot->Draw();

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

