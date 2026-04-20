#pragma once
#include"Application/Scenes/SceneBase.h"
#include"Application/Ui/ScenesUi/TitleUi.h"

class C_Title:public C_SceneBase
{
public:
	C_Title(){}
	~C_Title(){}

	void Init()override;
	void Update()override;
	void Draw()override;

	//‰æ‘œƒ[ƒh
	void TextureLoad()override;

	void StartButtonProcess();

private:

	//Ui
	C_TitleUi m_titleui;

};
