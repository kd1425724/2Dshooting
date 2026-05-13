#pragma once
#include"Application/Ui/ScenesUi/ScenesUiBase.h"

enum class SkillType;
class C_Game;

class C_GameUi : public C_ScenesUiBase
{
public:
	C_GameUi() {}
	~C_GameUi() override { Release(); }

	void Init()		override;
	void Update()	override;
	void Draw()		override;

	//背景用
	void BackGroundInit()	override;
	void BackGroundUpdate()	override;
	void BackGroundDraw()	override;

	//オーナー
	void SetOwner(std::shared_ptr<C_Game> owner)
	{
		m_owner = owner;
	}

	void SetScoreTex(std::shared_ptr<KdTexture> tex)
	{
		m_scoretex = tex;
	}

	//スキル用
	void SetSkillIconTex(std::vector<std::shared_ptr<KdTexture>> tex)
	{
		m_skillicontexs = tex;
	}

	void SetSkill(SkillType type);

	void SetSkillTex(std::shared_ptr<KdTexture> tex)
	{
		m_SKILLtex = tex;
	}

	//LIFE
	void SetLifeTex(std::shared_ptr<KdTexture> tex)
	{
		m_LIFETexttex = tex;
	}

private:

	void Release() override;

	//オーナー
	std::weak_ptr<C_Game> m_owner;

	//背景用
	Math::Matrix m_backgroundtransmat2 = Math::Matrix::Identity;
	Math::Matrix m_backgroundmat2 = Math::Matrix::Identity;

	Math::Vector2 m_backgroundpos2 = { 0,0 };

	//HUD用
	void HUDInit();
	void HUDUpdate();
	void HUDDraw();

	//画像
	KdTexture m_HUDareatex = {};

	//切り取り範囲
	Math::Rectangle m_HUDarearect = { 0,0,0,0 };

	//行列
	Math::Matrix m_HUDareascalemat = Math::Matrix::Identity;
	Math::Matrix m_HUDareatransmat = Math::Matrix::Identity;
	Math::Matrix m_HUDareamat = Math::Matrix::Identity;

	//座標
	Math::Vector2 m_HUDareapos = { 0,0 };

	//サイズ
	Math::Vector2 m_HUDareascale = { 1,1 };

	//カラー
	Math::Color m_HUDareacolor = { 1,1,1,1 };

	////////////

	//スコア
	void ScoreHUDInit();
	void ScoreHUDDraw();

	Math::Vector2 m_scorepos = { 0,0 };
	Math::Vector2 m_scorescale = { 1,1 };

	std::shared_ptr<KdTexture> m_scoretex = nullptr;

	//スキル
	void SkillHUDInit();
	void SkillHUDDraw();

	Math::Vector2 m_skilliconpos = { 0,0 };
	Math::Vector2 m_skilliconscale = { 1,1 };

	std::vector<std::shared_ptr<KdTexture>> m_skillicontexs;

	int m_skilliconindex = 0;

	Math::Vector2 m_skillpos = { 0,0 };
	Math::Vector2 m_skillscale = { 1,1 };

	std::shared_ptr<KdTexture> m_SKILLtex = nullptr;

	KdTexture m_OKicontex = {};
	KdTexture m_NOicontex = {};
	KdTexture m_Readytex = {};
	KdTexture m_Locktex = {};

	//残機HUD
	void LifeHUDInit();
	void LifeDraw();

	Math::Vector2 m_lifestartpos = { 0,0 };

	Math::Vector2 m_lifescale = { 1,1 };

	std::shared_ptr<KdTexture> m_LIFETexttex = nullptr;

	Math::Vector2 m_LIFETextpos = { 0,0 };
	Math::Vector2 m_LIFETextscale = { 1,1 };

	Math::Rectangle m_LIFETextrect = { 0,0,0,0 };

	//タイム
	void TimeInit();
	void TimeDraw();

	KdTexture m_TimeTextTex;

	//コロン:
	KdTexture m_colontex;

	//一時停止
	void PauseIconInit();
	void PauseIconDraw();

	KdTexture m_PauseIcontex;
	KdTexture m_ESCtex;
	
};