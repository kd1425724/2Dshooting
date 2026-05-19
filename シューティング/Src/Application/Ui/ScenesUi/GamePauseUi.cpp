#include "GamePauseUi.h"
#include"../../Common/CommonTexture.h"
#include"../../Scenes/SceneManager.h"
#include"../../Input/Input.h"
void C_GamePauseUi::Init()
{
	m_PAUSEtex.Load("Texture/Ui/HUD/PAUSE/PAUSE.png");

	m_EXITNOtex.Load("Texture/Ui/HUD/PAUSE/EXITNO.png");
	m_EXITOKtex.Load("Texture/Ui/HUD/PAUSE/EXITOK.png");

	m_BACKNOtex.Load("Texture/Ui/HUD/PAUSE/BACKNO.png");
	m_BACKOKtex.Load("Texture/Ui/HUD/PAUSE/BACKOK.png");

	Math::Color color = { 1,1,1,1 };
	Math::Vector2 scale = { 0.3f,0.3f };
	Math::Rectangle rect = { 0,0,700,210 };

	//タイトルへ戻るボタン
	{
		Math::Vector2 pos = { -200,-220 };
	
		CreateSpriteItemInit(pos, rect, scale, &m_EXITNOtex, color, &m_EXITOKtex);
		SetAction((int)GamePauseButton::EXIT,[]()
			{
				SCENEMANAGER.push(SceneType::Title, true,true);
			}
		);
	}

	//戻るボタン
	{
		Math::Vector2 pos = { 200,-220 };
		
		CreateSpriteItemInit(pos, rect, scale, &m_BACKNOtex, color, &m_BACKOKtex);
		SetAction((int)GamePauseButton::BACK, []()
			{
				SCENEMANAGER.pop();
			}
		);
	}

	m_button = GamePauseButton::BACK;

	m_backgroundalpha = 0.5f;

	//操作説明
	KeyInit();
}

void C_GamePauseUi::Update()
{
	CreateSpriteItemUpdate();

	if (Input.GetUserKey(UserKeyType::Top) && !Input.GetUserKeyFlg(UserKeyType::Top)|| 
		Input.GetUserKey(UserKeyType::Right) && !Input.GetUserKeyFlg(UserKeyType::Right))
	{
		if (m_button != GamePauseButton::BACK)
		{
			m_button = static_cast<GamePauseButton>(static_cast<int>(m_button) + 1);
		}
		else
		{
			m_button = static_cast<GamePauseButton>(static_cast<int>(m_button) - 1);
		}
	}

	if (Input.GetUserKey(UserKeyType::Bottom) && !Input.GetUserKeyFlg(UserKeyType::Bottom)||
	Input.GetUserKey(UserKeyType::Left) && !Input.GetUserKeyFlg(UserKeyType::Left))
	{
		if (m_button != GamePauseButton::EXIT)
		{
			m_button = static_cast<GamePauseButton>(static_cast<int>(m_button) - 1);
		}
		else
		{
			m_button = static_cast<GamePauseButton>(static_cast<int>(m_button) + 1);
		}
	}
	
	if (Input.GetUserKey(UserKeyType::ZKey) && !Input.GetUserKeyFlg(UserKeyType::ZKey))
	{
		ButtonUpdate((int)m_button);
	}


}

void C_GamePauseUi::Draw()
{
	CreateSpriteItemDraw();

	ButtonDraw((int)m_button);

	PAUSEDraw();

	KeyDraw();
}

void C_GamePauseUi::BackGroundInit()
{
}

void C_GamePauseUi::BackGroundUpdate()
{
}

void C_GamePauseUi::BackGroundDraw()
{
	Math::Vector2 pos = { 0,0 };

	Math::Matrix mat = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);

	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
	Math::Color color = { 0,0,0,m_backgroundalpha };
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(&CommonTex.GetWhiteBackTex(),0,0, &CommonTex.GetWhiteBackTexRect(),&color);
}

void C_GamePauseUi::Release()
{
	m_PAUSEtex.Release();
	m_EXITNOtex.Release();
	m_EXITOKtex.Release();
	m_BACKNOtex.Release();
	m_BACKOKtex.Release();
	m_ArrowKeyTex.Release();
	m_SpaceKeyTex.Release();
	m_EKeyTex.Release();
	m_ShotTextTex.Release();
	m_EscKeyTex.Release();
}

