#include "WarningLine.h"

void C_WarningLine::Init(Math::Vector2 pos, Math::Vector2 scale,int time)
{
	m_linescale = scale;
	m_pos = pos;
	m_linetime = time;
	m_rect = { 100,36 };
	m_alive = true;
	m_alpha = 0;

	m_linealpha = LineAlpha::Up;
}

void C_WarningLine::Update()
{
	if (m_linealpha == LineAlpha::Down)
	{
		m_alpha -= 0.01f;
		if (m_alpha < 0.0f)
		{
			m_alpha = 0.0f;
			m_linealpha = LineAlpha::Up;
		}
	}
	if (m_linealpha == LineAlpha::Up)
	{
		m_alpha += 0.5f / m_linetime;
		if (m_alpha > 0.5f)
		{
			m_alpha = 0.5f;
			Kill();
			m_linealpha = LineAlpha::Down;
		}
	}
}

void C_WarningLine::Draw()
{
	std::shared_ptr<KdTexture> tex = m_tex.lock();

	if (tex)
	{
		//s—ñ
		m_scalemat = Math::Matrix::CreateScale(m_linescale.x, m_linescale.y, 1);
		m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
		m_mat = m_scalemat * m_transmat;

		Math::Rectangle rect = { 0,0,(long)m_rect.x,(long)m_rect.y };
		Math::Color color = { 1,1,1,m_alpha };

		// ÀÛ‚Í‚¨‘O‚ÌŠÂ‹«‚Ì•`‰æAPI‚É‡‚í‚¹‚Ä‘‚­
		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_mat);
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(tex.get(), 0, 0, &rect, &color);
	}
}
