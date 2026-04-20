#pragma once
#
#include"Application/Ui/ScenesUi/ScenesUiBase.h"

//HUDエリア
enum HUDAreaLR 
{
	LeftArea,	//左側
	RightArea,	//右側
	HUDAreaNum
};

class C_GameUi :public C_ScenesUiBase
{
public:
	C_GameUi() {}
	~C_GameUi() {}

	void Init()override;
	void Update()override;
	void Draw()override;

	//画像ロード
	void TextureLoad()override;

	//背景用
	void BackGroundInit()override;
	void BackGroundUpdate()override;
	void BackGroundDraw()override;

	//HUD...左右のUi置く場所
	void HUDInit();
	void HUDUpdate();
	void HUDDraw();

private:

	//HUD用///
	 
	//画像
	KdTexture m_HUDareatex;
	//切り取り範囲
	Math::Rectangle m_HUDarearect;
	//行列
	Math::Matrix m_HUDareascalemat;
	Math::Matrix m_HUDareatransmat[HUDAreaNum];
	Math::Matrix m_HUDareamat[HUDAreaNum];
	//座標
	Math::Vector2 m_HUDareapos[HUDAreaNum];
	//サイズ
	Math::Vector2 m_HUDareascale;
	//カラー
	Math::Color m_HUDareacolor;
	////////////
};
