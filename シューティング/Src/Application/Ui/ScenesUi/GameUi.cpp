#include "GameUi.h"
#include"Application/Common/CommonTexture.h"
#include"Application/Info.h"
#include"../../Common/CommonAPI.h"
#include"../../Skill/SkillManager.h"
#include"../../Scenes/Game/Game.h"
#include"../../Player/Player.h"
#include"../../Enemy/Boss/Boss/Boss.h"
#include"../../Enemy/Boss/SubBoss/SubBoss.h"
#include"../../Scenes/SceneManager.h"

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

	//Hpバー
	HPBarInit();
}

void C_GameUi::HUDUpdate()
{
	HPBarUpdate();

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

	//Hpバー
	HPBarDraw();
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
	COMMONAPI.NumDraw(SCENEMANAGER.GetScore(), {-290,290}, {0.3f,0.5f}, 10);

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

	m_skillpos = { -160,330 };
	m_skillscale = { 0.4f,0.4f };

	m_OKicontex.Load("Texture/Ui/HUD/OKIcon.png");
	m_NOicontex.Load("Texture/Ui/HUD/NOIcon.png");
	m_Readytex.Load("Texture/Ui/HUD/READY.png");
	m_Locktex.Load("Texture/Ui/HUD/LOCK.png");
}

void C_GameUi::SkillHUDUpdate()
{

}

void C_GameUi::SkillHUDDraw()
{

	auto o = m_owner.lock();

	//スキルアイコン
	{
		Math::Matrix s = Math::Matrix::CreateScale(m_skilliconscale.x, m_skilliconscale.y, 1);
		Math::Matrix t = Math::Matrix::CreateTranslation(m_skilliconpos.x, m_skilliconpos.y, 0);
		Math::Matrix mat = s * t;

		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
		Math::Rectangle rect = { 0,0,300,100 };

		auto sm = o->GetSkillManager();

		Math::Color color = { 1,1,1,1 };

		if (sm)
		{
			if (!sm->GetPlayerSkillFlg())
			{
				color = { 1,1,1,1 };
			}
			else
			{
				color = { 0.3f,0.3f,0.3f,1.0f };
			}
		}

		KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_skillicontexs[m_skilliconindex].get(),0,0, &rect, &color);
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

	//READY LOCK
	{
		if (o)
		{
			auto sm = o->GetSkillManager();

			if (sm)
			{
				Math::Rectangle rect = { 0,0,700,210 };
				Math::Vector2 pos = { 10,330 };
				Math::Vector2 scale = { 0.22f,0.22f };

				Math::Matrix s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
				Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
				Math::Matrix mat = s * t;

				if (sm->GetPlayerSkillFlg())
				{
					KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
					KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_Locktex, rect, 1.0f);
				}
				else
				{
					KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
					KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_Readytex, rect, 1.0f);
				}
			}
		}
	}

	//OKNOアイコン
	{
		if (o)
		{
			auto sm = o->GetSkillManager();

			if (sm)
			{
				Math::Rectangle rect = { 0,0,210,210 };
				Math::Vector2 pos = { -60,330 };
				Math::Vector2 scale = { 0.22f,0.22f };

				Math::Matrix s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
				Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
				Math::Matrix mat = s * t;

				if (sm->GetPlayerSkillFlg())
				{
					KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
					KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_NOicontex, rect, 1.0f);
				}
				else
				{
					KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
					KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_OKicontex, rect, 1.0f);
				}
			}
		}
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

void C_GameUi::HPBarInit()
{
	m_BOSSTexttex.Load("Texture/Ui/Font/BOSS.png");

	m_hpbarrect = {0,0, 980,20 };
	m_hpbarframerect = { 0,0,1040,30 };

	//ボス
	m_bosshpbarstartpos = { 350,240 };
	m_bosshpbarpos = m_bosshpbarstartpos;
	m_bosshpbarscale = { 0.5f,1 };

	//サブボス
	m_subbosshpbarstartpos = { 475,335 };
	m_subbosshpbarscale = { 0.25f,1 };

	m_subBossHpRates.clear();
}

