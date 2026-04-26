#include "Boss.h"
#include"../../../Skill/Shot/Shot.h"
#include"../../../Skill/SkillManager.h"
void C_Boss::Init()
{
	//プレイヤーのインスタンス
	//m_player = move(player);

	m_skillmanager = nullptr;

	m_shot = std::make_shared<C_Shot>();

	//アニメーション用
	m_anim = { 0,0 };

	m_pos = { 700,0 - 60 };

	//移動量
	
	m_stoppos = { 500,0 - 60 };
	m_movespeed = { 4,4 };
	m_angle = atan2(m_stoppos.y - m_pos.y, m_stoppos.x - m_pos.x);
	m_move.x = cosf(m_angle) * m_movespeed.x;
	m_move.y = sinf(m_angle) * m_movespeed.y;

	//サイズ
	m_scale = { 3,3 };
	//カラー
	m_color = { 1,1,1,1 };
	//生存フラグ
	m_alive = true;
	//発射間隔時間
	m_shotintervaltime = 5 * 60;
	//発射間隔
	m_shotinterval = 0;

	m_texangle = DirectX::XMConvertToRadians(90);

	//エンジン用
	m_engineanim = { 0,0 };
	m_engineanimmaxnum = { 12,0 };

	//死亡演出用
	m_deathanim = { 0,0 };
	m_deathanimmaxnum = { 14,0 };

	//パターン
	m_pattern = Pattern::Start;

	//行動パターン
	m_actionpattern = ActionPattern::p1_EnemyGenerate;

	//固有行動
	//m_inherentmove = InherentMove::Start;
	//ストップカウント
	//m_stopcount = 0;

	m_spiralshotangle = DirectX::XMConvertToRadians(0);
	m_spiralshotinterval = 0;
}

void C_Boss::Update()
{
	switch (m_pattern)
	{
	case Pattern::Start:
		StartUpdate();
		break;
	case Pattern::Loop:
		LoopUpdate();
		break;
	case Pattern::Death:
		DeathUpdate();
		break;
	default:
		break;
	}

	//ボスが死んだらHpがなくなったら
	if (!m_alive)
	{
		
	}

	
	
	//アニメーション用
	m_anim.x += 0.1f;
	//マックス以上になったら,4コマなら4
	if (m_anim.x >= m_animmaxnum.x)
	{
		m_anim.x = 0;
		if (m_animmaxnum.y != 0)
		{
			m_anim.y++;
		}
	}
	if (m_animmaxnum.y != 0)
	{
		if (m_anim.y > m_animmaxnum.y)
		{
			m_anim = { 0,0 };
		}
	}

	if (m_pattern != Pattern::Death)
	{
		//エンジンアニメーション用
		m_engineanim.x += 0.1f;
		//マックス以上になったら,4コマなら4
		if (m_engineanim.x >= m_engineanimmaxnum.x)
		{
			m_engineanim.x = 0;
			if (m_engineanimmaxnum.y != 0)
			{
				m_engineanim.y++;
			}
		}
		if (m_engineanimmaxnum.y != 0)
		{
			if (m_engineanim.y > m_engineanimmaxnum.y)
			{
				m_engineanim = { 0,0 };
			}
		}
	}

	m_scalemat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1);
	m_rotatemat = Math::Matrix::CreateRotationZ(m_texangle);
	m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scalemat*m_rotatemat * m_transmat;
}

void C_Boss::Draw()
{
	switch (m_pattern)
	{
	case Pattern::Start:
		StartDraw();
		break;
	case Pattern::Loop:
		LoopDraw();
		break;
	case Pattern::Death:
		DeathDraw();
		break;
	default:
		break;
	}

	if (m_pattern != Pattern::Death)
	{
		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_mat);
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_tex, 0, 0,
			&Math::Rectangle(0, 0, m_rect.x, m_rect.y), &m_color);
		//エンジン
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_enginetex, 0, 0,
			&Math::Rectangle((int)m_engineanim.x * m_rect.x, (int)m_engineanim.y * m_rect.y, m_rect.x, m_rect.y), &m_color);
	}
}

void C_Boss::Release()
{
}

void C_Boss::StartUpdate()
{
	m_pos += m_move;

	if (m_pos.x <= m_stoppos.x)
	{
		m_pos = m_stoppos;
		m_move = { 0,0 };

		m_pattern = Pattern::Loop;

		m_actionpattern = ActionPattern::p1_EnemyGenerate;
	}
}

void C_Boss::StartDraw()
{
}

void C_Boss::LoopUpdate()
{
	switch (m_actionpattern)
	{
	case ActionPattern::p1_EnemyGenerate:
		p1_EnemyGenerateUpdate();
		break;
	case ActionPattern::p2_Laser:
		p2_LaserUpdate();
		break;
	case ActionPattern::p3_Barrier:
		p3_BarrierUpdate();
		break;
	case ActionPattern::p4_SpiralShot:
		p4_SpiralUpdate();
		break;
	default:
		break;
	}

	m_shot->Update();

}

