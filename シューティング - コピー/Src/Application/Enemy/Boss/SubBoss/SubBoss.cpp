#include "SubBoss.h"
#include"../../../Common/CommonAPI.h"
#include"../../../Skill/SkillManager.h"
#include"../../../Hit/HitManager.h"
#include"../../../Scenes/SceneManager.h"

void C_SubBoss::Init(Math::Vector2 pos)
{
	m_enemytype = EnemySType::SubBoss;

	m_nonetime = 0;
	
	//ステータス
	m_maxhp = 2000;
	m_hp = m_maxhp;

	m_score = 5000000;

	m_skilltype = SkillType::None;

	//アニメーション用
	m_anim = { 0,0 };

	m_pos = pos;

	//移動量
	m_stoppos = { 500,pos.y };
	m_movespeed = { 4,4 };
	m_angle = atan2(m_stoppos.y - m_pos.y, m_stoppos.x - m_pos.x);
	m_move.x = cosf(m_angle) * m_movespeed.x;
	m_move.y = sinf(m_angle) * m_movespeed.y;

	//サイズ
	m_scale = { 1,1 };
	//カラー
	m_color = { 1,1,1,1 };
	//生存フラグ
	m_alive = true;

	m_texangle = DirectX::XMConvertToRadians(180) + COMMONAPI.GetTextureAngleAdjustment(TextureAngle::Top);

	//エンジン用
	m_engineanim = { 0,0 };
	m_engineanimmaxnum = { 12,0 };

	//死亡演出用
	m_deathanim = { 0,0 };
	m_deathanimmaxnum = { 12,0 };

	//レーザー
	m_moveanim = { 0,0 };
	m_moveanimmaxnum = { 60,0 };
	m_laserflg = false;
	m_laserprogresstime = 0;

	//パターン
	m_pattern = Pattern::Start;

	//行動パターン
	m_actionpattern = SubBossActionPattern::None;
	m_nextactionpattern = SubBossActionPattern::p1_Laser;
	m_nonetime = NoneTime;

	//半径
	m_halfsize = m_rect * m_scale / 2;
	m_radius = m_rect.x * m_scale.x / 2;

	//当たり判定
	//当たり判定管理に渡す
	if (auto hm = m_hitmanager.lock())
	{
		hm->SetEnemy(shared_from_this());
	}

	m_scalemat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1);
	m_rotatemat = Math::Matrix::CreateRotationZ(m_texangle);
	m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scalemat * m_rotatemat * m_transmat;
}

void C_SubBoss::Update()
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
	m_rotatemat = Math::Matrix::CreateRotationZ(m_texangle);
	m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scalemat * m_rotatemat * m_transmat;
}

void C_SubBoss::Draw()
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

	if (m_pattern != Pattern::Death&&m_actionpattern!=SubBossActionPattern::p1_Laser)
	{
		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_mat);
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_tex, 0, 0,
			&Math::Rectangle(0, 0, m_rect.x, m_rect.y), &m_color);
		//エンジン
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_enginetex, 0, 0,
			&Math::Rectangle((int)m_engineanim.x * m_rect.x, (int)m_engineanim.y * m_rect.y, m_rect.x, m_rect.y),
			&m_color);
	}
}

void C_SubBoss::StartDirectionUpdate()
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
m_rotatemat = Math::Matrix::CreateRotationZ(m_texangle);
m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
m_mat = m_scalemat * m_rotatemat * m_transmat;
}

void C_SubBoss::Release()
{
	// 必要なら解放処理
}


//========================
// Start
//========================
void C_SubBoss::StartUpdate()
{
	m_move = { -1,0 };

	m_pos.x += m_move.x*3;

	// 例：停止位置まで移動
	if (m_pos.x <= m_stoppos.x)
	{
		m_pos = m_stoppos;
		m_move = { 0,0 };

		// ループ状態へ
		m_pattern = Pattern::Loop;

		// 最初の行動
		SetActionPattern(SubBossActionPattern::p1_Laser);
	}
}

void C_SubBoss::StartDraw()
{
	// 仮描画
}


//========================
// Loop
//========================
void C_SubBoss::LoopUpdate()
{
	// 現在の行動パターンごとに分岐
	switch (m_actionpattern)
	{
	case SubBossActionPattern::None:
		NoneUpdate();
		break;
	case SubBossActionPattern::p1_Laser:
		p1_LaserUpdate();
		break;

	case SubBossActionPattern::p2_Barrier:
		p2_BarrierUpdate();
		break;
	}
}

void C_SubBoss::LoopDraw()
{
	switch (m_actionpattern)
	{
	case SubBossActionPattern::p1_Laser:
		p1_LaserDrawSprite();
		break;

	case SubBossActionPattern::p2_Barrier:
		p2_BarrierDrawSprite();
		break;
	}
}


