#include "Boss.h"
#include"../../../Skill/Shot/Shot.h"

void C_Boss::Init()
{
	//プレイヤーのインスタンス
	//m_player = move(player);

	m_shot = std::make_shared<C_Shot>();

	//アニメーション用
	m_anim = { 0,0 };

	m_pos = { 700,0 - 60 };

	//移動量
	
	m_stoppos = { 300,0 - 60 };
	m_movespeed = { 4,4 };
	m_angle = atan2(m_stoppos.y - m_pos.y, m_stoppos.x - m_pos.x);
	m_move.x = cosf(m_angle) * m_movespeed.x;
	m_move.y = sinf(m_angle) * m_movespeed.y;

	//サイズ
	m_scale = { 3,3 };
	//カラー
	m_color = { 1,1,1,1 };
	//生存フラグ
	m_alive = true;
	//発射間隔時間
	m_shotintervaltime = 5 * 60;
	//発射間隔
	m_shotinterval = 0;

	m_texangle = DirectX::XMConvertToRadians(90);

	//エンジン用
	m_engineanim = { 0,0 };
	m_engineanimmaxnum = { 12,0 };

	//死亡演出用
	m_deathanim = { 0,0 };
	m_deathanimmaxnum = { 14,0 };

	//パターン
	m_pattern = Pattern::Start;

	//行動パターン
	m_actionpattern = ActionPattern::p1_EnemyGenerate;

	//固有行動
	//m_inherentmove = InherentMove::Start;
	//ストップカウント
	//m_stopcount = 0;
}

void C_Boss::Update()
{
	switch (m_pattern)
	{
	case Pattern::Start:
		StartUpdate();
		break;
	case Pattern::Loop:
		LoopUpdate();
		break;
	case Pattern::Death:
		DeathUpdate();
		break;
	default:
		break;
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

	//エンジンアニメーション用
	m_engineanim.x += 0.1f;
	//マックス以上になったら,4コマなら4
	if (m_engineanim.x >= m_engineanimmaxnum.x)
	{
		m_engineanim.x = 0;
		if (m_engineanimmaxnum.y != 0)
		{
			m_engineanim.y++;
		}
	}
	if (m_engineanimmaxnum.y != 0)
	{
		if (m_engineanim.y > m_engineanimmaxnum.y)
		{
			m_engineanim = { 0,0 };
		}
	}

	m_scalemat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1);
	m_rotatemat = Math::Matrix::CreateRotationZ(m_texangle);
	m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scalemat*m_rotatemat * m_transmat;
}

void C_Boss::Draw()
{
	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_mat);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_tex, 0, 0,
		&Math::Rectangle(0, 0, m_rect.x, m_rect.y), &m_color);
	//エンジン
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_enginetex, 0, 0,
		&Math::Rectangle((int)m_engineanim.x * m_rect.x, (int)m_engineanim.y * m_rect.y, m_rect.x, m_rect.y), &m_color);


	switch (m_pattern)
	{
	case Pattern::Start:
		StartDraw();
		break;
	case Pattern::Loop:
		LoopDraw();
		break;
	case Pattern::Death:
		DeathDraw();
		break;
	default:
		break;
	}
}

void C_Boss::Release()
{
}

void C_Boss::StartUpdate()
{
	m_pos += m_move;

	if (m_pos.x <= m_stoppos.x)
	{
		m_pos = m_stoppos;
		m_move = { 0,0 };

		m_pattern = Pattern::Loop;

		m_actionpattern = ActionPattern::p1_EnemyGenerate;
	}
}

void C_Boss::StartDraw()
{
}

void C_Boss::LoopUpdate()
{
	switch (m_actionpattern)
	{
	case ActionPattern::p1_EnemyGenerate:
		p1_EnemyGenerateUpdate();
		break;
	case ActionPattern::p2_Laser:
		p2_LaserUpdate();
		break;
	case ActionPattern::p3_Barrier:
		p3_BarrierUpdate();
		break;
	default:
		break;
	}
}

void C_Boss::LoopDraw()
{
}

void C_Boss::DeathUpdate()
{
	//死亡アニメーション用
	m_deathanim.x += 0.1f;
	//マックス以上になったら,4コマなら4
	if (m_deathanim.x >= m_deathanimmaxnum.x)
	{
		m_deathanim.x = 0;
		if (m_deathanimmaxnum.y != 0)
		{
			m_deathanim.y++;
		}
	}
	if (m_deathanimmaxnum.y != 0)
	{
		if (m_deathanim.y > m_deathanimmaxnum.y)
		{
			m_deathanim = { 0,0 };
		}
	}

	if (m_deathanim.x >= m_deathanimmaxnum.x)
	{
		//死亡演出が終了したら消去
		m_alive = false;
	}
}

void C_Boss::DeathDraw()
{
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_tex, 0, 0,
		&Math::Rectangle((int)m_deathanim.x * m_rect.x, (int)m_deathanim.y * m_rect.y, m_rect.x, m_rect.y),
		&m_color);
}

void C_Boss::p1_EnemyGenerateUpdate()
{

}

void C_Boss::p2_LaserUpdate()
{
}

void C_Boss::p3_BarrierUpdate()
{
}
