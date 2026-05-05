#include "TitleUi.h"
#include"Application/Common/CommonTexture.h"

void C_TitleUi::Init()
{
	//背景初期化
	BackGroundInit();

	//タイトル初期化
	TitleNameInit();

	//スタート初期化
	StartInit();

	//画像作成
	//CreateSpriteItemInit({ -300,0 }, { 0,0,1280,720 }, { 0.1,0.1 }, &CommonTex.GetWhiteBackTex(), {1,1,1,1});
	//CreateSpriteItemInit({ 300,0 }, { 0,0,1280,720 }, { 0.1,0.1 }, &CommonTex.GetWhiteBackTex(), {1,1,1,1});
}

void C_TitleUi::Update()
{
	//背景更新
	BackGroundUpdate();

	//スタート更新
	StartUpdate();
	
	//ボタン更新
	CreateSpriteItemUpdate();
}

void C_TitleUi::Draw()
{
	//背景描画
	BackGroundDraw();

	//タイトル描画
	TitleNameDraw();

	//スタート描画
	StartDraw();

	//ボタン更新
	CreateSpriteItemDraw();
}

//背景
void C_TitleUi::BackGroundInit()
{

	//背景
	m_backgroundtex.Load("Texture/Ui/BackGround/Title/TitleBackGround.png");

	//黒背景
	BlackBackInit();

	//座標
	m_backgroundpos = {0,0 };
	//サイズ
	m_backgroundscale = { 1.0f,1.0f };
	//アニメーション用
	m_backgroundanim = { 0,0 };
	//切り取り範囲
	m_backgroundrect = { 0,0,1280,720 };
	//アニメーション用
	m_backgroundanim = { 0,0 };
	//カラー
	m_backgroundcolor = { 1,1,1,1 };
}
void C_TitleUi::BackGroundUpdate()
{
	//黒背景
	BlackBackUpdate();

	m_backgroundscalemat = Math::Matrix::CreateScale(m_backgroundscale.x, m_backgroundscale.y, 1);
	m_backgroundtransmat = Math::Matrix::CreateTranslation(m_backgroundpos.x, m_backgroundpos.y, 0);
	m_backgroundmat = m_backgroundscalemat * m_backgroundtransmat;
}
void C_TitleUi::BackGroundDraw()
{
	//黒背景
	BlackBackDraw();

	//背景
	SHADER.m_spriteShader.SetMatrix(m_backgroundmat);
	SHADER.m_spriteShader.DrawTex(&m_backgroundtex, 0, 0, &Math::Rectangle(0,0, m_backgroundrect.width, m_backgroundrect.height), &m_backgroundcolor);
}

void C_TitleUi::Release()
{
	m_backgroundtex.Release();
}

void C_TitleUi::TitleNameInit()
{
	m_titlepos = { 0,200 };
}
void C_TitleUi::TitleNameDraw()
{
	//KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_titletex.get(), m_titlepos.x, m_titlepos.y);
}

void C_TitleUi::StartInit()
{
	m_startpos = {0,-200};

	m_startalpha = 1;

	m_startscale = { 0.5f,0.5f };

	m_startalphapattern = StartAlphaPattern::Down;
}
void C_TitleUi::StartUpdate()
{
	if (m_startalphapattern == StartAlphaPattern::Down)
	{
		m_startalpha -= 0.01f;
		if (m_startalpha < 0.3f)
		{
			m_startalpha = 0.3f;
			m_startalphapattern = StartAlphaPattern::Up;
		}
	}
	if (m_startalphapattern == StartAlphaPattern::Up)
	{
		m_startalpha += 0.01f;
		if (m_startalpha > 1.0f)
		{
			m_startalpha = 1.0f;
			m_startalphapattern = StartAlphaPattern::Down;
		}
	}
}
void C_TitleUi::StartDraw()
{
	Math::Matrix scale = Math::Matrix::CreateScale(m_startscale.x, m_startscale.y, 1);
	Math::Matrix mat = scale*Math::Matrix::CreateTranslation(m_startpos.x, m_startpos.y, 0);

	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
	Math::Color color = { 1,1,1,m_startalpha };
	Math::Rectangle r= { 0,0,480,97 };
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_starttex.get(), 0, 0, &r, &color);
}
