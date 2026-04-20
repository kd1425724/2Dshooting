#pragma once

class C_CommonTexture
{
public:
	~C_CommonTexture();

	//フェード用
	const KdTexture& GetWhiteBackTex()const { return m_whitebacktex; }
	const Math::Rectangle &GetWhiteBackTexRect()const { return m_whitebackrect; }

	//プレイヤー
	const KdTexture& GetPlayerTex()const { return m_playertex; }
	const Math::Rectangle& GetPlayerRect()const { return m_playerrect; }

private:

	//フェード用
	KdTexture m_whitebacktex;
	Math::Rectangle m_whitebackrect = { 0,0,1280,720 };

	//プレイヤー
	KdTexture m_playertex;
	Math::Rectangle m_playerrect = { 0,0,48,48 };

//シングルトン
private:

	C_CommonTexture();

public:
	
	static C_CommonTexture& GetInstans()
	{
		static C_CommonTexture instans;
		return instans;
	}
};
//共通テクスチャ
#define CommonTex C_CommonTexture::GetInstans()
