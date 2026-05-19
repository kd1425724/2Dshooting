#include"StageSelectUi.h"
#include"../../Common/CommonTexture.h"
#include"../../Scenes/SceneManager.h"
#include"../../Player/Player.h"
#include"../../Input/Input.h"
#include"../../Info.h"
void C_StageSelectUi::Release()
{
	m_backgroundtex.Release();
	m_movebackgroundtex.Release();

}

void C_StageSelectUi::Init()
{
	//背景初期化
	BackGroundInit();

	//stage1
	CreateSpriteItemInit(
		{ -200,100 },
		{ 0,0,210,210 },
		{ 0.3f,0.3f },
		&CommonTex.GetStage1tex(),
		{ 1,1,1,1 },
		&CommonTex.GetStage1FrameTex()
	);
	//stage1のアクション
	SetAction((int)StageSelectButton::Stage1, []()
		{
			//ステージ1に遷移
			SCENEMANAGER.push(SceneType::Game, true);
		}
	);

	float scale = 210.0f * 0.3f / 1254.0f;
	//stage2
	CreateSpriteItemInit(
		{ -200,-100 },
		{ 0,0,1254,1254 },
		{ scale,scale },
		&CommonTex.GetStage2tex(),
		{ 1,1,1,1 },
		&CommonTex.GetStage2FrameTex()
	);
	SetAction((int)StageSelectButton::Stage2, []()
		{
			//ステージ2に遷移
			SCENEMANAGER.push(SceneType::Game2, true);
		}
	);

	//BACK
	CreateSpriteItemInit(
		{ -400,-300 },
		{ 0,0,700,210 },
		{ 0.3f,0.3f },
		&CommonTex.GetBackButtonTex(),
		{ 1,1,1,1 },
		&CommonTex.GetBackButtonFrameTex()
	);
	SetAction((int)StageSelectButton::BACK, []()
		{
			//タイトルに遷移
			SCENEMANAGER.NoFeedpush(SceneType::Title, true);
		}
	);


	PlayerInit();

}

void C_StageSelectUi::Update()
{
	//背景更新
	BackGroundUpdate();

	PlayerUpdate();

	CreateSpriteItemUpdate();

	if (Input.GetUserKey(UserKeyType::Top) && !Input.GetUserKeyFlg(UserKeyType::Top))
	{
		if (m_button == StageSelectButton::Stage1)
		{
			m_button = static_cast<StageSelectButton>(static_cast<int>(m_button) -2);
		}
		else
		{
			m_button = static_cast<StageSelectButton>(static_cast<int>(m_button) + 1);
		}
	}
	if (Input.GetUserKey(UserKeyType::Bottom) && !Input.GetUserKeyFlg(UserKeyType::Bottom))
	{
		if (m_button == StageSelectButton::BACK)
		{
			m_button = static_cast<StageSelectButton>(static_cast<int>(m_button) + 2);
		}
		else
		{
			m_button = static_cast<StageSelectButton>(static_cast<int>(m_button) - 1);
		}
	}

	if (Input.GetUserKey(UserKeyType::ZKey) && !Input.GetUserKeyFlg(UserKeyType::ZKey))
	{
		ButtonUpdate((int)m_button);
	}
}

void C_StageSelectUi::Draw()
{
	//背景描画
	BackGroundDraw();

	PlayerDraw();

	CreateSpriteItemDraw();

	ButtonDraw((int)m_button);

	StageInfoDraw();
}

