#include "TitleUi.h"
#include"../../Common/CommonTexture.h"
#include"../../Player/Player.h"

void C_TitleUi::Init()
{
	//背景初期化
	BackGroundInit();

	//タイトル初期化
	TitleLogoInit();

	//スタート初期化
	StartInit();

	//プレイヤー
	PlayerInit();

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

	//プレイヤー
	PlayerUpdate();
	
	//ボタン更新
	CreateSpriteItemUpdate();
}

void C_TitleUi::Draw()
{
	//背景描画
	BackGroundDraw();

	//タイトル描画
	TitleLogoDraw();

	//スタート描画
	StartDraw();

	//プレイヤー
	PlayerDraw();

	//ボタン更新
	CreateSpriteItemDraw();
}

//背景
void C_TitleUi::BackGroundInit()
{

	//背景
	m_backgroundtex.Load("Texture/Ui/BackGround/Title/TitleBackGround.png");

	m_movebackgroundtex.Load("Texture/Ui/BackGround/Title/TitleMoveBackGround.png");
	m_movebackgroundpos = { 0,0 };

	m_movebackgroundrect = { 0,0,11520,720 };
	m_movebackgroundpos2 = { m_movebackgroundpos.x + m_movebackgroundrect.width,0 };

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

	m_movebackgroundpos.x -= 3.0f;
	m_movebackgroundpos2.x -= 3.0f;

	if (m_movebackgroundpos.x <= -m_movebackgroundrect.width)
	{
		m_movebackgroundpos.x = m_movebackgroundpos2.x + m_movebackgroundrect.width;
	}
	if (m_movebackgroundpos2.x <= -m_movebackgroundrect.width)
	{
		m_movebackgroundpos2.x = m_movebackgroundpos.x + m_movebackgroundrect.width;
	}

	m_backgroundscalemat = Math::Matrix::CreateScale(m_backgroundscale.x, m_backgroundscale.y, 1);
	m_backgroundtransmat = Math::Matrix::CreateTranslation(m_backgroundpos.x, m_backgroundpos.y, 0);
	m_backgroundmat = m_backgroundscalemat * m_backgroundtransmat;

	m_movebackgroundmat = Math::Matrix::CreateTranslation(m_movebackgroundpos.x, m_movebackgroundpos.y, 1);
	m_movebackgroundmat2 = Math::Matrix::CreateTranslation(m_movebackgroundpos2.x, m_movebackgroundpos2.y, 1);
}
void C_TitleUi::BackGroundDraw()
{
	//黒背景
	BlackBackDraw();

	//背景
	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_backgroundmat);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_backgroundtex, 0, 0, &Math::Rectangle(0,0, m_backgroundrect.width, m_backgroundrect.height), &m_backgroundcolor);

	Math::Color color = { 10.0f,10.0f,10.0f,0.2f };

	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_movebackgroundmat);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_movebackgroundtex,0,0, &m_movebackgroundrect,&color);

	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_movebackgroundmat2);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_movebackgroundtex,0,0, &m_movebackgroundrect,&color);
}

void C_TitleUi::Release()
{
	m_backgroundtex.Release();
	m_titlelogotex.Release();
	m_movebackgroundtex.Release();
}


void C_TitleUi::StartInit()
{
	m_startpos = {0,-230};

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
	Math::Rectangle r= { 0,0,1500,100 };
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_starttex.get(), 0, 0, &r, &color);
}

void C_TitleUi::TitleLogoInit()
{
	m_titlelogotex.Load("Texture/Ui/Font/COPYSYSTEM.png");
}

void C_TitleUi::TitleLogoDraw()
{
	Math::Vector2 pos = { 0,200 };
	Math::Vector2 scale = { 0.9f,1 };

	Math::Matrix s = Math::Matrix::CreateScale(scale.x,scale.y,1);
	Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
	Math::Matrix mat = s * t;

	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
	Math::Rectangle rect = { 0,0,1107,132 };
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_titlelogotex, rect, 1.0f);
}

void C_TitleUi::PlayerInit()
{
	m_player = std::make_shared<C_Player>();

	//プレイヤーエンジン
	std::shared_ptr<KdTexture> playerenginetex = std::make_shared<KdTexture>();
	playerenginetex->Load("Texture/Player/PlayerEngine_01.png");
	m_playerenginetexs.push_back(playerenginetex);
	playerenginetex = std::make_shared<KdTexture>();
	playerenginetex->Load("Texture/Player/PlayerEngine_02.png");
	m_playerenginetexs.push_back(playerenginetex);
	playerenginetex = std::make_shared<KdTexture>();
	playerenginetex->Load("Texture/Player/PlayerEngine_03.png");
	m_playerenginetexs.push_back(playerenginetex);

	m_player->SetEngineTex(m_playerenginetexs);

	m_player->TitleInit();
}
void C_TitleUi::PlayerUpdate()
{
	m_player->TitleUpdate();
}
void C_TitleUi::PlayerDraw()
{
	m_player->TitleDraw();
}