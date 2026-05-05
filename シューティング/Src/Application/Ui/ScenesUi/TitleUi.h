#pragma once
#include"Application/Ui/ScenesUi/ScenesUiBase.h"

enum TitleButton
{
	START,	//スタートボタン
	w
};

class C_TitleUi:public C_ScenesUiBase
{
public:
	C_TitleUi(){}
	~C_TitleUi()override { Release(); }

	void Init()override;
	void Update()override;
	void Draw()override;

	//スタートテクスチャセット
	void SetStartTex(std::shared_ptr<KdTexture> tex) { m_starttex = tex; }

	//背景用
	void BackGroundInit()override;
	void BackGroundUpdate()override;
	void BackGroundDraw()override; 

private:

	void Release()override;

	//タイトル用
	void TitleNameInit();
	void TitleNameDraw();
	//座標
	Math::Vector2 m_titlepos;
	//テクスチャ
	//std::shared_ptr<KdTexture> m_titletex;
	//スタート
	void StartInit();
	void StartUpdate();
	void StartDraw();

	enum class StartAlphaPattern
	{
		None,
		Up,
		Down
	};
	//座標
	Math::Vector2 m_startpos;
	//テクスチャ
	std::shared_ptr<KdTexture> m_starttex;
	//点滅用
	float m_startalpha;
	Math::Vector2 m_startscale;

	StartAlphaPattern m_startalphapattern = StartAlphaPattern::None;

};
