#include "Boss.h"
#include"../../../Skill/Shot/Shot.h"
#include"../../../Skill/SkillManager.h"
#include"../../../Common/CommonAPI.h"
#include"../../../Hit/HitManager.h"
#include"../../../Info.h"
#include"../../../Scenes/Game/Game.h"

void C_Boss::Init()
{
	m_enemytype = EnemySType::Boss;

	//ステータス
	m_maxhp = 10000;
	m_hp = m_maxhp;

	m_score = 10000000;

	//プレイヤーのインスタンス
	//m_player = move(player);

	m_skilltype = SkillType::None;


	//アニメーション用
	m_anim = { 0,0 };

	m_pos = { 700,0 - (float)INFO.HUDAreaHeight/2 };

	m_moveanim = {};
	m_moveanimmaxnum = { 30,0 };

	//移動量

	m_stoppos = { 500,0 - (float)INFO.HUDAreaHeight / 2 };
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

	m_texangle = DirectX::XMConvertToRadians(180);

	//エンジン用
	m_engineanim = { 0,0 };
	m_engineanimmaxnum = { 12,0 };

	//死亡演出用
	m_deathanim = { 0,0 };
	m_deathanimmaxnum = { 14,0 };

	//パターン
	m_pattern = Pattern::Start;
	
	//行動パターン
	m_actionpattern = BossActionPattern::None;
	m_nextactionpattern = BossActionPattern::p1_EnemyGenerate;
	m_nonetime = NoneTime;


	//固有行動
	//m_inherentmove = InherentMove::Start;
	//ストップカウント
	//m_stopcount = 0;

	m_spiralshotangle = DirectX::XMConvertToRadians(0);
	m_spiralshotinterval = 0;

	//半径
	m_halfsize = m_rect * m_scale / 3.0;
	m_radius = m_rect.x * m_scale.x / 3.0;

	//当たり判定
	//当たり判定管理に渡す
	if (auto hm = m_hitmanager.lock())
	{
		hm->SetEnemy(shared_from_this());
	}
}

void C_Boss::StartDirectionUpdate()
{
	StartUpdate();

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
	m_scalemat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1);
	m_rotatemat = Math::Matrix::CreateRotationZ(m_texangle + COMMONAPI.GetTextureAngleAdjustment(TextureAngle::Top));
	m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scalemat * m_rotatemat * m_transmat;
}

void C_Boss::Update()
{
	switch (m_pattern)
	{
	case Pattern::Start:
		
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
	if (m_hp<=0)
	{
		m_pattern = Pattern::Death;
	}

	
	if (m_pattern != Pattern::Death)
	{
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
	m_rotatemat = Math::Matrix::CreateRotationZ(m_texangle+ COMMONAPI.GetTextureAngleAdjustment(TextureAngle::Top));
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
		if (!m_moveflg)
		{
			KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_mat);
			KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_tex, 0, 0,
				&Math::Rectangle(0, 0, m_rect.x, m_rect.y), &m_color);
		}
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
	switch (m_startpattern)
	{
	case StartPattern::BossStartMove:
		m_move = { -1,0 };

		m_pos += m_move * 3;

		if (m_pos.x <= m_stoppos.x)
		{
			m_pos = m_stoppos;
			m_move = { 0,0 };

			m_pattern = Pattern::Loop;

			m_actionpattern = BossActionPattern::p1_EnemyGenerate;

			m_startpattern = StartPattern::BossStartLaser;
		}
		break;
	case StartPattern::BossStartLaser:
		if (auto sm = m_skillmanager.lock())
		{
			sm->SetEnemySkill(SkillType::Laser, shared_from_this());
		}
		m_startpattern = StartPattern::BossStartStop;
		break;
	case StartPattern::BossStartStop:
		break;
	default:
		break;
	}
}

void C_Boss::StartDraw()
{
}

void C_Boss::LoopUpdate()
{
	switch (m_actionpattern)
	{
	case BossActionPattern::None:
		NoneUpdate();
		break;
	case BossActionPattern::p1_EnemyGenerate:
		p1_EnemyGenerateUpdate();
		break;
	case BossActionPattern::p2_Laser:
		p2_LaserUpdate();
		break;
	case BossActionPattern::p3_Barrier:
		p3_BarrierUpdate();
		break;
	case BossActionPattern::p4_SpiralShot:
		p4_SpiralUpdate();
		break;
	case BossActionPattern::p5_Shot2:
		p5_Shot2Update();
		break;
	default:
		break;
	}
}

void C_Boss::LoopDraw()
{

	if (m_moveflg)
	{
		//行動アニメーション用
		m_moveanim.x += 0.2f;
		//マックス以上になったら,4コマなら4
		if (m_moveanim.x >= m_moveanimmaxnum.x)
		{
			m_moveanim.x = 0;
			m_moveflg = false;
		}

		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_mat);
		//行動中
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_movetex, 0, 0,
			&Math::Rectangle((int)m_moveanim.x * m_rect.x, (int)m_moveanim.y * m_rect.y, m_rect.x, m_rect.y),
			&m_color);
	}
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

void C_Boss::NoneInit(BossActionPattern pattern)
{
	m_moveflg = false;
	if (auto sm = m_skillmanager.lock())
	{
		sm->SetEnemySkill(SkillType::EnemyGenerate, shared_from_this());
	}
	m_actionpattern = BossActionPattern::None;
	m_nextactionpattern = pattern;
	m_nonetime = NoneTime;
}

void C_Boss::p1_EnemyGenerateInit()
{
	m_enemygeneratetime = EnemyGenerateTime;

	if (auto sm = m_skillmanager.lock())
	{
		sm->SetEnemySkill(SkillType::EnemyGenerate, shared_from_this());
	}
}

