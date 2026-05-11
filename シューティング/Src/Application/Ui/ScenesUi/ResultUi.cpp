#include "ResultUi.h"
#include"Application/Common/CommonTexture.h"
#include"../../Scenes/Result/Result.h"
#include"../../Common/CommonAPI.h"
#include"../../Info.h"
#include"../../Player/Player.h"
#include"../../Scenes/SceneManager.h"

void C_ResultUi::Init()
{
	//背景初期化
	BackGroundInit();

	ScoreInit();

	StarInit();

	PlayerInit();

	ENTERInit();
}

void C_ResultUi::Update()
{
	//背景更新
	BackGroundUpdate();

	PlayerUpdate();
}

void C_ResultUi::Draw()
{
	//背景描画
	BackGroundDraw();

	StarDraw();

	ScoreDraw();

	ENTERDraw();
}

//背景
void C_ResultUi::BackGroundInit()
{
	//黒背景
	BlackBackInit();

	//背景
	m_backgroundtex.Load("Texture/Ui/BackGround/Result/ResultBackGround.png");

	//座標
	m_backgroundpos = { 0,0 };
	//サイズ
	m_backgroundscale = { 1.0f,1.0f };
	//アニメーション用
	m_backgroundanim = { 0,0 };
	//切り取り範囲
	m_backgroundrect = { 0,0,1280,720 };
	//アニメーション用
	m_backgroundanim = { 0,0 };
	//カラー
	m_backgroundcolor = { 1,1,1,1 };

	//枠
	m_frametex.Load("Texture/Ui/Result/ResuLtHUD.png");

	m_framepos = { 0,0 };
	m_framescale = { 4,3 };
	m_framerect = { 0,0,211,211 };
}
void C_ResultUi::BackGroundUpdate()
{
	//黒背景
	BlackBackUpdate();

	m_backgroundscalemat = Math::Matrix::CreateScale(m_backgroundscale.x, m_backgroundscale.y, 1);
	m_backgroundtransmat = Math::Matrix::CreateTranslation(m_backgroundpos.x, m_backgroundpos.y, 0);
	m_backgroundmat = m_backgroundscalemat * m_backgroundtransmat;
}
void C_ResultUi::BackGroundDraw()
{
	//黒背景
	BlackBackDraw();

	//背景
	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_backgroundmat);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_backgroundtex, 0, 0, &Math::Rectangle((int)m_backgroundanim.x * m_backgroundrect.width, m_backgroundrect.y, m_backgroundrect.width, m_backgroundrect.height), &m_backgroundcolor);

	PlayerDraw();

	//枠
	{
		Math::Matrix s = Math::Matrix::CreateScale(m_framescale.x, m_framescale.y, 1);
		Math::Matrix t = Math::Matrix::CreateTranslation(m_framepos.x, m_framepos.y, 0);
		Math::Matrix mat = s * t;

		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_frametex, m_framerect, 0.7f);
	}
}

void C_ResultUi::Release()
{
	m_backgroundtex.Release();
	m_frametex.Release();
	m_ENTERTex.Release();
	m_CrearTextTex.Release();
	m_ScoreTextTex.Release();
	m_LifeTextTex.Release();
	m_TimeTextTex.Release();
	m_TotalTextTex.Release();
	m_starframetex.Release();
	m_startex.Release();
}

void C_ResultUi::ENTERInit()
{
	m_ENTERTex.Load("Texture/Ui/HUD/Result/ENTER.png");

	m_ENTERpos = { 500,-300 };
	m_ENTERrect = { 0,0,480,100 };
	m_ENTERscale = { 0.5f,0.5f };
}

void C_ResultUi::ENTERDraw()
{
	Math::Matrix s = Math::Matrix::CreateScale(m_ENTERscale.x, m_ENTERscale.y, 1);
	Math::Matrix t = Math::Matrix::CreateTranslation(m_ENTERpos.x, m_ENTERpos.y, 0);
	Math::Matrix mat = s * t;

	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_ENTERTex, m_ENTERrect, 1.0f);
}

