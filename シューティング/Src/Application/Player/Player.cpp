#include "Player.h"
#include"../Common/CommonTexture.h"
#include"../Input/Input.h"
#include"../Skill/Shot/Shot.h"
#include"../Info.h"
#include"../Hit/HitManager.h"

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

	//îºåa
	m_halfsize = m_rect * m_scale / 2;
	m_radius = m_rect.x /** m_scale.x *// 2;

	//ìñÇΩÇËîªíËóp
	m_hitmanager->SetPlayer(shared_from_this());

}
void C_Player::Update()
{

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

	m_pos += m_move * m_movespeed;
	
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
void C_Player::ImGui()
{
	ImGui::Text("\nPlayerHP : %d",m_Hp);
}

void C_Player::ShotInit()
{
	m_shot = std::make_shared<C_Shot>();
	m_shot->SetHitManager(m_hitmanager);
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
				m_pos, { m_pos.x + 100,m_pos.y },12);
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
