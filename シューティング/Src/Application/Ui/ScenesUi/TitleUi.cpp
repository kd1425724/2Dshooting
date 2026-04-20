#include "TitleUi.h"
#include"Application/Common/CommonTexture.h"

void C_TitleUi::TextureLoad()
{
	//”wŒi
	m_backgroundtex.Load("Texture/Ui/BackGround/Title/TitleBackGround.png");
}

void C_TitleUi::Init()
{
	//”wŒi‰Šú‰»
	BackGroundInit();

	//‰æ‘œì¬
	CreateSpriteItemInit({ -300,0 }, { 0,0,1280,720 }, { 0.1,0.1 }, &CommonTex.GetWhiteBackTex(), {1,1,1,1});
	CreateSpriteItemInit({ 300,0 }, { 0,0,1280,720 }, { 0.1,0.1 }, &CommonTex.GetWhiteBackTex(), {1,1,1,1});
}

void C_TitleUi::Update()
{
	//”wŒiXV
	BackGroundUpdate();
	
	//ƒ{ƒ^ƒ“XV
	CreateSpriteItemUpdate();
}

void C_TitleUi::Draw()
{
	//”wŒi•`‰æ
	BackGroundDraw();

	//ƒ{ƒ^ƒ“XV
	CreateSpriteItemDraw();
}

//”wŒi
void C_TitleUi::BackGroundInit()
{
	//•”wŒi
	BlackBackInit();

	//À•W
	m_backgroundpos = {0,0 };
	//ƒTƒCƒY
	m_backgroundscale = { 2.0f,2.0f };
	//ƒAƒjƒ[ƒVƒ‡ƒ“—p
	m_backgroundanim = { 0,0 };
	//Ø‚èæ‚è”ÍˆÍ
	m_backgroundrect = { 0,0,640,360 };
	//ƒAƒjƒ[ƒVƒ‡ƒ“—p
	m_backgroundanim = { 0,0 };
	//ƒJƒ‰[
	m_backgroundcolor = { 1,1,1,1 };
}
void C_TitleUi::BackGroundUpdate()
{
	//•”wŒi
	BlackBackUpdate();

	//”wŒi
	m_backgroundanim.x += 0.08f;

	m_backgroundscalemat = Math::Matrix::CreateScale(m_backgroundscale.x, m_backgroundscale.y, 1);
	m_backgroundtransmat = Math::Matrix::CreateTranslation(m_backgroundpos.x, m_backgroundpos.y, 0);
	m_backgroundmat = m_backgroundscalemat * m_backgroundtransmat;
}
void C_TitleUi::BackGroundDraw()
{
	//•”wŒi
	BlackBackDraw();

	//”wŒi
	SHADER.m_spriteShader.SetMatrix(m_backgroundmat);
	SHADER.m_spriteShader.DrawTex(&m_backgroundtex, 0, 0, &Math::Rectangle((int)m_backgroundanim.x * m_backgroundrect.width, m_backgroundrect.y, m_backgroundrect.width, m_backgroundrect.height), &m_backgroundcolor);
}