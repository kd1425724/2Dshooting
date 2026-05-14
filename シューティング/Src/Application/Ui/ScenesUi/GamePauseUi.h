#pragma once
#include"Application/Ui/ScenesUi/ScenesUiBase.h"

class C_GamePause;

enum class GamePauseButton
{
	EXIT,
	BACK
};

class C_GamePauseUi :public C_ScenesUiBase
{
public:
	C_GamePauseUi() {}
	~C_GamePauseUi()override { Release(); }

	void Init()override;
	void Update()override;
	void Draw()override;

	//背景用
	void BackGroundInit()override;
	void BackGroundUpdate()override;
	void BackGroundDraw()override;

	void SetOwner(std::shared_ptr<C_GamePause> owner) { m_owner = owner; }

private:

	GamePauseButton m_button = GamePauseButton::BACK;

	void Release()override;

	//オーナー
	std::weak_ptr<C_GamePause> m_owner;

	//背景
	float m_backgroundalpha = 1.0f;

	//ポーズ
	void PAUSEDraw();

	//テクスチャ
	// PAUSE
	KdTexture m_PAUSEtex;
	//タイトルへ用
	KdTexture m_EXITNOtex;
	KdTexture m_EXITOKtex;
	//ゲームに戻る
	KdTexture m_BACKNOtex;
	KdTexture m_BACKOKtex;

	//操作説明
	void KeyInit();
	void KeyDraw();
	KdTexture m_ArrowKeyTex;
	KdTexture m_SpaceKeyTex;
	KdTexture m_EKeyTex;
	KdTexture m_EscKeyTex;
	KdTexture m_ShotTextTex;
	KdTexture m_MoveTextTex;
	
};
