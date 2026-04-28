#pragma once
#include"Application/Scenes/SceneBase.h"
#include"Application/Ui/ScenesUi/TitleUi.h"

class C_Title:public C_SceneBase
{
public:
	C_Title(){}
	~C_Title()override{}

	void Init()override;
	void Update()override;
	void Draw()override;

	void StartButtonProcess();

private:

	//画像ロード
	void TextureLoad()override;

	//リリース
	void Release()override;

	//Ui
	C_TitleUi m_titleui;

};
