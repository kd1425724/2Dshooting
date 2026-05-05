#pragma once
#include"Application/Scenes/SceneBase.h"

class C_TitleUi;

class C_Title:public C_SceneBase
{
public:
	C_Title(){}
	~C_Title()override{}

	void Init()override;
	void Update()override;
	void Draw()override;
private:

	//リリース
	void Release()override;

	//Ui
	std::shared_ptr<C_TitleUi> m_titleui;

	//スタートテクスチャ
	std::shared_ptr<KdTexture> m_starttex;

};