void C_ResultUi::ScoreInit()
{
	m_PlayTimeTextTex.Load("Texture/Ui/Font/PLAYTIME.png");
	m_CrearTextTex.Load("Texture/Ui/Font/CLEAR.png");
	m_ScoreTextTex.Load("Texture/Ui/Font/SCORE.png");
	m_LifeTextTex.Load("Texture/Ui/Font/LIFE.png");
	m_TimeTextTex.Load("Texture/Ui/Font/TIME.png");
	m_TotalTextTex.Load("Texture/Ui/Font/TOTAL.png");
	m_colontex.Load("Texture/Ui/Font/colon.png");
	m_BonusTextTex.Load("Texture/Ui/Font/BONUS.png");

	//スコア代入
	auto s = SCENEMANAGER.GetScoreData();

	if (!s)
	{
		return;
	}
	//スコア計算
	int score = s->score;
	int clear = 0;
	int time = 0;
	if (s->clear)
	{
		clear = ClearScoreUpNum;
		time = std::max(0, 180 - s->time) * TimeScoreUpNum;
	}
	int lifescore = s->playerlife * PlayerLifeUpNum;

	int total = score + clear + lifescore + time;

	//星の数制御用
	//５０万ずつ引く
	//５０万以下になるかm_pickupstarnumが３になるまでループ
	while (total >= StarControlNum && m_pickstarnum < StarNum)
	{
		m_pickstarnum++;

		total -= StarControlNum;
	}

}


void C_ResultUi::ScoreDraw()
{

	Math::Rectangle rect = { 0,0,480,100 };

	//テキスト
	{
		Math::Vector2 scale = { 0.3f,0.35f };
		Math::Matrix s = Math::Matrix::CreateScale(scale.x, scale.y, 1);

		//PLAYTIME
		{
			Math::Vector2 pos = { -200,120 };

			Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);

			Math::Matrix mat = s * t;

			Math::Rectangle playtimerect = { 0,0,1000,100 };

			KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
			KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_PlayTimeTextTex, playtimerect, 1.0f);
		}

		//クリア
		{
			Math::Vector2 pos = { -200,60 };

			Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);

			Math::Matrix mat = s * t;

			KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
			KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_CrearTextTex, rect, 1.0f);
		}

		//スコア
		{
			Math::Vector2 pos = { -200,0 };

			Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);

			Math::Matrix mat = s * t;

			KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
			KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_ScoreTextTex, rect, 1.0f);
		}

		//ライフ
		{
			Math::Vector2 pos = { -270,-60 };

			Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);

			Math::Matrix mat = s * t;

			KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
			KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_LifeTextTex, rect, 1.0f);
		}
		//BONUS
		{
			Math::Vector2 pos = { -150,-60 };

			Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);

			Math::Matrix mat = s * t;

			KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
			KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_BonusTextTex, rect, 1.0f);
		}

		//タイム
		{
			Math::Vector2 pos = { -270,-120 };

			Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);

			Math::Matrix mat = s * t;

			KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
			KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_TimeTextTex, rect, 1.0f);
		}
		//BONUS
		{
			Math::Vector2 pos = { -150,-120 };

			Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);

			Math::Matrix mat = s * t;

			KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
			KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_BonusTextTex, rect, 1.0f);
		}
	}

	//トータル
	{
		Math::Vector2 scale = { 0.5f,0.5f };
		Math::Matrix s = Math::Matrix::CreateScale(scale.x, scale.y, 1);

		Math::Vector2 pos = { -200,-200 };
		Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);

		Math::Matrix mat = s * t;

		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
		Math::Color color = { 1.0f,1.0f,0,1.0f };
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_TotalTextTex, 0, 0, &rect, &color);
	}

	//数字描画
	{
		//スコア代入
		auto s = SCENEMANAGER.GetScoreData();

		if (!s)
		{
			return;
		}
		//スコア計算
		int score = s->score;
		int clear = 0;
		int time = 0;
		if (s->clear)
		{
			clear = ClearScoreUpNum;
			time = std::max(0, 180 - s->time) * TimeScoreUpNum;
		}
		int lifescore = s->playerlife * PlayerLifeUpNum;

		int total = score + clear + lifescore + time;

		//描画
		Math::Vector2 numscale = { 0.3f,0.35f };
		COMMONAPI.NumDraw(clear, { 200,60 }, numscale);
		COMMONAPI.NumDraw(score, { 200,0 }, numscale);
		COMMONAPI.NumDraw(lifescore, { 200,-60 }, numscale);
		COMMONAPI.NumDraw(time, { 200,-120 }, numscale);
		COMMONAPI.NumDraw(total, { 250,-200 }, { 0.35f,0.60f }, { 1.0f,1.0f,0.0f,1.0f });
	}

	{
		//スコア代入
		auto s = SCENEMANAGER.GetScoreData();

		if (!s)
		{
			return;
		}

		int time = s->time;

		int minute = static_cast<int>(time / 60.0f);
		int second = static_cast<int>(time) % 60;
		int millisecond = static_cast<int>(time * 100.0f) % 100;


		Math::Vector2 scale = { 0.3f,0.35f };
		Math::Color color = { 1,1,1,1 };

		Math::Vector2 pos1 = { 20,120 };
		COMMONAPI.NumDraw(minute, pos1, scale, color, true, 2);

		Math::Vector2 pos2 = { 110,120 };
		COMMONAPI.NumDraw(second, pos2, scale, color, true, 2);

		Math::Vector2 pos3 = { 200,120 };
		COMMONAPI.NumDraw(millisecond, pos3, scale, color, true, 2);
	}

	//コロン：
	{
		Math::Rectangle colonrect = { 0,0,100,100 };

		Math::Vector2 scale = { 0.3f,0.35f };

		Math::Matrix s = Math::Matrix::CreateScale(scale.x, scale.y, 1);;

		for (int i = 0; i < 2; i++)
		{
			Math::Vector2 pos = { 50.0f + (i * 90),120 };

			Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
			Math::Matrix mat = s * t;

			KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
			KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_colontex, colonrect, 1.0f);
		}
	}
}

