#include "CommonTexture.h"

//ロード用
C_CommonTexture::C_CommonTexture()
{
	//フェード用
	m_whitebacktex.Load("Texture/Ui/WhiteBack.png");
	//プレイヤー
	m_playertex.Load("Texture/Player/Player.png");
}
//解放用
C_CommonTexture::~C_CommonTexture()
{
	//フェード用
	m_whitebacktex.Release();
	//プレイヤー
	m_playertex.Release();
}

