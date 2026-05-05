#include "GameUi.h"
#include"Application/Common/CommonTexture.h"
#include"Application/Info.h"

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

	//背景
	m_backgroundtex.Load("Texture/Ui/BackGround/Game/GameBackGround.png");

	//黒背景
	BlackBackInit();

	//座標
	m_backgroundpos = { 0,0 };
	//サイズ
	m_backgroundscale = { 1.0f,1.0f };
	//アニメーション用
	m_backgroundanim = { 0,0 };
	//切り取り範囲
	m_backgroundrect = { 0,0,4096,4096 };
	//アニメーション用
	m_backgroundanim = { 0,0 };
	//カラー
	m_backgroundcolor = { 1,1,1,1 };

	m_backgroundpos2 = { m_backgroundpos.x + m_backgroundrect.width,0 };
}
void C_GameUi::BackGroundUpdate()
{
	//黒背景
	BlackBackUpdate();

	m_backgroundpos.x -= 6.0f;
	m_backgroundpos2.x -= 6.0f;

	if (m_backgroundpos.x <= -m_backgroundrect.width)
	{
		m_backgroundpos.x = m_backgroundpos2.x+ m_backgroundrect.width;
	}
	if (m_backgroundpos2.x <= -m_backgroundrect.width)
	{
		m_backgroundpos2.x = m_backgroundpos.x+ m_backgroundrect.width;
	}

	m_backgroundscalemat = Math::Matrix::CreateScale(m_backgroundscale.x, m_backgroundscale.y, 1);
	m_backgroundtransmat = Math::Matrix::CreateTranslation(m_backgroundpos.x, m_backgroundpos.y, 0);
	m_backgroundmat = m_backgroundscalemat * m_backgroundtransmat;

	m_backgroundtransmat2 = Math::Matrix::CreateTranslation(m_backgroundpos2.x, m_backgroundpos.y, 0);
	m_backgroundmat2 = m_backgroundtransmat2;
}
void C_GameUi::BackGroundDraw()
{
	//黒背景
	BlackBackDraw();

	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_backgroundmat);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_backgroundtex, 0, 0, &Math::Rectangle(0, 0, m_backgroundrect.width, m_backgroundrect.height), &m_backgroundcolor);
	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_backgroundmat2);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_backgroundtex, 0, 0, &Math::Rectangle(0, 0, m_backgroundrect.width, m_backgroundrect.height), &m_backgroundcolor);
}

void C_GameUi::Release()
{
	m_backgroundtex.Release();
	m_HUDareatex.Release();
}

void C_GameUi::HUDInit()
{
	//HUDエリア
	m_HUDareatex.Load("Texture/Ui/HUD/GameHUDArea.png");

	//共通
	m_HUDarearect = { 0,0,INFO.HUDAreaWidth ,INFO.HUDAreaHeight };
	m_HUDareascale = { 1.0f,1.0f };
	m_HUDareacolor = { 1.0f,1.0f,1.0f,1 };

	
	m_HUDareapos = { 0,(float)INFO.ScrHeight / 2 - INFO.HUDAreaHeight / 2 };
}

void C_GameUi::HUDUpdate()
{
	
	m_HUDareascalemat = Math::Matrix::CreateScale(m_HUDareascale.x, m_HUDareascale.y, 1);
	m_HUDareatransmat = Math::Matrix::CreateTranslation(m_HUDareapos.x, m_HUDareapos.y, 0);
	m_HUDareamat = m_HUDareascalemat * m_HUDareatransmat;
	
}

void C_GameUi::HUDDraw()
{
	
	SHADER.m_spriteShader.SetMatrix(m_HUDareamat);
	SHADER.m_spriteShader.DrawTex(&m_HUDareatex, 0, 0, &m_HUDarearect, &m_HUDareacolor);
	
}