void C_ResultUi::StarInit()
{
	m_startex.Load("Texture/Ui/Result/Star.png");
	m_starframetex.Load("Texture/Ui/Result/StarFrame.png");

	m_starstartpos = { -150,200 };
	m_starscale = { 0.4,0.4 };
}
void C_ResultUi::StarDraw()
{

	Math::Rectangle rect = { 0,0,292,280 };


	for (int i = 0; i < StarNum; i++)
	{
		Math::Vector2 pos;

		pos.x = m_starstartpos.x + (i * 150);
		pos.y = m_starstartpos.y + ((int)(i % 2) * 30);

		Math::Matrix s = Math::Matrix::CreateScale(m_starscale.x, m_starscale.y, 1);
		Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
		Math::Matrix mat = s * t;

		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_starframetex, rect, 1.0f);
	}

	for (int i = 0; i < m_pickstarnum; i++)
	{
		Math::Vector2 pos;

		pos.x = m_starstartpos.x + (i * 150);
		pos.y = m_starstartpos.y + ((int)(i % 2) * 30);

		Math::Matrix s = Math::Matrix::CreateScale(m_starscale.x, m_starscale.y, 1);
		Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
		Math::Matrix mat = s * t;
		
		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_startex, rect, 1.0f);
	}
}

void C_ResultUi::PlayerInit()
{
	m_player = std::make_shared<C_Player>();
	
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

	m_player->SetEngineTex(m_playerenginetexs);

	m_player->ResultInit();
}

void C_ResultUi::PlayerUpdate()
{
	m_player->ResultUpdate();

}

void C_ResultUi::PlayerDraw()
{
	m_player->ResultDraw();
}
