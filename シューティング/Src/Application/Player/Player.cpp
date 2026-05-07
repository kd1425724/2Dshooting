#include "Player.h"
#include"../Common/CommonTexture.h"
#include"../Input/Input.h"
#include"../Skill/Shot/Shot.h"
#include"../Info.h"
#include"../Hit/HitManager.h"
#include"../Effect/EffectManager.h"
#include"../Common/CommonAPI.h"
#include"../Scenes/Game/Game.h"

void C_Player::Init()	
{
	ShotInit();

	m_Hp = 3;

	//座標
	m_pos = { -300,0 - (float)INFO.HUDAreaHeight/2 };
	//移動量
	m_move = { 0.0f,0.0f };
	m_movespeed = { 8.0f,8.0f };
	//サイズ
	m_scale = { 1.2f,1.2f };
	//カラー
	m_color = { 1,1,1,1 };
	//切り取り範囲
	m_rect = { (float)CommonTex.GetPlayerRect().width,(float)CommonTex.GetPlayerRect().height };

	//半径
	m_halfsize = m_rect * m_scale / 2;
	m_radius = m_rect.x /** m_scale.x *//3;

	//当たり判定用
	if (m_hitmanager)
	{
		m_hitmanager->SetPlayer(shared_from_this());
	}

	m_engineanim = 0;

	m_alive = true;

}
void C_Player::Update()
{
	//当たった時
	HitUpdate();

	ShotUpdate();

	m_move = { 0,0 };

	if (Input.GetPlayerKey(PlayerKeyType::Top))
	{
		m_move.y = 1.0f;
	}
	else if (Input.GetPlayerKey(PlayerKeyType::Bottom))
	{
		m_move.y = -1.0f; 
	}
	if (Input.GetPlayerKey(PlayerKeyType::Left))
	{
		m_move.x = -1.0f;
	}
	else if (Input.GetPlayerKey(PlayerKeyType::Right))
	{
		m_move.x = 1.0f;
	}
	m_move.Normalize();

	//エンジンアニメーション用
	m_engineanim += 0.1f;
	if (m_engineanim >= m_enginetexs.size())
	{
		m_engineanim = 0;
	}

	m_pos += m_move * m_movespeed;
	
	m_scalemat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1);
	m_transmat = Math::Matrix::CreateTranslation((int)(m_pos.x+0.5f), (int)(m_pos.y+0.5f), 0);//+0.5f四捨五入してる
	m_mat = m_scalemat * m_transmat;

	if (m_Hp <= 0)
	{
		m_alive = false;
	}
}
void C_Player::Draw()
{
	
	Math::Color color = { 1,1,1,1 };
	Math::Rectangle enginerect = { 0,0, 64,64 };

	Math::Matrix enginscale = Math::Matrix::CreateScale(0.8f, 0.8f, 0);
	Math::Matrix engintrans = Math::Matrix::CreateTranslation((int)(m_pos.x - 60+0.5f), (int)(m_pos.y+0.5f), 0);

	Math::Matrix mat = enginscale * engintrans;
	
	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_enginetexs[(int)m_engineanim].get(), 0, 0, &enginerect, &color);

	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_mat);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(&CommonTex.GetPlayerTex(), 0, 0, &CommonTex.GetPlayerRect(), &m_color);
}

void C_Player::ResultInit()
{
	//座標
	m_pos = { 700,0 - (float)INFO.HUDAreaHeight / 2 };
	//移動量
	m_move = { 0.0f,0.0f };
	m_movespeed = { 4.0f,4.0f };
	//サイズ
	m_scale = { 1.0f,1.0f };
	//カラー
	m_color = { 1,1,1,1 };
	//切り取り範囲
	m_rect = { (float)CommonTex.GetPlayerRect().width,(float)CommonTex.GetPlayerRect().height };

	//半径
	m_halfsize = m_rect * m_scale / 2;
	m_radius = m_rect.x /** m_scale.x */ / 3;

	m_engineanim = 0;
}

void C_Player::ResultUpdate()
{
	m_move = { -1,0 };

	//エンジンアニメーション用
	m_engineanim += 0.1f;
	if (m_engineanim >= m_enginetexs.size())
	{
		m_engineanim = 0;
	}



	if (COMMONAPI.OutOfScreen(m_pos, { (float)CommonTex.GetPlayerRect().width,(float)CommonTex.GetPlayerRect().height / 2 }))
	{
		m_pos.x = (float)INFO.ScrWidth / 2 + (float)CommonTex.GetPlayerRect().width;
	}
	m_pos += m_move * m_movespeed;
	
	m_scalemat = Math::Matrix::CreateScale(-m_scale.x, m_scale.y, 1);
	m_transmat = Math::Matrix::CreateTranslation((int)(m_pos.x + 0.5f), (int)(m_pos.y + 0.5f), 0);//+0.5f四捨五入してる
	m_mat = m_scalemat * m_transmat;
}

void C_Player::ResultDraw()
{
	Math::Color color = { 1,1,1,1 };
	Math::Rectangle enginerect = { 0,0, 64,64 };

	Math::Matrix enginscale = Math::Matrix::CreateScale(-0.8f, 0.8f, 0);
	Math::Matrix engintrans = Math::Matrix::CreateTranslation((int)(m_pos.x + 60 + 0.5f), (int)(m_pos.y + 0.5f), 0);

	Math::Matrix mat = enginscale * engintrans;

	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_enginetexs[(int)m_engineanim].get(), 0, 0, &enginerect, &color);

	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_mat);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(&CommonTex.GetPlayerTex(), 0, 0, &CommonTex.GetPlayerRect(), &m_color);

}

void C_Player::Release()
{
}
void C_Player::ImGui()
{
	ImGui::Text("\nPlayerHP : %d",m_Hp);
}

void C_Player::ShotInit()
{
	m_shotinterval = 0;
}

void C_Player::ShotUpdate()
{

	//通常攻撃
	if (m_shotinterval <= 0)
	{
		if (Input.GetPlayerKey(PlayerKeyType::NormalShot))
		{
			auto s = std::make_shared<C_Shot>();
			auto o = m_owner.lock();

			if (s && o)
			{

				s->SetHitManager(m_hitmanager);

				s->ShotManager(ShotType::NormalShot, ShotTextureType::Pulse, { 4,0 }, { 63,32 },
					m_pos, { m_pos.x + 100,m_pos.y + 10 }, 18);
				s->ShotManager(ShotType::NormalShot, ShotTextureType::Bolt, { 4,0 }, { 48,32 },
					m_pos, { m_pos.x + 100,m_pos.y }, 18);
				s->ShotManager(ShotType::NormalShot, ShotTextureType::Pulse, { 4,0 }, { 63,32 },
					m_pos, { m_pos.x + 100,m_pos.y - 10 }, 18);
			
				o->SetShot(s);
				
			}

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

void C_Player::Damage()
{
	if (m_hittimer <= 0)
	{
		m_Hp--;

		m_hittimer = HitTime;

		EFFECTMANAGER.AddEffect(EffectType::Explosion, m_pos);
	}
}

void C_Player::HitUpdate()
{
	if (m_hittimer > 0)
	{
		m_hittimer--;

		if ((m_hittimer / 2) % 2 == 0)
		{
			m_color = { 1.5f, 1.5f, 1.5f, 1.0f }; // 明るく（白っぽく）
		}
		else
		{
			m_color = { 1.0f, 1.0f, 1.0f, 1.0f }; // 通常
		}
	}
}