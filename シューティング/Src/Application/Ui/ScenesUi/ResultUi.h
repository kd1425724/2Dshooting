#pragma once
#include"Application/Ui/ScenesUi/ScenesUiBase.h"

class C_Result;
class C_Player;

struct Score;

class C_ResultUi :public C_ScenesUiBase
{
public:
	C_ResultUi() {}
	~C_ResultUi()override { Release(); }

	void Init()override;
	void Update()override;
	void Draw()override;

	//背景用
	void BackGroundInit()override;
	void BackGroundUpdate()override;
	void BackGroundDraw()override;

	void SetOwner(std::shared_ptr<C_Result> owner) { m_owner = owner; }

private:
	
	void Release()override;

	//オーナー
	std::weak_ptr<C_Result> m_owner;

	std::shared_ptr<C_Player> m_player;

	//枠
	Math::Vector2 m_framepos;
	Math::Vector2 m_framescale;
	Math::Rectangle m_framerect;

	KdTexture m_frametex;

	//ENTER
	void ENTERInit();
	void ENTERDraw();
	KdTexture m_ENTERTex;

	Math::Vector2 m_ENTERpos = {};
	Math::Vector2 m_ENTERscale = {};
	Math::Rectangle m_ENTERrect = {};

	//スコア用
	void ScoreInit();
	void ScoreDraw();
	
	
	static const int PlayerLifeUpNum = 100000;//１０万
	static const int ClearScoreUpNum = 10000000;//１０００万
	static const int TimeScoreUpNum = 100000;//１０万

	//テキスト
	KdTexture m_CrearTextTex;
	KdTexture m_ScoreTextTex;
	KdTexture m_LifeTextTex;
	KdTexture m_TimeTextTex;
	KdTexture m_TotalTextTex;
	//星
	void StarInit();
	void StarDraw();

	static const int StarControlNum = 1000000;
	static const int StarNum = 3;

	int m_pickstarnum = 0;

	KdTexture m_startex;
	KdTexture m_starframetex;

	Math::Vector2 m_starstartpos;
	Math::Vector2 m_starscale;

	//演出用
	//プレイヤー
	void PlayerInit();
	void PlayerUpdate();
	void PlayerDraw();
	//プレイヤーエンジン
	std::vector<std::shared_ptr<KdTexture>> m_playerenginetexs;
	Math::Vector2 m_playerpos;
};
