#pragma once
#include"Application/Ui/ScenesUi/ScenesUiBase.h"

class C_GameUi :public C_ScenesUiBase
{
public:
	C_GameUi() {}
	~C_GameUi() {}

	void Init()		override;
	void Update()	override;
	void Draw()		override;

	//画像ロード
	void TextureLoad()override;

	//背景用
	void BackGroundInit()	override;
	void BackGroundUpdate()	override;
	void BackGroundDraw()	override;

	
private:

	//HUD用///
	 //HUD
	void HUDInit();
	void HUDUpdate();
	void HUDDraw();

	//画像
	KdTexture m_HUDareatex;
	//切り取り範囲
	Math::Rectangle m_HUDarearect;
	//行列
	Math::Matrix m_HUDareascalemat;
	Math::Matrix m_HUDareatransmat;
	Math::Matrix m_HUDareamat;
	//座標
	Math::Vector2 m_HUDareapos;
	//サイズ
	Math::Vector2 m_HUDareascale;
	//カラー
	Math::Color m_HUDareacolor;
	////////////
};
