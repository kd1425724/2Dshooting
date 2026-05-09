#pragma once

class C_CommonTexture
{
public:

	//フェード用
	const KdTexture& GetWhiteBackTex()const { return m_whitebacktex; }
	const Math::Rectangle &GetWhiteBackTexRect()const { return m_whitebackrect; }

	//プレイヤー
	const KdTexture& GetPlayerTex()const { return m_playertex; }
	const Math::Rectangle GetPlayerRect()const { return m_playerrect; }
	
	//数字
	const KdTexture& GetNumTex()const { return m_numtex; }
	const Math::Rectangle GetNumRect()const { return m_numrect; }

private:

	//フェード用
	KdTexture m_whitebacktex;
	Math::Rectangle m_whitebackrect = { 0,0,1280,720 };

	//プレイヤー
	KdTexture m_playertex;
	Math::Rectangle m_playerrect = { 0,0,64,64 };

	//数字
	KdTexture m_numtex;
	Math::Rectangle m_numrect = { 0,0,100,100 };

//シングルトン
private:

	C_CommonTexture();
	~C_CommonTexture();

public:
	
	static C_CommonTexture& GetInstans()
	{
		static C_CommonTexture instans;
		return instans;
	}
};
//共通テクスチャ
#define CommonTex C_CommonTexture::GetInstans()
