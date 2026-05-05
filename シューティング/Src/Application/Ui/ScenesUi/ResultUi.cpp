#include "ResultUi.h"
#include"Application/Common/CommonTexture.h"

void C_ResultUi::Init()
{
	//”wŒi‰Šú‰»
	BackGroundInit();

}

void C_ResultUi::Update()
{
	//”wŒiXV
	BackGroundUpdate();
}

void C_ResultUi::Draw()
{
	//”wŒi•`‰æ
	BackGroundDraw();


}

//”wŒi
void C_ResultUi::BackGroundInit()
{
	//•”wŒi
	BlackBackInit();

	//”wŒi
	m_backgroundtex.Load("Texture/Ui/BackGround/Result/ResultBackGround.png");

	//À•W
	m_backgroundpos = { 0,0 };
	//ƒTƒCƒY
	m_backgroundscale = { 1.0f,1.0f };
	//ƒAƒjƒ[ƒVƒ‡ƒ“—p
	m_backgroundanim = { 0,0 };
	//Ø‚èæ‚è”ÍˆÍ
	m_backgroundrect = { 0,0,1280,720 };
	//ƒAƒjƒ[ƒVƒ‡ƒ“—p
	m_backgroundanim = { 0,0 };
	//ƒJƒ‰[
	m_backgroundcolor = { 1,1,1,1 };
}
void C_ResultUi::BackGroundUpdate()
{
	//•”wŒi
	BlackBackUpdate();

	m_backgroundscalemat = Math::Matrix::CreateScale(m_backgroundscale.x, m_backgroundscale.y, 1);
	m_backgroundtransmat = Math::Matrix::CreateTranslation(m_backgroundpos.x, m_backgroundpos.y, 0);
	m_backgroundmat = m_backgroundscalemat * m_backgroundtransmat;
}
void C_ResultUi::BackGroundDraw()
{
	//•”wŒi
	BlackBackDraw();

	//”wŒi
	SHADER.m_spriteShader.SetMatrix(m_backgroundmat);
	SHADER.m_spriteShader.DrawTex(&m_backgroundtex, 0, 0, &Math::Rectangle((int)m_backgroundanim.x * m_backgroundrect.width, m_backgroundrect.y, m_backgroundrect.width, m_backgroundrect.height), &m_backgroundcolor);
}

void C_ResultUi::Release()
{
	m_backgroundtex.Release();
}
