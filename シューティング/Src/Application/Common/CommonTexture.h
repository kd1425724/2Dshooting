#pragma once

class C_CommonTexture
{
public:

	//フェード用
	const KdTexture& GetWhiteBackTex()const { return m_whitebacktex; }
	const Math::Rectangle &GetWhiteBackTexRect()const { return m_whitebackrect; }

	//プレイヤー
	const KdTexture& GetPlayerTex()const { return m_playertex; }
	const Math::Rectangle GetPlayerRect()const { return m_playerrect; }
	
	//数字
	const KdTexture& GetNumTex()const { return m_numtex; }
	const Math::Rectangle GetNumRect()const { return m_numrect; }

	//SCORE
	const KdTexture& GetSCORETEXTtex()const { return m_SCORETEXTtex; }

	//SKILL
	const KdTexture& GetSKILLTEXTtex()const { return m_SKILLTEXTtex; }

	//LIFE
	const KdTexture& GetLIFETEXTtex()const { return m_LIFETEXTtex; }

	//START
	const KdTexture& GetSTARTTEXTtex()const { return m_STARTTEXTtex; }

	//GAMEHUD
	const KdTexture& GetGameHUDAreatex()const { return m_GameHUDareatex; }

	//TIME
	const KdTexture& GetTIMETEXTtex()const { return m_TimeTextTex; }

	//コロン：
	const KdTexture& GetColontex()const { return m_colontex; }

	//PAUSEText
	const KdTexture& GetPauseicontex()const { return m_Pauseicontex;}

	//ESC
	const KdTexture& GetESCtex()const { return m_ESCtex; }

	//プレイヤーエンジン
	const std::vector<std::shared_ptr<KdTexture>>& GetPlayerEnginetex()const { return m_playerenginetexs; }

	//敵
	KdTexture& GetEnemy1tex() { return m_enemy1tex; }
	KdTexture& GetEnemy2tex() { return m_enemy2tex; }
	KdTexture& GetEnemy3tex() { return m_enemy3tex; }

	KdTexture& GetEnemy1Enginetex() { return m_enemy1enginetex; }
	KdTexture& GetEnemy2Enginetex() { return m_enemy2enginetex; }
	KdTexture& GetEnemy3Enginetex() { return m_enemy3enginetex; }
	//サブボス＆ボス
	KdTexture& GetSubBosstex(){ return m_subbosstex; }
	KdTexture& GetBosstex(){ return m_bosstex; }
	
	KdTexture& GetSubBossDeathtex(){ return m_subbossdeathtex; }
	KdTexture& GetBossDeathtex() { return m_bossdeathtex; }
	
	KdTexture& GetSubBossMovetex() { return m_subbossmovetex; }
	KdTexture& GetBossMovetex() { return m_bossmovetex; }
	
	KdTexture& GetSubBossEnginetex() { return m_subbossenginetex; }
	KdTexture& GetBossEnginetex() { return m_bossenginetex; }

	//HUD用
	const KdTexture& GetOKIcontex()const { return m_OKicontex; }
	const KdTexture& GetNOIcontex()const { return m_NOicontex; }
	const KdTexture& GetReadytex()const { return m_Readytex; }
	const KdTexture& GetLocktex()const { return m_Locktex; }

	//スキル
	std::shared_ptr<KdTexture> GetLasertex(){ return m_lasertex; }
	std::shared_ptr<KdTexture> GetBarriertex(){ return m_barriertex; }

	//スキルアイコン
	const std::vector<std::shared_ptr<KdTexture>>& GetSkillIcontex()const { return m_skillicontexs; }

private:

	//フェード用
	KdTexture m_whitebacktex;
	Math::Rectangle m_whitebackrect = { 0,0,1280,720 };

	//プレイヤー
	KdTexture m_playertex;
	Math::Rectangle m_playerrect = { 0,0,64,64 };

	//数字
	KdTexture m_numtex;
	Math::Rectangle m_numrect = { 0,0,100,100 };

	//SCORE
	KdTexture m_SCORETEXTtex = {};

	//SKILL
	KdTexture m_SKILLTEXTtex = {};

	//LIFE
	KdTexture m_LIFETEXTtex = {};

	//TIME
	KdTexture m_TimeTextTex = {};

	//コロン:
	KdTexture m_colontex = {};

	KdTexture m_Pauseicontex = {};
	KdTexture m_ESCtex = {};

	//GameHUDArea
	KdTexture m_GameHUDareatex = {};


	//プレイヤーエンジン
	std::vector<std::shared_ptr<KdTexture>> m_playerenginetexs = {};

	//敵
	//１
	KdTexture m_enemy1tex = {};
	KdTexture m_enemy1enginetex = {};
	//２
	KdTexture m_enemy2tex = {};
	KdTexture m_enemy2enginetex = {};
	//３
	KdTexture m_enemy3tex = {};
	KdTexture m_enemy3enginetex = {};

	//サブボス用
	KdTexture m_subbosstex = {};
	KdTexture m_subbossmovetex = {};
	KdTexture m_subbossenginetex = {};
	KdTexture m_subbossdeathtex = {};

	//ボス用
	KdTexture m_bosstex = {};
	KdTexture m_bossmovetex = {};
	KdTexture m_bossenginetex = {};
	KdTexture m_bossdeathtex = {};


	//HUD用
	KdTexture m_OKicontex = {};
	KdTexture m_NOicontex = {};
	KdTexture m_Readytex = {};
	KdTexture m_Locktex = {};

	//レーザー
	std::shared_ptr<KdTexture> m_lasertex = {};

	//バリアー
	std::shared_ptr<KdTexture> m_barriertex = {};

	//スキルアイコン
	std::vector<std::shared_ptr<KdTexture>> m_skillicontexs = {};

	//START
	KdTexture m_STARTTEXTtex;

//シングルトン
private:

	C_CommonTexture();
	~C_CommonTexture();

public:
	
	static C_CommonTexture& GetInstans()
	{
		static C_CommonTexture instans;
		return instans;
	}
};
//共通テクスチャ
#define CommonTex C_CommonTexture::GetInstans()
