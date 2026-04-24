#include"Application/Enemy/EnemyMove/EnemyMove2/EnemyMove2.h"
#include"Application/Info.h"
#include"Application/Prayer/Player.h"
#include"Application/Enemy/EnemyManager.h"
#include"../../../Skill/Shot/Shot.h"
#include"Application/Common/CommonAPI.h"
#include"Application/Input/Input.h"

void C_EnemyMove2::Init(PosPattern pospattern, MovePattern movepattern, std::shared_ptr<C_Player> player, int i)
{
	//プレイヤーのインスタンス
	m_player = move(player);

	m_shot = std::make_shared<C_Shot>();

	//アニメーション用
	m_anim = { 0,0 };

	//座標
	switch (pospattern)
	{
	case PosPattern::Pattern1:
		m_pos = { /*(float)(i * 60) +*/ 700, (float)200 - INFO.HUDAreaHeight};
		break;
	case PosPattern::Pattern2:
		m_pos = { /*(float)(i * 60) + */ 700, (float)-200 - INFO.HUDAreaHeight};
		break;
	case PosPattern::Pattern3:
		//m_pos = { 0,(float)(i * 60) + 400 };
		break;
	case PosPattern::Pattern4:
		//m_pos = { 0,(float)(i * 60) - 400 };
		break;
	default:
		break;
	}

	//移動量
	switch (movepattern)
	{
	case MovePattern::Pattern1:
		m_movespeed = { 4,4 };
		m_shotpos = { 400,(float)200 - INFO.HUDAreaHeight };
		m_angle = atan2(m_shotpos.y - m_pos.y, m_shotpos.x - m_pos.x);
		m_move.x = cosf(m_angle) * m_movespeed.x;
		m_move.y = sinf(m_angle) * m_movespeed.y;
		break;
	case MovePattern::Pattern2:
		m_movespeed = { 4,4 };
		m_shotpos = { 400,(float)200 - INFO.HUDAreaHeight };
		m_angle = atan2(m_shotpos.y - m_pos.y, m_shotpos.x - m_pos.x);
		m_move.x = cosf(m_angle) * m_movespeed.x;
		m_move.y = sinf(m_angle) * m_movespeed.y;
		break;
	case MovePattern::Pattern3:
		m_movespeed = { -2,1 };
		m_move = m_movespeed;
		break;
	case MovePattern::Pattern4:
		m_movespeed = { 0,-2 };
		m_move = m_movespeed;
		break;
	case MovePattern::Pattern5:
		m_movespeed = { 0,2 };
		m_move = m_movespeed;
		break;
	default:
		break;
	}

	//サイズ
	m_scale = { 1,1 };
	//カラー
	m_color = { 1,1,1,1 };
	//生存フラグ
	m_alive = true;
	//発射間隔時間
	m_shotintervaltime = 5 * 60;
	//発射間隔
	m_shotinterval = 0;

	//固有行動
	m_inherentmove = InherentMove::Start;
	//ストップカウント
	m_stopcount = 0;
}
void C_EnemyMove2::Update()
{
	if (m_inherentmove == InherentMove::Start)
	{
		m_pos += m_move;

		if (m_pos.x < m_shotpos.x)
		{
			m_inherentmove = InherentMove::Stop;
			m_move = { 0,0 };
			m_stopcount = m_stopcountmax;
		}
	}
	else if (m_inherentmove == InherentMove::Stop)
	{
		m_stopcount--;

		if (m_stopcount < 0)
		{
			m_inherentmove = InherentMove::Shot;

			m_angle = atan2(m_player->GetPlayerPos().y - m_pos.y, m_player->GetPlayerPos().x - m_pos.x);
			m_move.x = cosf(m_angle) * m_movespeed.x;
			m_move.y = sinf(m_angle) * m_movespeed.y;
		}
	}
	else if (m_inherentmove == InherentMove::Shot)
	{
		m_shotangle = atan2(m_player->GetPlayerPos().y - m_pos.y, m_player->GetPlayerPos().x - m_pos.x) - DirectX::XMConvertToRadians(90);

		for (int i = 0; i < 5; i++)
		{
			float keep = m_shotangle;

			m_shotangle += DirectX::XMConvertToRadians(i * 45);
			m_shot->ShotManager(ShotType::NormalShot, ShotTextureType::Bolt, { 4,0 }, { 48,32 },
				m_pos, m_shotangle,6);

			m_shotangle = keep;
		}

		m_stopcount = m_stopcountmax;

		m_inherentmove = InherentMove::Stop2;
	}
	else if (m_inherentmove == InherentMove::Stop2)
	{
		m_stopcount--;

		if (m_stopcount < 0)
		{
			m_inherentmove = InherentMove::ReStart;

			m_angle = atan2(m_player->GetPlayerPos().y - m_pos.y, m_player->GetPlayerPos().x - m_pos.x);
			m_move.x = cosf(m_angle) * m_movespeed.x*2;
			m_move.y = sinf(m_angle) * m_movespeed.y*2;
		}
	}
	else if(m_inherentmove==InherentMove::ReStart)
	{
		m_pos += m_move;
	}
	m_shot->Update();

	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}
void C_EnemyMove2::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_tex,0,0,&Math::Rectangle(0,0,m_rect.x,m_rect.y), &m_color);
	
	m_shot->Draw();
}
void C_EnemyMove2::Release()
{

}
