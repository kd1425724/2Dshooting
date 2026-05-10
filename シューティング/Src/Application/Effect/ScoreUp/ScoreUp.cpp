#include "ScoreUp.h"
#include"../../Common/CommonAPI.h"

void C_ScoreUp::Init(Math::Vector2 pos,int value)
{
	//ç¿ïWë„ì¸
	m_pos = pos;
	m_value = value;
	m_scale = 2.0f;
	m_alive = true;
	m_alpha = 1;
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
	Math::Color color = { 1,1,1,m_alpha };
	COMMONAPI.NumDraw(m_value, m_pos, { 0.15f,0.15f }, color);
}
