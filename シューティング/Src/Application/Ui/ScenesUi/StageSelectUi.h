#pragma once
#include"ScenesUiBase.h"

class C_Player;

enum class StageSelectButton
{
	Stage1,
	Stage2,
	BACK
};


class C_StageSelectUi :public C_ScenesUiBase
{
public:
	C_StageSelectUi(){}
	~C_StageSelectUi()override { Release(); }

	void Init()override;
	void Update()override;
	void Draw()override;

	//背景用
	void BackGroundInit()override;
	void BackGroundUpdate()override;
	void BackGroundDraw()override;

private:

	StageSelectButton m_button = StageSelectButton::Stage1;

	//ボタン
	void ButtonFrameDraw();

	//情報
	void StageInfoDraw();

	void Release()override;

	//背景
	void MoveBackGroundInit();
	void MoveBackGroundUpdate();
	void MoveBackGroundDraw();
	KdTexture m_movebackgroundtex;
	Math::Vector2 m_movebackgroundpos = {};
	Math::Vector2 m_movebackgroundpos2 = {};

	Math::Rectangle m_movebackgroundrect = {};

	Math::Matrix m_movebackgroundmat = {};
	Math::Matrix m_movebackgroundmat2 = {};

	// ===== ステージ選択 =====


	  // ===== プレイヤー =====
	void PlayerInit();
	void PlayerUpdate();
	void PlayerDraw();

	std::shared_ptr<C_Player> m_player = nullptr;
	std::vector<std::shared_ptr<KdTexture>> m_playerenginetexs;

};