void C_Boss::p2_LaserInit()
{
	//m_pattern = Pattern::Death;
	m_lasertime = LaserTime;

	if (auto sm = m_skillmanager.lock())
	{
		sm->SetEnemySkill(SkillType::Laser, shared_from_this());
	}
}

void C_Boss::p3_BarrierInit()
{
	//m_pattern = Pattern::Death;
	m_barriertime = BarrierTime;

	if (auto sm = m_skillmanager.lock())
	{
		sm->SetEnemySkill(SkillType::Barrier, shared_from_this());
	}
}

void C_Boss::p4_SpiralInit()
{
	m_spiraltime = SpiralTime;
}

void C_Boss::p5_Shot2Init()
{
	m_shot2time = Shot2Time;
}

void C_Boss::NoneUpdate()
{
	m_nonetime--;
	if (m_nonetime < 0)
	{
		m_moveflg = true;
		SetActionPattern(GetRandomPatternExclude(m_nextactionpattern));
	}
}

void C_Boss::p1_EnemyGenerateUpdate()
{
	m_enemygeneratetime--;

	if (m_enemygeneratetime < 0)
	{
		NoneInit(BossActionPattern::p1_EnemyGenerate);
	}
}

void C_Boss::p2_LaserUpdate()
{
	m_lasertime--;
	if(m_lasertime<0)
	{
		NoneInit(BossActionPattern::p2_Laser);
	}
}

void C_Boss::p3_BarrierUpdate()
{
	m_barriertime--;

	if (m_barriertime % 60 == 0)
	{
		if (auto sm = m_skillmanager.lock())
		{
			sm->SetEnemySkill(SkillType::EnemyGenerate, shared_from_this());
		}
	}

	if (m_barriertime < 0)
	{
		NoneInit(BossActionPattern::p3_Barrier);
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

			auto s = std::make_shared<C_Shot>();
			auto hm = m_hitmanager.lock();
			auto o = m_owner.lock();
			
			s->SetHitManager(hm);
			s->ShotManager(
				ShotType::EnemyNormalShot,
				ShotTextureType::Bolt,
				{ 4,0 },
				{ 48,32 },
				m_pos,
				angle,
				7
			);

			o->SetShot(s);
		}
	
		m_spiralshotinterval = SpiralShotInterval;
	}
	
	m_spiraltime--;
	if (m_spiraltime <= 0)
	{
		NoneInit(BossActionPattern::p4_SpiralShot);
	}
}

void C_Boss::p5_Shot2Update()
{
	m_shot2interval--;

	if (m_shot2interval < 0)
	{

		auto s = std::make_shared<C_Shot>();
		auto hm = m_hitmanager.lock();
		auto o = m_owner.lock();

		s->SetHitManager(hm);
		s->ShotManager(ShotType::EnemyNormalShot,ShotTextureType::Pulse,{ 4,0 },{ 63,32 },
			{ m_pos.x-100,m_pos.y+50 },
			{m_pos.x-200,m_pos.y+40},
			10);
		s->ShotManager(ShotType::EnemyNormalShot,ShotTextureType::Pulse,{ 4,0 },{ 63,32 },
			{ m_pos.x - 100,m_pos.y - 50 },
			{ m_pos.x - 200,m_pos.y-40 },
					10);

		o->SetShot(s);
		

		m_shot2interval = Shot2Interval;
	}

	m_shot2time--;
	if (m_shot2time <= 0)
	{
		NoneInit(BossActionPattern::p5_Shot2);
	}
}


void C_Boss::SetActionPattern(BossActionPattern pattern)
{
	switch (pattern)
	{
	case BossActionPattern::p1_EnemyGenerate:
		m_actionpattern = BossActionPattern::p1_EnemyGenerate;
		m_skilltype = SkillType::EnemyGenerate;
		p1_EnemyGenerateInit();
		break;
	case BossActionPattern::p2_Laser:
		m_actionpattern = BossActionPattern::p2_Laser;
		m_skilltype = SkillType::Laser;
		p2_LaserInit();
		break;
	case BossActionPattern::p3_Barrier:
		m_actionpattern = BossActionPattern::p3_Barrier;
		m_skilltype = SkillType::Barrier;
		p3_BarrierInit();
		break;
	case BossActionPattern::p4_SpiralShot:
		m_actionpattern = BossActionPattern::p4_SpiralShot;
		m_skilltype= GetRandomSkillType();
		p4_SpiralInit();
		break;
	case BossActionPattern::p5_Shot2:
		m_actionpattern = BossActionPattern::p5_Shot2;
		m_skilltype= GetRandomSkillType();
		p5_Shot2Init();
		break;

	case BossActionPattern::None:
	default:
		m_actionpattern = BossActionPattern::p3_Barrier;
		p3_BarrierInit();
		break;
	}
}

BossActionPattern C_Boss::GetRandomPatternExclude(BossActionPattern exclude)
{
	static std::random_device rd;
	static std::mt19937 mt(rd());

	int min = 1;
	int max = static_cast<int>(BossActionPattern::BossActionPatternNum);

	std::uniform_int_distribution<int> dist(min, max - 1);

	BossActionPattern result;

	do
	{
		result = static_cast<BossActionPattern>(dist(mt));
	} while (result == exclude);

	return result;
}
SkillType C_Boss::GetRandomSkillType()
{
	static std::random_device rd;
	static std::mt19937 mt(rd());

	int min = (int)SkillType::EnemyGenerate;
	int max = static_cast<int>(SkillType::Laser);

	std::uniform_int_distribution<int> dist(min, max - 1);

	SkillType result;

	result = static_cast<SkillType>(dist(mt));

	return result;
}