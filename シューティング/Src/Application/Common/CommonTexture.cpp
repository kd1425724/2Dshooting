#include "CommonTexture.h"

//ロード用
C_CommonTexture::C_CommonTexture()
{
	//フェード用
	m_whitebacktex.Load("Texture/Ui/WhiteBack.png");
	//プレイヤー
	m_playertex.Load("Texture/Player/Player.png");
	//数字
	m_numtex.Load("Texture/Ui/Font/Num.png");
	//SCORE
	m_SCORETEXTtex.Load("Texture/Ui/Font/SCORE.png");
	//SKILL
	m_SKILLTEXTtex.Load("Texture/Ui/Font/SKILL.png");
	//LIFE
	m_LIFETEXTtex.Load("Texture/Ui/Font/LIFE.png");
	//START
	m_STARTTEXTtex.Load("Texture/Ui/Font/START.png");
	//HUDエリア
	m_GameHUDareatex.Load("Texture/Ui/HUD/GameHUDArea.png");
	//TIME
	m_TimeTextTex.Load("Texture/Ui/Font/TIME.png");
	//コロン：
	m_colontex.Load("Texture/Ui/Font/colon.png");
	//ESC
	m_ESCtex.Load("Texture/Ui/HUD/ESC.png");
	//Pause
	m_Pauseicontex.Load("Texture/Ui/HUD/PauseIcon.png");

	m_stage1tex.Load("Texture/Ui/StageSelect/Stage1.png");
	m_stage2tex.Load("Texture/Ui/StageSelect/Stage2.png");
	m_stage1frametex.Load("Texture/Ui/StageSelect/Stage1Frame.png");
	m_stage2frametex.Load("Texture/Ui/StageSelect/Stage2Frame.png");
	m_backbuttontex.Load("Texture/Ui/HUD/PAUSE/BACKNO.png");
	m_backbuttonframetex.Load("Texture/Ui/HUD/PAUSE/BACKOK.png");
	
	m_StageSelectHUDtex.Load("Texture/Ui/StageSelect/StageSelectHUD.png");

	//プレイヤーエンジン
	std::shared_ptr<KdTexture> playerenginetex = std::make_shared<KdTexture>();
	playerenginetex->Load("Texture/Player/PlayerEngine_01.png");
	m_playerenginetexs.push_back(playerenginetex);
	playerenginetex = std::make_shared<KdTexture>();
	playerenginetex->Load("Texture/Player/PlayerEngine_02.png");
	m_playerenginetexs.push_back(playerenginetex);
	playerenginetex = std::make_shared<KdTexture>();
	playerenginetex->Load("Texture/Player/PlayerEngine_03.png");
	m_playerenginetexs.push_back(playerenginetex);

	//敵１
	m_enemy1tex.Load("Texture/Enemy/Enemy1/Enemy1Base.png");
	m_enemy1enginetex.Load("Texture/Enemy/Enemy1/Enemy1Engine.png");
	//敵２
	m_enemy2tex.Load("Texture/Enemy/Enemy2/Enemy2Base.png");
	m_enemy2enginetex.Load("Texture/Enemy/Enemy2/Enemy2Engine.png");
	//敵３
	m_enemy3tex.Load("Texture/Enemy/Enemy3/Enemy3Base.png");
	m_enemy3enginetex.Load("Texture/Enemy/Enemy3/Enemy3Engine.png");

	m_subbosstex.Load("Texture/Enemy/SubBoss/SubBossBase.png");
	m_subbossmovetex.Load("Texture/Enemy/SubBoss/SubBossMove.png");
	m_subbossenginetex.Load("Texture/Enemy/SubBoss/SubBossEngine.png");
	m_subbossdeathtex.Load("Texture/Enemy/SubBoss/SubBossDeath.png");

	m_bosstex.Load("Texture/Enemy/Boss/BossBase.png");
	m_bossmovetex.Load("Texture/Enemy/Boss/BossMove.png");
	m_bossenginetex.Load("Texture/Enemy/Boss/BossEngine.png");
	m_bossdeathtex.Load("Texture/Enemy/Boss/BossDeath.png");

	//HUD
	m_OKicontex.Load("Texture/Ui/HUD/OKIcon.png");
	m_NOicontex.Load("Texture/Ui/HUD/NOIcon.png");
	m_Readytex.Load("Texture/Ui/HUD/READY.png");
	m_Locktex.Load("Texture/Ui/HUD/LOCK.png");

	//レーザー
	m_lasertex = std::make_shared<KdTexture>();
	m_lasertex->Load("Texture/Skill/Attack/Laser.png");
	//バリア
	m_barriertex = std::make_shared<KdTexture>();
	m_barriertex->Load("Texture/Skill/Barrier/Barrier.png");

	m_skillicontexs.push_back(std::make_shared<KdTexture>());
	m_skillicontexs.back()->Load("Texture/Ui/HUD/Copy.png");
	m_skillicontexs.push_back(std::make_shared<KdTexture>());
	m_skillicontexs.back()->Load("Texture/Ui/HUD/EnemyGenerate.png");
	m_skillicontexs.push_back(std::make_shared<KdTexture>());
	m_skillicontexs.back()->Load("Texture/Ui/HUD/Barrier.png");
	m_skillicontexs.push_back(std::make_shared<KdTexture>());
	m_skillicontexs.back()->Load("Texture/Ui/HUD/Laser.png");

	//ステージセレクト
	//スコアアタック
	m_ScoreAttackTextTex.Load("Texture/Ui/StageSelect/ScoreAttackText.png");
	//タイムアタック
	m_TimeAttackTextTex.Load("Texture/Ui/StageSelect/TimeAttackText.png");
	//「以内にクリア」
	m_ClearWithinTextTex.Load("Texture/Ui/StageSelect/ClearWithinText.png");
	//「以上達成」
	m_AchieveAboveTextTex.Load("Texture/Ui/StageSelect/AchieveAboveText.png");

	//星獲得条件フレーム用
	std::shared_ptr<KdTexture> starframetex1=std::make_shared<KdTexture>();
	starframetex1->Load("Texture/Ui/StageSelect/StarGetConditionFrame1.png");
	m_StarGetConditionFrameTex.push_back(starframetex1);
	std::shared_ptr<KdTexture> starframetex2 = std::make_shared<KdTexture>();
	starframetex2->Load("Texture/Ui/StageSelect/StarGetConditionFrame2.png");
	m_StarGetConditionFrameTex.push_back(starframetex2);
	std::shared_ptr<KdTexture> starframetex3 = std::make_shared<KdTexture>();
	starframetex3->Load("Texture/Ui/StageSelect/StarGetConditionFrame3.png");
	m_StarGetConditionFrameTex.push_back(starframetex3);

	//タイムアタック条件
	std::shared_ptr<KdTexture> timeattacktex1 = std::make_shared<KdTexture>();
	timeattacktex1->Load("Texture/Ui/StageSelect/TimeAttackCondition1.png");
	m_TimeAttackConditionTex.push_back(timeattacktex1);
	std::shared_ptr<KdTexture> timeattacktex2 = std::make_shared<KdTexture>();
	timeattacktex2->Load("Texture/Ui/StageSelect/TimeAttackCondition2.png");
	m_TimeAttackConditionTex.push_back(timeattacktex2);
	std::shared_ptr<KdTexture> timeattacktex3 = std::make_shared<KdTexture>();
	timeattacktex3->Load("Texture/Ui/StageSelect/TimeAttackCondition3.png");
	m_TimeAttackConditionTex.push_back(timeattacktex3);

	//スコアアタック条件
	std::shared_ptr<KdTexture> scoreattacktex1 = std::make_shared<KdTexture>();
	scoreattacktex1->Load("Texture/Ui/StageSelect/ScoreAttackCondition1.png");
	m_ScoreAttackConditionTex.push_back(scoreattacktex1);
	std::shared_ptr<KdTexture> scoreattacktex2 = std::make_shared<KdTexture>();
	scoreattacktex2->Load("Texture/Ui/StageSelect/ScoreAttackCondition2.png");
	m_ScoreAttackConditionTex.push_back(scoreattacktex2);
	std::shared_ptr<KdTexture> scoreattacktex3 = std::make_shared<KdTexture>();
	scoreattacktex3->Load("Texture/Ui/StageSelect/ScoreAttackCondition3.png");
	m_ScoreAttackConditionTex.push_back(scoreattacktex3);

	//星フレーム
	m_starframetex.Load("Texture/Ui/StageSelect/StarFrame.png");
	//星
	m_startex.Load("Texture/Ui/StageSelect/Star.png");

	//「スキャン中」テキスト
	m_ScaningTextTex = std::make_shared<KdTexture>();
	m_ScaningTextTex->Load("Texture/Ui/Font/ScaningText.png");
	//「スキャン完了」テキスト
	m_ScanCompleteTextTex = std::make_shared<KdTexture>();
	m_ScanCompleteTextTex->Load("Texture/Ui/Font/ScanCompleteText.png");
	//「スキャン失敗」テキスト
	m_ScanMissTextTex = std::make_shared<KdTexture>();
	m_ScanMissTextTex->Load("Texture/Ui/Font/ScanMissText.png");

	//「星獲得条件」テキスト
	m_StarRequirementsTextTex = std::make_shared<KdTexture>();
	m_StarRequirementsTextTex->Load("Texture/Ui/Font/StarRequirementsText.png");

	//「コピー！」テキスト
	m_CopyTextTex = std::make_shared<KdTexture>();
	m_CopyTextTex->Load("Texture/Ui/Font/CopyText.png");

	//OKフレーム
	m_OKFrameTex.Load("Texture/Ui/HUD/OKFrame.png");
	//NOフレーム
	m_NOFrameTex.Load("Texture/Ui/HUD/NOFrame.png");
}
//解放用
C_CommonTexture::~C_CommonTexture()
{
	//フェード用
	m_whitebacktex.Release();
	//プレイヤー
	m_playertex.Release();
	//数字
	m_numtex.Release();
	//SCORE
	m_SCORETEXTtex.Release();
	//SKILL
	m_SKILLTEXTtex.Release();
	m_GameHUDareatex.Release();
	m_colontex.Release();
	m_TimeTextTex.Release();
	m_Pauseicontex.Release();
	m_ESCtex.Release();
	//プレイヤーエンジン
	m_playerenginetexs.clear();
	//敵
	m_enemy1tex.Release();
	m_enemy1enginetex.Release();
	m_enemy2tex.Release();
	m_enemy2enginetex.Release();
	m_enemy3tex.Release();
	m_enemy3enginetex.Release();
	//サブボス
	m_subbosstex.Release();
	m_subbossmovetex.Release();
	m_subbossenginetex.Release();
	m_subbossdeathtex.Release();
	//ボス
	m_bosstex.Release();
	m_bossmovetex.Release();
	m_bossenginetex.Release();
	m_bossdeathtex.Release();

	m_OKicontex.Release();
	m_NOicontex.Release();
	m_Readytex.Release();
	m_Locktex.Release();

	m_skillicontexs.clear();

	m_STARTTEXTtex.Release();

	m_lasertex.reset();
	m_barriertex.reset();

	m_stage1tex.Release();
	m_stage2tex.Release();
	m_stage1frametex.Release();
	m_stage2frametex.Release();	
	m_backbuttontex.Release();	
	m_backbuttonframetex.Release();

	m_StageSelectHUDtex.Release();
	m_ScoreAttackTextTex.Release();
	m_TimeAttackTextTex.Release();
	m_ClearWithinTextTex.Release();
	m_AchieveAboveTextTex.Release();

	m_starframetex.Release();
	m_startex.Release();

	m_ScaningTextTex.reset();
	m_ScanCompleteTextTex.reset();
	m_ScanMissTextTex.reset();

	m_StarRequirementsTextTex.reset();

	m_CopyTextTex.reset();

	m_OKFrameTex.Release();
	m_NOFrameTex.Release();
}