void C_StageSelectUi::StageInfoDraw()
{
	//フレーム用
	{
		Math::Vector2 pos = { 200,0 };
		Math::Vector2 scale = { 3.5f,3 };

		Math::Matrix s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
		Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
		Math::Matrix mat = s * t;

		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
		Math::Rectangle rect = { 0,0,210,210 };
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(&CommonTex.GetStageSelectHUDTex(), 0, 0, &rect, &Math::Color(1, 1, 1, 0.7f));
	}

	switch (m_button)
	{
	case StageSelectButton::Stage1:
		//ステージ1
		{
			//スコアアタック
			{
				Math::Vector2 pos = { 200,200 };
				Math::Vector2 scale = { 0.2f,0.2f };
				Math::Matrix s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
				Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
				Math::Matrix mat = s * t;

				KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
				Math::Rectangle rect = { 0,0,1534,1080 };
				KdShaderManager::GetInstance().m_spriteShader.DrawTex(&CommonTex.GetScoreAttackTextTex(), 0, 0, &rect, &Math::Color(1, 1, 1, 1));
			}

			//星獲得条件フレーム用
			{
				float startposY = -40.0f;

				for (int i = 0; i < 3; i++)
				{
					//条件フレーム
					Math::Vector2 pos = { 200,startposY - i * 80.0f };
					Math::Vector2 scale = { 0.8f,0.35f };
					Math::Matrix s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
					Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
					Math::Matrix mat = s * t;

					KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
					Math::Rectangle rect = { 0,0,700,210 };
					KdShaderManager::GetInstance().m_spriteShader.DrawTex(CommonTex.GetStarGetConditionFrameTex(i).get(), 0, 0, &rect, &Math::Color(1, 1, 1, 1));

					//以上達成
					pos = { 300,startposY - i * 80.0f };
					s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
					t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
					mat = s * t;

					KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
					rect = { 0,0,210,210 };
					KdShaderManager::GetInstance().m_spriteShader.DrawTex(&CommonTex.GetAchieveAboveTextTex(), 0, 0, &rect, &Math::Color(1, 1, 1, 1));

					//条件
					pos = { 200,startposY - i * 80.0f };
					scale = { 0.3f,0.3f };
					s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
					t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
					mat = s * t;

					KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
					rect = { 0,0,1000,100 };
					KdShaderManager::GetInstance().m_spriteShader.DrawTex(CommonTex.GetScoreAttackConditionTex(i).get(), 0, 0, &rect, &Math::Color(1, 1, 1, 1));
				}

				//星フレーム
				{
					for (int i = 0; i < 3; i++)
					{
						Math::Vector2 pos = { 0,startposY - i * 80.0f };
						Math::Vector2 scale = { 0.23f,0.23f };
						Math::Matrix s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
						Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
						Math::Matrix mat = s * t;
						KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
						Math::Rectangle rect = { 0,0,292,280 };
						KdShaderManager::GetInstance().m_spriteShader.DrawTex(&CommonTex.GetStarFrameTex(), 0, 0, &rect, &Math::Color(1, 1, 1, 1));
					}
				}

				//星
				{
					for (int i = 0; i < INFO.ScoreAttackUserStarInfo; i++)
					{
						Math::Vector2 pos = { 0,startposY - i * 80.0f };
						Math::Vector2 scale = { 0.23f,0.23f };
						Math::Matrix s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
						Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
						Math::Matrix mat = s * t;
						KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
						Math::Rectangle rect = { 0,0,292,280 };
						KdShaderManager::GetInstance().m_spriteShader.DrawTex(&CommonTex.GetStarTex(), 0, 0, &rect, &Math::Color(1, 1, 1, 1));
					}
				}
			}
		}
		break;
	case StageSelectButton::Stage2:
		//ステージ2
		{
			//タイムアタック
			{
				Math::Vector2 pos = { 200,200 };
				Math::Vector2 scale = { 0.2f,0.2f };
				Math::Matrix s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
				Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
				Math::Matrix mat = s * t;
				KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
				Math::Rectangle rect = { 0,0,1534,1080 };
				KdShaderManager::GetInstance().m_spriteShader.DrawTex(&CommonTex.GetTimeAttackTextTex(), 0, 0, &rect, &Math::Color(1, 1, 1, 1));
			}

			//星獲得条件フレーム用
			{
				float startposY = -40.0f;

				for (int i = 0; i < 3; i++)
				{
					//条件フレーム
					Math::Vector2 pos = { 200,startposY - i * 80.0f };
					Math::Vector2 scale = { 0.8f,0.35f };
					Math::Matrix s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
					Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
					Math::Matrix mat = s * t;
					KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
					Math::Rectangle rect = { 0,0,700,210 };
					KdShaderManager::GetInstance().m_spriteShader.DrawTex(CommonTex.GetStarGetConditionFrameTex(i).get(), 0, 0, &rect, &Math::Color(1, 1, 1, 1));

					//以上達成
					pos = { 300,startposY - i * 80.0f };
					s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
					t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
					mat = s * t;
					KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
					rect = { 0,0,210,210 };
					KdShaderManager::GetInstance().m_spriteShader.DrawTex(&CommonTex.GetAchieveAboveTextTex(), 0, 0, &rect, &Math::Color(1, 1, 1, 1));

					//条件
					pos = { 200,startposY - i * 80.0f };
					scale = { 0.3f,0.3f };
					s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
					t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
					mat = s * t;
					KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
					rect = { 0,0,1000,100 };
					KdShaderManager::GetInstance().m_spriteShader.DrawTex(CommonTex.GetScoreAttackConditionTex(i).get(), 0, 0, &rect, &Math::Color(1, 1, 1, 1));
				}


				//星フレーム
				{
					for (int i = 0; i < 3; i++)
					{
						Math::Vector2 pos = { 0,startposY - i * 80.0f };
						Math::Vector2 scale = { 0.23f,0.23f };
						Math::Matrix s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
						Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
						Math::Matrix mat = s * t;
						KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
						Math::Rectangle rect = { 0,0,292,280 };
						KdShaderManager::GetInstance().m_spriteShader.DrawTex(&CommonTex.GetStarFrameTex(), 0, 0, &rect, &Math::Color(1, 1, 1, 1));
					}
				}

				//星
				{
					for (int i = 0; i < INFO.TimeAttackUserStarInfo; i++)
					{
						Math::Vector2 pos = { 0,startposY - i * 80.0f };
						Math::Vector2 scale = { 0.23f,0.23f };
						Math::Matrix s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
						Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
						Math::Matrix mat = s * t;
						KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
						Math::Rectangle rect = { 0,0,292,280 };
						KdShaderManager::GetInstance().m_spriteShader.DrawTex(&CommonTex.GetStarTex(), 0, 0, &rect, &Math::Color(1, 1, 1, 1));
					}
				}
			}
		}
		break;
	case StageSelectButton::BACK:
		break;
	default:
		break;
	}
}

