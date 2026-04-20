#pragma once
#include"Application/Scenes/SceneBase.h"
#include"Application/Ui/ScenesUi/GameUi.h"
#include"Application/Prayer/Player.h"

class C_Game:public C_SceneBase
{
public:
	C_Game(){}
	~C_Game(){}

	void Init()override;
	void Update()override;
	void Draw()override;

	//画像ロード
	void TextureLoad()override;

private:

	//Ui
	C_GameUi m_gameui;

	//プレイヤー
	C_Player m_player;
};