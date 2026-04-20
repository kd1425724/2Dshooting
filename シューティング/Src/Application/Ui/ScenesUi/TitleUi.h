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
	~C_TitleUi(){}

	void Init()override;
	void Update()override;
	void Draw()override;

	//画像ロード
	void TextureLoad()override;

	//背景用
	void BackGroundInit()override;
	void BackGroundUpdate()override;
	void BackGroundDraw()override; 
	

private:

};