void C_StageSelectUi::BackGroundInit()
{

	BlackBackInit();
	//背景
	m_backgroundtex.Load("Texture/Ui/BackGround/Title/TitleBackGround.png");
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

	MoveBackGroundInit();
}

void C_StageSelectUi::BackGroundUpdate()
{
	BlackBackUpdate();

	m_backgroundscalemat = Math::Matrix::CreateScale(m_backgroundscale.x, m_backgroundscale.y, 1);
	m_backgroundtransmat = Math::Matrix::CreateTranslation(m_backgroundpos.x, m_backgroundpos.y, 0);
	m_backgroundmat = m_backgroundscalemat * m_backgroundtransmat;

	MoveBackGroundUpdate();
}

void C_StageSelectUi::BackGroundDraw()
{
	BlackBackDraw();

	//背景描画
	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_backgroundmat);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_backgroundtex,0,0, &m_backgroundrect, &m_backgroundcolor);

	MoveBackGroundDraw();
}

void C_StageSelectUi::MoveBackGroundInit()
{
	m_movebackgroundtex.Load("Texture/Ui/BackGround/Title/TitleMoveBackGround.png");
	m_movebackgroundpos = { 0,0 };

	m_movebackgroundrect = { 0,0,11520,720 };
	m_movebackgroundpos2 = { m_movebackgroundpos.x + m_movebackgroundrect.width,0 };

}
void C_StageSelectUi::MoveBackGroundUpdate()
{
	m_movebackgroundpos.x -= 3.0f;
	m_movebackgroundpos2.x -= 3.0f;

	if (m_movebackgroundpos.x <= -m_movebackgroundrect.width)
	{
		m_movebackgroundpos.x = m_movebackgroundpos2.x + m_movebackgroundrect.width;
	}
	if (m_movebackgroundpos2.x <= -m_movebackgroundrect.width)
	{
		m_movebackgroundpos2.x = m_movebackgroundpos.x + m_movebackgroundrect.width;
	}

	m_movebackgroundmat = Math::Matrix::CreateTranslation(m_movebackgroundpos.x, m_movebackgroundpos.y, 1);
	m_movebackgroundmat2 = Math::Matrix::CreateTranslation(m_movebackgroundpos2.x, m_movebackgroundpos2.y, 1);

}
void C_StageSelectUi::MoveBackGroundDraw()
{
	Math::Color color = { 10.0f,10.0f,10.0f,0.25f };

	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_movebackgroundmat);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_movebackgroundtex, 0, 0, &m_movebackgroundrect, &color);

	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_movebackgroundmat2);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_movebackgroundtex, 0, 0, &m_movebackgroundrect, &color);
}

void C_StageSelectUi::PlayerInit()
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

	m_player->TitleInit();
}
void C_StageSelectUi::PlayerUpdate()
{
	m_player->TitleUpdate();
}
void C_StageSelectUi::PlayerDraw()
{
	m_player->TitleDraw();
}