#pragma once
#include"Application/Ui/ScenesUi/ScenesUiBase.h"

enum class SkillType;
class C_Game;

class C_GameUi :public C_ScenesUiBase
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
	void SetOwner(std::shared_ptr<C_Game> owner) { m_owner = owner; }

	void SetScoreTex(std::shared_ptr<KdTexture> tex) { m_scoretex = tex; }

	//スキル用
	void SetSkillIconTex(std::vector<std::shared_ptr<KdTexture>> tex) { m_skillicontexs = tex; }

	void SetSkill(SkillType type);

	void SetSkillTex(std::shared_ptr<KdTexture> tex) { m_SKILLtex = tex; }

	//LIFE
	void SetLifeTex(std::shared_ptr<KdTexture> tex) { m_LIFETexttex = tex; }
	
	//Hpバー
	void SetHpBarTex(std::shared_ptr<KdTexture> tex) { m_hpbartex = tex; }
	//Hpバー枠
	void SetHpBarFrameTex(std::shared_ptr<KdTexture> tex) { m_hpbarframetex = tex; }

private:

	void Release()override;

	//オーナー
	std::weak_ptr<C_Game> m_owner;

	//背景用
	Math::Matrix m_backgroundtransmat2;
	Math::Matrix m_backgroundmat2;
	Math::Vector2 m_backgroundpos2;

	//HUD用///
	 //HUD
	void HUDInit();
	void HUDUpdate();
	void HUDDraw();

	//画像
	KdTexture m_HUDareatex;
	//切り取り範囲
	Math::Rectangle m_HUDarearect;
	//行列
	Math::Matrix m_HUDareascalemat;
	Math::Matrix m_HUDareatransmat;
	Math::Matrix m_HUDareamat;
	//座標
	Math::Vector2 m_HUDareapos;
	//サイズ
	Math::Vector2 m_HUDareascale;
	//カラー
	Math::Color m_HUDareacolor;
	////////////

	//スコア
	void ScoreHUDInit();
	void ScoreHUDUpdate();
	void ScoreHUDDraw();

	Math::Vector2 m_scorepos;
	Math::Vector2 m_scorescale;

	std::shared_ptr<KdTexture> m_scoretex;

	//スキル
	void C_GameUi::SkillHUDInit();
	void C_GameUi::SkillHUDUpdate();
	void C_GameUi::SkillHUDDraw();

	Math::Vector2 m_skilliconpos;
	Math::Vector2 m_skilliconscale;
	std::vector<std::shared_ptr<KdTexture>> m_skillicontexs;
	int m_skilliconindex = 0;
	Math::Vector2 m_skillpos;
	Math::Vector2 m_skillscale;
	std::shared_ptr<KdTexture> m_SKILLtex;

	KdTexture m_OKicontex;
	KdTexture m_NOicontex;

	//残機HUD
	void LifeHUDInit();
	void LifeDraw();

	Math::Vector2 m_lifestartpos;

	Math::Vector2 m_lifescale;

	std::shared_ptr<KdTexture> m_LIFETexttex;

	Math::Vector2 m_LIFETextpos;
	Math::Vector2 m_LIFETextscale;

	Math::Rectangle m_LIFETextrect;

	//Hpバー
	void HPBarInit();
	void HPBarUpdate();
	void HPBarDraw();

	KdTexture m_BOSSTexttex;

	Math::Rectangle m_hpbarrect;
	Math::Rectangle m_hpbarframerect;
	std::shared_ptr<KdTexture> m_hpbartex;
	std::shared_ptr<KdTexture> m_hpbarframetex;

	float m_bossHpRate = 1.0f;
	bool  m_isBossExist = false;

	std::vector<float> m_subBossHpRates;

	//ボス
	Math::Vector2 m_bosshpbarstartpos;
	Math::Vector2 m_bosshpbarpos;
	Math::Vector2 m_bosshpbarscale;

	//サブボス用
	Math::Vector2 m_subbosshpbarstartpos;
	Math::Vector2 m_subbosshpbarscale;
};
