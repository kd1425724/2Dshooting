#include "ScenesUiBase.h"
#include"Application/Common/CommonTexture.h"
#include"Application/Input/Input.h"

void C_ScenesUiBase::TextureLoad()
{
	return;
}
void C_ScenesUiBase::Init()
{
	return;
}
void C_ScenesUiBase::Update()
{
	return;
}
void C_ScenesUiBase::Draw()
{
	return;
}
void C_ScenesUiBase::BackGroundInit()
{
	return;
}
void C_ScenesUiBase::BackGroundUpdate()
{
	return;
}
void C_ScenesUiBase::BackGroundDraw()
{
	return;
}

//共通背景
void C_ScenesUiBase::BlackBackInit()
{
	//座標
	m_blackbackpos = { 0,0 };
	//カラー
	m_blackbackcolor = { 0.03f,0.03f,0.03f,1 };
}

void C_ScenesUiBase::BlackBackUpdate()
{
	//行列
	m_blackbackmat = Math::Matrix::CreateTranslation(m_blackbackpos.x, m_blackbackpos.y, 0);
}

void C_ScenesUiBase::BlackBackDraw()
{
	SHADER.m_spriteShader.SetMatrix(m_blackbackmat);
	SHADER.m_spriteShader.DrawTex(&CommonTex.GetWhiteBackTex(), 0, 0, &CommonTex.GetWhiteBackTexRect(), &m_blackbackcolor);
}

void C_ScenesUiBase::CreateSpriteItemInit(Math::Vector2 pos, Math::Rectangle rect, Math::Vector2 scale,const KdTexture* tex, Math::Color color)
{
	SpriteItem d;
	d.pos = pos;
	d.rect = rect;
	d.scale = { scale.x, scale.y };
	d.radius = { d.rect.width * scale.x,d.rect.height * scale.y };
	d.color = color;
	d.tex = tex;

	d.action = nullptr;

	//フレーム用
	d.framescale = {d.rect.width * d.scale.x / m_framerect.width,
		d.rect.height * d.scale.y / m_framerect.height };

	m_SpriteItem.push_back(d);
}

void C_ScenesUiBase::CreateSpriteItemUpdate()
{
	for (int i = 0; i < m_SpriteItem.size(); i++)
	{
		m_SpriteItem[i].scaleMat = Math::Matrix::CreateScale(m_SpriteItem[i].scale.x, m_SpriteItem[i].scale.y, 1);
		m_SpriteItem[i].transMat = Math::Matrix::CreateTranslation(m_SpriteItem[i].pos.x, m_SpriteItem[i].pos.y, 1);
		m_SpriteItem[i].mat = m_SpriteItem[i].scaleMat * m_SpriteItem[i].transMat;

		m_SpriteItem[i].framescalemat = Math::Matrix::CreateScale(m_SpriteItem[i].framescale.x, m_SpriteItem[i].framescale.y, 1);
		m_SpriteItem[i].framemat=m_SpriteItem[i].framescalemat * m_SpriteItem[i].transMat;
	}
}

void C_ScenesUiBase::CreateSpriteItemDraw()
{
	for (int i = 0; i < m_SpriteItem.size(); i++)
	{
		SHADER.m_spriteShader.SetMatrix(m_SpriteItem[i].mat);
		SHADER.m_spriteShader.DrawTex(m_SpriteItem[i].tex, 0, 0, &m_SpriteItem[i].rect, &m_SpriteItem[i].color);
	}
	IsOnTopDraw();
}

void C_ScenesUiBase::IsOnTopDraw()
{
	for (int i = 0; i < m_SpriteItem.size(); i++)
	{
		if (m_SpriteItem[i].GetIsOnTop())
		{
			SHADER.m_spriteShader.SetMatrix(m_SpriteItem[i].framemat);
			SHADER.m_spriteShader.DrawTex(&m_frametex, 0, 0, &m_framerect, &Math::Color(1, 1, 1, 1));
		}
	}
}

void C_ScenesUiBase::ClickableUi()
{
	for (int i = 0; i < m_SpriteItem.size(); i++)
	{
		if (m_SpriteItem[i].GetIsOnTop() && Input.GetClickFlg())
		{
			if (m_SpriteItem[i].action)
			{
				m_SpriteItem[i].action();
			}
		}
	}
}

bool SpriteItem::GetIsOnTop()
{
	//マウスが範囲内に入っているときは
	if (Input.GetMousePos().x > pos.x - radius.x / 2 && Input.GetMousePos().x< pos.x + radius.x / 2 &&
		Input.GetMousePos().y> pos.y - radius.y / 2 && Input.GetMousePos().y < pos.y + radius.y / 2)
	{
		return true;
	}
	else
	{
		return false;
	}


	return false;
}

