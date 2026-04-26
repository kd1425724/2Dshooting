#include "Player.h"
#include"Application/Common/CommonTexture.h"
#include"Application/Input/Input.h"
#include"../Skill/Shot/Shot.h"
#include"Application/Info.h"

void C_Player::Init()	
{
	ShotInit();

	//ç¿ïW
	m_pos = { -300,0 - (float)INFO.HUDAreaHeight };
	//à⁄ìÆó 
	m_move = { 0.0f,0.0f };
	m_movespeed = { 9.0f,9.0f };
	//ÉTÉCÉY
	m_scale = { 1.5f,1.5f };
	//ÉJÉâÅ[
	m_color = { 1,1,1,1 };
	//êÿÇËéÊÇËîÕàÕ
	m_rect = { (float)CommonTex.GetPlayerRect().width,(float)CommonTex.GetPlayerRect().height };

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
}

void C_Player::ShotInit()
{
	m_shot = std::make_shared<C_Shot>();

	m_shotinterval = 0;
}

void C_Player::ShotUpdate()
{
	//çUåÇUpdate
	m_shot->Update();

	//í èÌçUåÇ
	if (m_shotinterval <= 0)
	{
		if (Input.GetPlayerKey(PlayerKeyType::NormalShot))
		{
			m_shot->ShotManager(ShotType::NormalShot, ShotTextureType::Bolt, { 4,0 }, { 48,32 },
				m_pos, { m_pos.x + 100,m_pos.y },7);
			m_shotinterval = (int)PlayerShotInterval::NormalShot;
		}
	}

	//í èÌçUåÇî≠éÀä‘äuå∏è≠
	if (m_shotinterval > 0)
	{
		m_shotinterval--;
		if (m_shotinterval <= 0)
		{
			m_shotinterval = 0;
		}
	}
}