void C_GamePauseUi::PAUSEDraw()
{
	Math::Vector2 pos = { 0,300 };
	Math::Vector2 scale = { 1.0f,1.0f };
	Math::Rectangle rect = { 0,0,480,100 };

	Math::Matrix s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
	Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
	Math::Matrix mat = s * t;

	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_PAUSEtex, rect, 1.0f);
}

void C_GamePauseUi::KeyInit()
{
	m_ArrowKeyTex.Load("Texture/Ui/Button/ArrowKey.png");
	m_SpaceKeyTex.Load("Texture/Ui/Button/SPACEKey.png");
	m_EKeyTex.Load("Texture/Ui/Button/EKey.png");
	m_ShotTextTex.Load("Texture/Ui/Font/SHOT.png");
	m_MoveTextTex.Load("Texture/Ui/Font/MOVE.png");
	m_EscKeyTex.Load("Texture/Ui/Button/ESCKey.png");
}

void C_GamePauseUi::KeyDraw()
{
	Math::Vector2 scale = { 0.5f,0.5f};
	Math::Color color = { 3.0f,3.0f,3.0f,1.0f };

	//Move
	{
		Math::Vector2 texscale = { 0.5f,0.5f };
		Math::Vector2 pos = { -150,180 };

		Math::Matrix s = Math::Matrix::CreateScale(texscale.x, texscale.y, 1);
		Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
		Math::Matrix mat = s * t;

		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
		Math::Rectangle rect = { 0,0,480,100 };
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_MoveTextTex, 0, 0, &rect, &color);
	}
	//Arrow
	{
		
		Math::Vector2 pos = { 150,180 };

		Math::Matrix s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
		Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
		Math::Matrix mat = s * t;

		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
		Math::Rectangle rect = { 0,0,300,200 };
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_ArrowKeyTex,0,0, &rect, &color);
	}
	//SHOT
	{
		Math::Vector2 texscale = { 0.5f,0.5f };
		Math::Vector2 pos = { -150,80 };

		Math::Matrix s = Math::Matrix::CreateScale(texscale.x, texscale.y, 1);
		Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
		Math::Matrix mat = s * t;

		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
		Math::Rectangle rect = { 0,0,480,100 };
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_ShotTextTex, 0, 0, &rect, &color);
	}
	//SPACE
	{
		//Math::Vector2 scale = { 1,1 };
		Math::Vector2 pos = { 150,80 };

		Math::Matrix s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
		Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
		Math::Matrix mat = s * t;

		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
		Math::Rectangle rect = { 0,0,373,80 };
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_SpaceKeyTex, 0, 0, &rect, &color);
	}
	//SKILL
	{
		Math::Vector2 texscale = { 0.5f,0.5f };
		Math::Vector2 pos = { -150,-20 };

		Math::Matrix s = Math::Matrix::CreateScale(texscale.x, texscale.y, 1);
		Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
		Math::Matrix mat = s * t;

		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
		Math::Rectangle rect = { 0,0,480,100 };
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(&CommonTex.GetSKILLTEXTtex(), 0, 0, &rect, &color);
	}
	//Eキー
	{
		//Math::Vector2 scale = { 1,1 };
		Math::Vector2 pos = { 150,-20 };

		Math::Matrix s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
		Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
		Math::Matrix mat = s * t;

		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
		Math::Rectangle rect = { 0,0,72,80 };
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_EKeyTex, 0, 0, &rect, &color);
	}
	//PAUSE
	{
		Math::Vector2 texscale = { 0.5f,0.5f };
		Math::Vector2 pos = { -150,-120 };

		Math::Matrix s = Math::Matrix::CreateScale(texscale.x, texscale.y, 1);
		Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
		Math::Matrix mat = s * t;

		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
		Math::Rectangle rect = { 0,0,480,100 };
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_PAUSEtex, 0, 0, &rect, &color);
	}
	//ESCキー
	{
		//Math::Vector2 scale = { 1,1 };
		Math::Vector2 pos = { 150,-120 };
		Math::Vector2 texscale = { 1.0f,1.0f };
		Math::Matrix s = Math::Matrix::CreateScale(texscale.x, texscale.y, 1);
		Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
		Math::Matrix mat = s * t;

		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
		Math::Rectangle rect = { 0,0,111,80 };
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_EscKeyTex, 0, 0, &rect, &color);
	}
}
