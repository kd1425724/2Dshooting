#include"CopyScan.h"
#include"../../Enemy/EnemyMoveBase.h"
#include"../../Skill/SkillManager.h"
#include"../../Common/CommonTexture.h"
#include"../../Effect/EffectManager.h"
#include"../../Skill/Shot/Shot.h"
#include"../../Scenes/Game/Game.h"
#include"../../Scenes/Game2/Game2.h"
void C_CopyScan::Release()
{

}

void C_CopyScan::Init(Math::Vector2 pos, std::shared_ptr<C_SkillManager> skillmanager, std::shared_ptr<C_EnemyMoveBase> enemy)
{
	//座標代入
	m_pos = pos;
	m_scale = 3.0f;
	m_anim = 0;
	m_rect = { 32,32 };
	m_alive = true;
	m_skillmanager = skillmanager;
	m_enemy = enemy;
	m_alpha = 1;
	m_time = 60;
}

void C_CopyScan::Update()
{
	m_time--;

	if(m_time <= 0)
	{
		EFFECTMANAGER.AddEffect(EffectType::CopyScanConplete, m_pos, { 1,1 });

		auto o = m_owner.lock();

		if (o)
		{
			auto s = std::make_shared<C_Shot>();
			if (s)
			{
				auto hm = m_hitmanager.lock();
				auto p = o->GetPlayer();
				if (hm && p)
				{
					s->SetPlayer(p);
					s->SetHitManager(hm);
				}
				s->ShotManager(ShotType::HomingShot, ShotTextureType::CopyBack, { 4,0 }, { 32,32 }, m_pos, 0, 10);
				
				o->SetShot(s);
			}
		}
		else
		{
			auto o2 = m_owner2.lock();
			if (o2)
			{
				auto s = std::make_shared<C_Shot>();
				if (s)
				{
					auto hm = m_hitmanager.lock();
					auto p = o->GetPlayer();
					if (hm&&p)
					{
						s->SetPlayer(p);
						s->SetHitManager(hm);
					}
					s->ShotManager(ShotType::HomingShot, ShotTextureType::CopyBack, { 5,0 }, { 32,32 }, m_pos, 0, 10);

					o->SetShot(s);
				}
			}
		}

		Kill();
	}

	//アニメーション用
	m_anim += 0.3f;
	//マックス以上になったら,4コマなら4
	if (m_anim >= AnimMax)
	{
		m_anim = 0;
	}
}

void C_CopyScan::Draw()
{
	std::shared_ptr<KdTexture> tex = m_tex.lock();

	if (tex)
	{
		//行列
		m_scalemat = Math::Matrix::CreateScale(m_scale);
		m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
		m_mat = m_scalemat * m_transmat;
		Math::Rectangle rect = { (int)m_anim * (long)m_rect.x,0,(long)m_rect.x,(long)m_rect.y };
		Math::Color color = { 1,1,1,m_alpha };
		
		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_mat);
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(tex.get(), 0, 0, &rect, &color);
	}

	//スキャン中
	{
		float scale = 0.3f;
		Math::Matrix scalemat = Math::Matrix::CreateScale(scale);
		Math::Matrix transmat = Math::Matrix::CreateTranslation(m_pos.x-100, m_pos.y, 0);
		Math::Matrix mat = scalemat * transmat;
		Math::Rectangle rect = { 0,0,480,100 };
		Math::Color color = { 0,1,0,0.7f };
		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(CommonTex.GetScaningTextTex().get(), 0, 0, &rect, &color);
	}
}