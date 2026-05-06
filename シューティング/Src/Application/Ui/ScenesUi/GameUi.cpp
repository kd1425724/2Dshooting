#include "GameUi.h"
#include"Application/Common/CommonTexture.h"
#include"Application/Info.h"
#include"../../Common/CommonAPI.h"
#include"../../Skill/SkillManager.h"
#include"../../Scenes/Game/Game.h"
#include"../../Player/Player.h"
void C_GameUi::Init()
{
	BackGroundInit();

	HUDInit();
}

void C_GameUi::Update()
{
	BackGroundUpdate();

	HUDUpdate();
}

void C_GameUi::Draw()
{
	HUDDraw();
}

//背景
void C_GameUi::BackGroundInit()
{

	//背景
	m_backgroundtex.Load("Texture/Ui/BackGround/Game/GameBackGround.png");

	//黒背景
	BlackBackInit();

	//座標
	m_backgroundpos = { 0,0 };
	//サイズ
	m_backgroundscale = { 1.0f,1.0f };
	//アニメーション用
	m_backgroundanim = { 0,0 };
	//切り取り範囲
	m_backgroundrect = { 0,0,4096,4096 };
	//アニメーション用
	m_backgroundanim = { 0,0 };
	//カラー
	m_backgroundcolor = { 1,1,1,1 };

	m_backgroundpos2 = { m_backgroundpos.x + m_backgroundrect.width,0 };
}
void C_GameUi::BackGroundUpdate()
{
	//黒背景
	BlackBackUpdate();

	m_backgroundpos.x -= 6.0f;
	m_backgroundpos2.x -= 6.0f;

	if (m_backgroundpos.x <= -m_backgroundrect.width)
	{
		m_backgroundpos.x = m_backgroundpos2.x+ m_backgroundrect.width;
	}
	if (m_backgroundpos2.x <= -m_backgroundrect.width)
	{
		m_backgroundpos2.x = m_backgroundpos.x+ m_backgroundrect.width;
	}

	m_backgroundscalemat = Math::Matrix::CreateScale(m_backgroundscale.x, m_backgroundscale.y, 1);
	m_backgroundtransmat = Math::Matrix::CreateTranslation(m_backgroundpos.x, m_backgroundpos.y, 0);
	m_backgroundmat = m_backgroundscalemat * m_backgroundtransmat;

	m_backgroundtransmat2 = Math::Matrix::CreateTranslation(m_backgroundpos2.x, m_backgroundpos.y, 0);
	m_backgroundmat2 = m_backgroundtransmat2;
}
void C_GameUi::BackGroundDraw()
{
	//黒背景
	BlackBackDraw();

	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_backgroundmat);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_backgroundtex, 0, 0, &Math::Rectangle(0, 0, m_backgroundrect.width, m_backgroundrect.height), &m_backgroundcolor);
	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_backgroundmat2);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_backgroundtex, 0, 0, &Math::Rectangle(0, 0, m_backgroundrect.width, m_backgroundrect.height), &m_backgroundcolor);
}

void C_GameUi::SetSkill(SkillType type)
{
	if (type <= SkillType::None)
	{
		m_skilliconindex = 0; // デフォルト
	}
	else
	{
		m_skilliconindex = (int)type - 1;
	}
}

void C_GameUi::Release()
{
	m_backgroundtex.Release();
	m_HUDareatex.Release();
}

void C_GameUi::HUDInit()
{
	//HUDエリア
	m_HUDareatex.Load("Texture/Ui/HUD/GameHUDArea.png");

	//共通
	m_HUDarearect = { 0,0,INFO.HUDAreaWidth ,INFO.HUDAreaHeight };
	m_HUDareascale = { 1.0f,1.0f };
	m_HUDareacolor = { 1.0f,1.0f,1.0f,1 };

	
	m_HUDareapos = { 0,(float)INFO.ScrHeight / 2 - INFO.HUDAreaHeight / 2 };

	//スコア表示用
	ScoreHUDInit();

	//スキル表示
	SkillHUDInit();

	//残機
	LifeHUDInit();
}

