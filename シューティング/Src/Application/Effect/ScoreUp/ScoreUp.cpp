#include "ScoreUp.h"
#include"../../Common/CommonAPI.h"
#include"../../Scenes/SceneManager.h"

void C_ScoreUp::Release()
{
	m_tex.reset();
}

void C_ScoreUp::Init(Math::Vector2 pos,int value)
{
	//À•W‘ã“ü
	m_pos = pos;
	m_value = value;
	m_scale = 0.35f;
	m_alive = true;
	m_alpha = 1;
	m_rect = { 100,100 };
}

void C_ScoreUp::Update()
{
	m_pos.y += 1.0f;

	m_alpha -= 0.02f;
	if (m_alpha <= 0)
	{
		Kill();
	}
}

void C_ScoreUp::Draw()
{
	Math::Color color = { 1,1,0,m_alpha };
	if(SCENEMANAGER.GetNowSceneType() == SceneType::Game2)
	{
		color = { 1,1,1,m_alpha };
	}
	COMMONAPI.NumDraw(m_value, m_pos, { 0.15f,0.15f }, color);

	std::shared_ptr<KdTexture> tex = m_tex.lock();

	if (tex)
	{
		//s—ñ
		m_scalemat = Math::Matrix::CreateScale(m_scale);
		m_transmat = Math::Matrix::CreateTranslation(m_pos.x - 80, m_pos.y, 0);
		m_mat = m_scalemat * m_transmat;

		Math::Rectangle rect = { 0,0,(long)m_rect.x,(long)m_rect.y };
		Math::Color color = { 1,1,1,m_alpha };

		// ÀÛ‚Í‚¨‘O‚ÌŠÂ‹«‚Ì•`‰æAPI‚É‡‚í‚¹‚Ä‘‚­
		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_mat);
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(tex.get(), 0, 0, &rect, &color);
	}
}
