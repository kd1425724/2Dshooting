#include"CopyScan.h"
#include"../../Enemy/EnemyMoveBase.h"
#include"../../Skill/SkillManager.h"
#include"../../Common/CommonTexture.h"

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
		auto e = m_enemy.lock();

		if (e)
		{
			std::shared_ptr<C_SkillManager> sm = m_skillmanager.lock();

			if (sm)
			{
				sm->SetPlayerSkill(e->GetSkillType());
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
		// 実際はお前の環境の描画APIに合わせて書く
		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_mat);
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(tex.get(), 0, 0, &rect, &color);
	}

	//スキャン中
	{
		Math::Matrix scalemat = Math::Matrix::CreateScale(m_scale);
		Math::Matrix transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
		Math::Matrix mat = scalemat * transmat;
		Math::Rectangle rect = { 0,0,480,100 };
		Math::Color color = { 0,1,0,0.7f };
		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(&CommonTex.GetScaningTextTex(), 0, 0, &rect, &color);
	}
}