void C_GameUi::HPBarUpdate()
{
	auto o = m_owner.lock();

	if (o)
	{
		auto b = o->GetBoss();


		if (b)
		{
			m_bossHpRate = (float)b->GetHp() / b->GetMaxHp();
			if (m_bossHpRate <= 0)
			{
				m_bossHpRate = 0;
			}
			m_isBossExist = true;
		}

		auto sb = o->GetSubBoss();

		for (auto& s : sb)
		{
			if (!s) continue;

			int id = s->GetId();

			if (id >= m_subBossHpRates.size())
			{
				m_subBossHpRates.resize(id + 1, 0.0f);
			}

			m_subBossHpRates[id] =
				std::max(0.0f, (float)s->GetHp() / s->GetMaxHp());
		}
	}
}


void C_GameUi::HPBarDraw()
{
	//ボステキスト
	{
		Math::Vector2 pos = { 210,300 };
		Math::Vector2 scale = {0.6f,0.6f};

		Math::Matrix s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
		Math::Matrix t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
		Math::Matrix mat = s * t;
	
		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
		Math::Rectangle rect = { 0,0,480,100 };
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_BOSSTexttex, rect, 1.0f);
	}

	auto o = m_owner.lock();

	if (o)
	{
		//ボス
		auto b = o->GetBoss();

		if (m_isBossExist)
		{
			//枠
			{
				Math::Matrix s = Math::Matrix::CreateScale(m_bosshpbarscale.x, m_bosshpbarscale.y, 1);
				Math::Matrix t = Math::Matrix::CreateTranslation(m_bosshpbarstartpos.x, m_bosshpbarpos.y, 0);
				Math::Matrix mat = s * t;

				KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
				KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_hpbarframetex.get(), m_hpbarframerect, 1.0f);

			}

			//Hpバー
			{
				float rate = m_bossHpRate;

				float d = m_hpbarrect.width * (1.0f - rate);
				float offset = d / 2.0f;

				m_bosshpbarpos.x = m_bosshpbarstartpos.x - offset * m_bosshpbarscale.x;

				Math::Matrix s = Math::Matrix::CreateScale(m_bosshpbarscale.x, m_bosshpbarscale.y, 1);
				Math::Matrix t = Math::Matrix::CreateTranslation(m_bosshpbarpos.x, m_bosshpbarpos.y, 0);
				Math::Matrix mat = s * t;

				KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
				Math::Rectangle rect = { 0,0,(long)(m_hpbarrect.width * rate) ,m_hpbarrect.height };
				KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_hpbartex.get(), rect, 1.0f);
			}
		}

		for (int i = 0; i < m_subBossHpRates.size(); i++)
		{
			//枠
			{
				float posY = m_subbosshpbarstartpos.y - (i * (m_hpbarrect.height * m_subbosshpbarscale.y + 25));

				Math::Matrix s = Math::Matrix::CreateScale(m_subbosshpbarscale.x, m_subbosshpbarscale.y, 1);
				Math::Matrix t = Math::Matrix::CreateTranslation(m_subbosshpbarstartpos.x,posY, 0);
				Math::Matrix mat = s * t;

				KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
				KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_hpbarframetex.get(), m_hpbarframerect, 1.0f);
			}

			//Hpバー
			{
				float rate = m_subBossHpRates[i];

				// ここでバー描画
				float d = m_hpbarrect.width * (1.0f - rate);
				float offset = d / 2.0f;

				float posX = m_subbosshpbarstartpos.x- offset*m_subbosshpbarscale.x;
				float posY = m_subbosshpbarstartpos.y - (i * (m_hpbarrect.height * m_subbosshpbarscale.y + 25));


				Math::Matrix s = Math::Matrix::CreateScale(m_subbosshpbarscale.x, m_subbosshpbarscale.y, 1);
				Math::Matrix t = Math::Matrix::CreateTranslation(posX, posY, 0);
				Math::Matrix mat = s * t;

				KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
				Math::Rectangle rect = { 0,0,(long)(m_hpbarrect.width * rate) ,m_hpbarrect.height };
				KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_hpbartex.get(), rect, 1.0f);

			}
		}
	}
}