void C_Boss::LoopDraw()
{
	switch (m_actionpattern)
	{
	case ActionPattern::p1_EnemyGenerate:
		p1_EnemyGenerateDrawSprite();
		break;
	case ActionPattern::p2_Laser:
		p2_LaserDrawSprite();
		break;
	case ActionPattern::p3_Barrier:
		p3_BarrierDrawSprite();
		break;
	case ActionPattern::p4_SpiralShot:
		p4_SpiralDrawSprite();
		break;
	default:
		break;
	}

	m_shot->Draw();
}

void C_Boss::DeathUpdate()
{
	//死亡アニメーション用
	m_deathanim.x += 0.1f;
	//マックス以上になったら,4コマなら4
	if (m_deathanim.x >= m_deathanimmaxnum.x)
	{
		m_deathanim.x = 0;
		//死亡演出が終了したら消去
		m_alive = false;
	}
}

void C_Boss::DeathDraw()
{
	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_mat);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_deathtex, 0, 0,
		&Math::Rectangle((int)m_deathanim.x * m_rect.x, (int)m_deathanim.y * m_rect.y, m_rect.x, m_rect.y),
		&m_color);
}

void C_Boss::p1_EnemyGenerateInit()
{
	m_enemygeneratetime = EnemyGenerateTime;

	m_skillmanager->SetUseSkill(SkillType::EnemyGenerate, shared_from_this());
}

void C_Boss::p2_LaserInit()
{
	m_pattern = Pattern::Death;
	m_lasertime = LaserTime;

	m_skillmanager->SetUseSkill(SkillType::Laser, shared_from_this());
}

void C_Boss::p3_BarrierInit()
{
	m_pattern = Pattern::Death;
	m_barriertime = BarrierTime;

	m_skillmanager->SetUseSkill(SkillType::Barrier, shared_from_this());
}

void C_Boss::p4_SpiralInit()
{
	m_spiraltime = SpiralTime;
}

void C_Boss::p1_EnemyGenerateUpdate()
{
	m_enemygeneratetime--;

	if (m_enemygeneratetime < 0)
	{
		SetActionPattern(GetRandomPatternExclude(ActionPattern::p1_EnemyGenerate));
	}
}

void C_Boss::p2_LaserUpdate()
{
	m_lasertime--;
	if(m_lasertime<0)
	{
		SetActionPattern(GetRandomPatternExclude(ActionPattern::p2_Laser));
	}
}

void C_Boss::p3_BarrierUpdate()
{
	m_barriertime--;
	if (m_barriertime < 0)
	{
		SetActionPattern(GetRandomPatternExclude(ActionPattern::p3_Barrier));
	}
}

void C_Boss::p4_SpiralUpdate()
{
	m_spiralshotinterval--;

	if (m_spiralshotinterval < 0)
	{
		int count = 3;

		m_spiralshotangle += DirectX::XMConvertToRadians(10);

		for (int i = 0; i < count; i++)
		{
			float angle = m_spiralshotangle + DirectX::XM_2PI * i / count;

			m_shot->ShotManager(
				ShotType::NormalShot,
				ShotTextureType::Bolt,
				{ 4,0 },
				{ 48,32 },
				m_pos,
				angle,
				7
			);
		}
	
		m_spiralshotinterval = SpiralShotInterval;
	}
	
	m_spiraltime--;
	if (m_spiraltime <= 0)
	{
		SetActionPattern(GetRandomPatternExclude(ActionPattern::p4_SpiralShot));
	}
}

void C_Boss::p1_EnemyGenerateDrawSprite()
{
}

void C_Boss::p2_LaserDrawSprite()
{
}

void C_Boss::p3_BarrierDrawSprite()
{
}

void C_Boss::p4_SpiralDrawSprite()
{

}

void C_Boss::SetActionPattern(ActionPattern pattern)
{
	switch (pattern)
	{
	case ActionPattern::p1_EnemyGenerate:
		m_actionpattern = ActionPattern::p1_EnemyGenerate;
	
		p1_EnemyGenerateInit();
		break;
	case ActionPattern::p2_Laser:
		m_actionpattern = ActionPattern::p2_Laser;
		
		p2_LaserInit();
		break;
	case ActionPattern::p3_Barrier:
		m_actionpattern = ActionPattern::p3_Barrier;
	
		p3_BarrierInit();
		break;
	case ActionPattern::p4_SpiralShot:
		m_actionpattern = ActionPattern::p4_SpiralShot;
		
		p4_SpiralInit();
		break;
	default:
		m_actionpattern = ActionPattern::p3_Barrier;
		p3_BarrierInit();
		break;
	}
}

ActionPattern C_Boss::GetRandomPatternExclude(ActionPattern exclude)
{
	static std::random_device rd;
	static std::mt19937 mt(rd());

	// 総数（enumの最後）
	int max = static_cast<int>(ActionPattern::ActionPatternNum);

	std::uniform_int_distribution<int> dist(0, max - 2);
	int r = dist(mt);

	int excludeIndex = static_cast<int>(exclude);

	// 除外分ずらす
	if (r >= excludeIndex)
	{
		r++;
	}

	return static_cast<ActionPattern>(r);
}