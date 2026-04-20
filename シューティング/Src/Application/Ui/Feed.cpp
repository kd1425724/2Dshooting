#include "Feed.h"
#include"Application/Common/CommonTexture.h"

void C_Feed::FeedInInit(float time)
{
	m_alpha = 1.0f;
	m_delta = 1.0f / time;
	m_state = FeedIn;

	m_feedflg = true;

	m_finishpattern = nullptr;
}

void C_Feed::FeedOutInit(float time, function<void()> finishpattern)
{
	m_alpha = 0.0f;
	m_delta = 1.0f / time;
	m_state = FeedOut;

	m_feedflg = true;

	m_finishpattern = finishpattern;
}
void C_Feed::Update()
{
	if (!m_feedflg) { return; }

	if (m_state == FeedIn)
	{
		m_alpha -= m_delta;
		if (m_alpha <= 0.0f)
		{
			FeedEnd();
		}
	}

	if (m_state == FeedOut)
	{
		m_alpha += m_delta;
		if (m_alpha >= 1.0f)
		{
			FeedEnd();
		}
	}

	m_mat = Math::Matrix::CreateTranslation(0, 0, 0);
}
void C_Feed::Draw()
{
	if (!m_feedflg) { return; }

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&CommonTex.GetWhiteBackTex(), 0, 0, &CommonTex.GetWhiteBackTexRect(), &Math::Color(0, 0, 0, m_alpha));
}

void C_Feed::FeedEnd()
{
	m_alpha = 0.0f;

	m_state = NoFeed;

	//èàóùÇ™ì¸Ç¡ÇƒÇ¢ÇΩÇÁ
	if (m_finishpattern)
	{
		m_finishpattern();
	}
}