void C_GameUi::HUDUpdate()
{
	
	m_HUDareascalemat = Math::Matrix::CreateScale(m_HUDareascale.x, m_HUDareascale.y, 1);
	m_HUDareatransmat = Math::Matrix::CreateTranslation(m_HUDareapos.x, m_HUDareapos.y, 0);
	m_HUDareamat = m_HUDareascalemat * m_HUDareatransmat;
	
}

void C_GameUi::HUDDraw()
{
	
	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_HUDareamat);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_HUDareatex, 0, 0, &m_HUDarearect, &m_HUDareacolor);

	//スコア表示用
	ScoreHUDDraw();

	//スキル
	SkillHUDDraw();

	//残機
	LifeDraw();
}

void C_GameUi::ScoreHUDInit()
{
	m_scorepos = { -500,340 };

	m_scorescale = { 0.3f,0.3f };
}

void C_GameUi::ScoreHUDUpdate()
{

}
void C_GameUi::ScoreHUDDraw()
{
	//スコア表示
	COMMONAPI.NumDraw(100, {-290,290}, {0.3f,0.5f}, 10);

	Math::Matrix s = Math::Matrix::CreateScale(m_scorescale.x, m_scorescale.y, 1);
	Math::Matrix t = Math::Matrix::CreateTranslation(m_scorepos.x, m_scorepos.y, 0);
	Math::Matrix mat = s * t;

	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
	Math::Rectangle rect = { 0,0,480,100 };
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_scoretex.get(), rect, 1.0f);
}

void C_GameUi::SkillHUDInit()
{
	m_skilliconpos = { -70,255 };
	m_skilliconscale = { 1,1 };

	m_skillpos = { -150,330 };
	m_skillscale = { 0.4f,0.4f };
}

void C_GameUi::SkillHUDUpdate()
{

}

void C_GameUi::SkillHUDDraw()
{
	//スキルアイコン
	{
		Math::Matrix s = Math::Matrix::CreateScale(m_skilliconscale.x, m_skilliconscale.y, 1);
		Math::Matrix t = Math::Matrix::CreateTranslation(m_skilliconpos.x, m_skilliconpos.y, 0);
		Math::Matrix mat = s * t;

		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
		Math::Rectangle rect = { 0,0,300,100 };
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_skillicontexs[m_skilliconindex].get(), rect, 1.0f);
	}
	
	//スキル
	{
		Math::Matrix s = Math::Matrix::CreateScale(m_skillscale.x, m_skillscale.y, 1);
		Math::Matrix t = Math::Matrix::CreateTranslation(m_skillpos.x, m_skillpos.y, 0);
		Math::Matrix mat = s * t;

		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
		Math::Rectangle rect = { 0,0,480,100 };
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_SKILLtex.get(), rect, 1.0f);

	}
}

void C_GameUi::LifeHUDInit()
{
	m_lifestartpos = { -420,235 };

	m_lifescale = { 0.7f,0.7f };

	m_LIFETextpos = { -517,235 };
	m_LIFETextscale = { 0.4f,0.4f };
	m_LIFETextrect = { 0,0,480,100 };
}

void C_GameUi::LifeDraw()
{
	{
		Math::Matrix s = Math::Matrix::CreateScale(m_LIFETextscale.x, m_LIFETextscale.y, 1);
		Math::Matrix t = Math::Matrix::CreateTranslation(m_LIFETextpos.x, m_LIFETextpos.y, 0);
		Math::Matrix mat = s * t;
		
		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_LIFETexttex.get(), m_LIFETextrect, 1.0f);
	}

	{
		auto o = m_owner.lock();

		float w = CommonTex.GetPlayerRect().width;

		Math::Matrix s = Math::Matrix::CreateScale(m_lifescale.x, m_lifescale.y, 1);

		if (o)
		{
			for (int i = 0; i < o->GetPlayer()->GetHp(); i++)
			{
				Math::Vector2 pos = { m_lifestartpos.x + w * m_lifescale.x * i,m_lifestartpos.y };

				Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
				Math::Matrix mat = s * t;

				KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
				KdShaderManager::GetInstance().m_spriteShader.DrawTex(&CommonTex.GetPlayerTex(),
					CommonTex.GetPlayerRect(), 1.0f);
			}
		}
	}
}
