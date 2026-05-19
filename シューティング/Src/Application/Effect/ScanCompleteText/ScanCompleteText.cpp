#include"ScanCompleteText.h"
#include"../../Common/CommonTexture.h"

void C_ScanCompleteText::Release()
{
}

void C_ScanCompleteText::Init(Math::Vector2 pos)
{
	//ç¿ïWë„ì¸
	m_pos = pos;
	m_scale = 1.0f;
	m_rect = { 256,64 };
	m_alive = true;
	m_alpha = 1;
}

void C_ScanCompleteText::Update()
{
	m_pos.y += 1.0f;

	m_alpha -= 0.02f;
	if (m_alpha <= 0)
	{
		Kill();
	}
}

void C_ScanCompleteText::Draw()
{
	//ï`âÊ
	{
		//çsóÒ
		m_scalemat = Math::Matrix::CreateScale(m_scale);
		m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
		m_mat = m_scalemat * m_transmat;

		Math::Rectangle rect = { 0,0,480,100 };
		Math::Color color = { 1,1,1,m_alpha };

		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_mat);
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(&CommonTex.GetScanCompleteTextTex(), 0, 0, &rect, &color);
	}
}