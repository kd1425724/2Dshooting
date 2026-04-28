#include "SubBoss.h"
#include"../../../Common/CommonAPI.h"
#include"../../../Skill/SkillManager.h"

void C_SubBoss::Init(Math::Vector2 pos)
{
	//m_skillmanager = nullptr;

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
	m_deathanimmaxnum = { 14,0 };

	//パターン
	m_pattern = Pattern::Start;

	//行動パターン
	m_actionpattern = SubBossActionPattern::p1_Laser;
}

void C_SubBoss::Update()
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

void C_SubBoss::Release()
{
	// 必要なら解放処理
}


//========================
// Start
//========================
void C_SubBoss::StartUpdate()
{
	m_pos.x += m_move.x;

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
		m_deathanim.x = 0;
		//死亡演出が終了したら消去
		m_alive = false;
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


//========================
// パターン初期化
//========================
void C_SubBoss::p1_LaserInit()
{
	// レーザー初期化
	m_skilltype = SkillType::Laser;

	m_lasertime = LaserTime;

	m_skillmanager->SetEnemySkill(SkillType::Laser, shared_from_this());
}

void C_SubBoss::p2_BarrierInit()
{
	// バリア初期化
	m_skilltype = SkillType::Barrier;

	m_barriertime = BarrierTime;

	m_skillmanager->SetEnemySkill(SkillType::Barrier, shared_from_this());

	//m_pattern = Pattern::Death;
}


//========================
// パターン更新
//========================
void C_SubBoss::p1_LaserUpdate()
{
	// レーザー処理
	m_lasertime--;
	if (m_lasertime < 0)
	{
		SetActionPattern(GetRandomPatternExclude(SubBossActionPattern::p1_Laser));
	}
}

void C_SubBoss::p2_BarrierUpdate()
{
	// バリア処理
	m_barriertime--;
	if (m_barriertime < 0)
	{
		SetActionPattern(GetRandomPatternExclude(SubBossActionPattern::p2_Barrier));
	}
}


//========================
// パターン描画
//========================
void C_SubBoss::p1_LaserDrawSprite()
{
	// レーザー描画
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
	default:
		m_actionpattern = SubBossActionPattern::p2_Barrier;
		p2_BarrierInit();
		break;
	}
}


//========================
// ランダム取得（除外あり）
//========================
SubBossActionPattern C_SubBoss::GetRandomPatternExclude(SubBossActionPattern exclude)
{
	static std::random_device rd;
	static std::mt19937 mt(rd());

	// 総数（enumの最後）
	int max = static_cast<int>(SubBossActionPattern::SubBossActionPatternNum);

	std::uniform_int_distribution<int> dist(0, max - 2);
	int r = dist(mt);

	int excludeIndex = static_cast<int>(exclude);

	// 除外分ずらす
	if (r >= excludeIndex)
	{
		r++;
	}

	return static_cast<SubBossActionPattern>(r);
}