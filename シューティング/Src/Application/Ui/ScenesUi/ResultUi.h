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

	//îwåióp
	void BackGroundInit()override;
	void BackGroundUpdate()override;
	void BackGroundDraw()override;

	void SetOwner(std::shared_ptr<C_Result> owner) { m_owner = owner; }

private:
	
	void Release()override;

	//ÉIÅ[ÉiÅ[
	std::weak_ptr<C_Result> m_owner;

	std::shared_ptr<C_Player> m_player;

	//òg
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

	//ÉXÉRÉAóp
	void ScoreInit();
	void ScoreDraw();
	
	
	static const int PlayerLifeUpNum = 1000000;//ÇPÇOÇOñú
	static const int ClearScoreUpNum = 10000000;//ÇPÇOÇOÇOñú
	static const int TimeScoreUpNum = 100000;//ÇPÇOñú

	//ÉeÉLÉXÉg
	KdTexture m_CrearTextTex;
	KdTexture m_ScoreTextTex;
	KdTexture m_LifeTextTex;
	KdTexture m_TimeTextTex;
	KdTexture m_TotalTextTex;
	//êØ
	void StarInit();
	void StarDraw();

	static const int StarControlNum = 15000000;//ÇP5ÇOÇOñú
	static const int StarNum = 3;

	int m_pickstarnum = 0;

	KdTexture m_startex;
	KdTexture m_starframetex;

	Math::Vector2 m_starstartpos;
	Math::Vector2 m_starscale;

	//ââèoóp
	//ÉvÉåÉCÉÑÅ[
	void PlayerInit();
	void PlayerUpdate();
	void PlayerDraw();
	//ÉvÉåÉCÉÑÅ[ÉGÉìÉWÉì
	std::vector<std::shared_ptr<KdTexture>> m_playerenginetexs;
};