//========================
// Death
//========================
void C_SubBoss::DeathUpdate()
{
	// 死亡処理
	//死亡アニメーション用
	m_deathanim.x += 0.1f;
	//マックス以上になったら,4コマなら4
	if (m_deathanim.x >= m_deathanimmaxnum.x)
	{
		m_deathanim.x = m_deathanimmaxnum.x;
		//死亡演出が終了したら消去
		m_alive = false;
		SCENEMANAGER.SetScore(m_score);
	}
}

void C_SubBoss::DeathDraw()
{
	// 死亡演出描画
	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_mat);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_deathtex, 0, 0,
		&Math::Rectangle((int)m_deathanim.x * m_rect.x, (int)m_deathanim.y * m_rect.y, m_rect.x, m_rect.y),
		&m_color);
}


void C_SubBoss::NoneInit(SubBossActionPattern pattern)
{
	m_actionpattern = SubBossActionPattern::None;
	m_nextactionpattern = pattern;
	m_nonetime = NoneTime;
}

//========================
// パターン初期化
//========================
void C_SubBoss::p1_LaserInit()
{
	// レーザー初期化
	m_skilltype = SkillType::Laser;

	m_lasertime = LaserTime;

	m_laserflg = false;
	m_laserprogresstime = 0;
}

void C_SubBoss::p2_BarrierInit()
{
	// バリア初期化
	m_skilltype = SkillType::Barrier;

	m_barriertime = BarrierTime;

	if (auto sm = m_skillmanager.lock())
	{
		sm->SetEnemySkill(SkillType::Barrier, shared_from_this());
	}
	//m_pattern = Pattern::Death;
}


void C_SubBoss::NoneUpdate()
{
	m_nonetime--;
	if (m_nonetime < 0)
	{
		SetActionPattern(GetPatternExclude(m_nextactionpattern));
	}
}

//========================
// パターン更新
//========================
void C_SubBoss::p1_LaserUpdate()
{
	// レーザー処理

	if (!m_laserflg)
	{
		float prev = m_moveanim.x;
		m_moveanim.x += 0.5f;

		if (prev < 57.0f && m_moveanim.x >= 57.0f)
		{
			if (auto sm = m_skillmanager.lock())
			{
				sm->SetEnemySkill(SkillType::Laser, shared_from_this());
			}

			m_laserflg = true;
			m_laserprogresstime = 180;
		}
	}

	if (m_laserflg)
	{
		m_laserprogresstime--;

		if (m_laserprogresstime <= 0)
		{
			m_moveanim.x += 0.1f;
		}
	}

	//マックス以上になったら,4コマなら4
	if (m_moveanim.x >= m_moveanimmaxnum.x)
	{
		NoneInit(SubBossActionPattern::p1_Laser);
		m_moveanim.x = {};
	}
}

void C_SubBoss::p2_BarrierUpdate()
{
	// バリア処理
	m_barriertime--;
	if (m_barriertime < 0)
	{
		NoneInit(SubBossActionPattern::p2_Barrier);
	}
}


//========================
// パターン描画
//========================
void C_SubBoss::p1_LaserDrawSprite()
{
	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_mat);
	//行動中
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_movetex, 0, 0,
		&Math::Rectangle((int)m_moveanim.x * m_rect.x, (int)m_moveanim.y * m_rect.y, m_rect.x, m_rect.y),
		&m_color);
	//エンジン
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_enginetex, 0, 0,
		&Math::Rectangle((int)m_engineanim.x * m_rect.x, (int)m_engineanim.y * m_rect.y, m_rect.x, m_rect.y),
		&m_color);
}

void C_SubBoss::p2_BarrierDrawSprite()
{
	// バリア描画
}


//========================
// パターン設定
//========================
void C_SubBoss::SetActionPattern(SubBossActionPattern pattern)
{
	switch (pattern)
	{
	case SubBossActionPattern::p1_Laser:
		m_actionpattern = SubBossActionPattern::p1_Laser;

		p1_LaserInit();
		break;
	case SubBossActionPattern::p2_Barrier:
		m_actionpattern = SubBossActionPattern::p2_Barrier;

		p2_BarrierInit();
		break;

	case SubBossActionPattern::None:
	default:
		m_actionpattern = SubBossActionPattern::p2_Barrier;
		p2_BarrierInit();
		break;
	}
}


//========================
// ランダム取得（除外あり）
//========================
SubBossActionPattern C_SubBoss::GetPatternExclude(SubBossActionPattern exclude)
{
	static std::random_device rd;
	static std::mt19937 mt(rd());

	int min = 1;
	int max = static_cast<int>(SubBossActionPattern::SubBossActionPatternNum);

	std::uniform_int_distribution<int> dist(min, max - 1);

	SubBossActionPattern result;

	do
	{
		result = static_cast<SubBossActionPattern>(dist(mt));
	} while (result == exclude);

	return result;
}