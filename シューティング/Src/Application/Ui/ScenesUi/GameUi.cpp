#include "GameUi.h"
#include"Application/Common/CommonTexture.h"

void C_GameUi::TextureLoad()
{
	//背景
	m_backgroundtex.Load("Texture/Ui/BackGround/Game/GameBackGround.png");
	//HUDエリア
	m_HUDareatex.Load("Texture/Ui/HUD/GameHUDArea.png");
}

void C_GameUi::Init()
{
	BackGroundInit();

	HUDInit();
}

void C_GameUi::Update()
{
	BackGroundUpdate();

	HUDUpdate();
}

void C_GameUi::Draw()
{
	HUDDraw();
}

//背景
void C_GameUi::BackGroundInit()
{
	//黒背景
	BlackBackInit();

	//座標
	m_backgroundpos = { 0,0 };
	//サイズ
	m_backgroundscale = { 1.0f,1.0f };
	//アニメーション用
	m_backgroundanim = { 0,0 };
	//切り取り範囲
	m_backgroundrect = { 0,0,580,9280 };
	//アニメーション用
	m_backgroundanim = { 0,0 };
	//カラー
	m_backgroundcolor = { 1,1,1,1 };
}
void C_GameUi::BackGroundUpdate()
{
	//黒背景
	BlackBackUpdate();

	m_backgroundpos.y += 1.5f;

	m_backgroundscalemat = Math::Matrix::CreateScale(m_backgroundscale.x, m_backgroundscale.y, 1);
	m_backgroundtransmat = Math::Matrix::CreateTranslation(m_backgroundpos.x, m_backgroundpos.y, 0);
	m_backgroundmat = m_backgroundscalemat * m_backgroundtransmat;
}
void C_GameUi::BackGroundDraw()
{
	//黒背景
	BlackBackDraw();

	SHADER.m_spriteShader.SetMatrix(m_backgroundmat);
	SHADER.m_spriteShader.DrawTex(&m_backgroundtex, 0, 0, &Math::Rectangle(/*(int)m_backgroundanim.x *  m_backgroundrect.width*/0, m_backgroundrect.y, m_backgroundrect.width, m_backgroundrect.height), &m_backgroundcolor);
}

void C_GameUi::HUDInit()
{
	//共通
	m_HUDarearect = { 0,0,350,720 };
	m_HUDareascale = { 1.0f,1.0f };
	m_HUDareacolor = { 1.0f,1.0f,1.0f,1 };

	//左
	m_HUDareapos[LeftArea] = { -465,0 };

	//右
	m_HUDareapos[RightArea] = { 465,0 };
}

void C_GameUi::HUDUpdate()
{
	for (int i = 0; i < HUDAreaNum; i++)
	{
		m_HUDareascalemat = Math::Matrix::CreateScale(m_HUDareascale.x, m_HUDareascale.y, 1);
		m_HUDareatransmat[i] = Math::Matrix::CreateTranslation(m_HUDareapos[i].x, m_HUDareapos[i].y, 0);
		m_HUDareamat[i] = m_HUDareascalemat * m_HUDareatransmat[i];
	}
}

void C_GameUi::HUDDraw()
{
	for (int i = 0; i < HUDAreaNum; i++)
	{
		SHADER.m_spriteShader.SetMatrix(m_HUDareamat[i]);
		SHADER.m_spriteShader.DrawTex(&m_HUDareatex, 0, 0, &m_HUDarearect, &m_HUDareacolor);
	}
}
