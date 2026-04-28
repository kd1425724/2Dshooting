#include"EnemyMove3.h"
#include"../../../Player/Player.h"
#include"Application/Enemy/EnemyManager.h"
#include"../../../Skill/Shot/Shot.h"
#include"Application/Common/CommonAPI.h"
#include"Application/Info.h"
#include"../../../Skill/SkillManager.h"
#include"../../../Skill/SkillBase.h"
#include"../../../Hit/HitManager.h"
#include"../../../Hit/EnemyHit/Enemy/EnemyHit.h"

void C_EnemyMove3::Init(Math::Vector2 pos, UseType type, int i)
{
	m_shot = std::make_shared<C_Shot>();

	//スキル初期化
	//m_skillmanager = nullptr;
	m_skilltype = SkillType::None;

	m_usetype = type;

	//アニメーション用
	m_anim = { 0,0 };

	m_pos = pos;

	m_movespeed = { 4,4 };

	switch (m_usetype)
	{
	case UseType::Player:
		m_stoppos = { m_pos.x + 40,m_pos.y + 150 - (i * 100) };
		
		m_color = { 0,0.5,1,1 };
		break;
	case UseType::Enemy:
		m_color = { 1,1,1,1 };
		m_stoppos = { m_pos.x - 40,m_pos.y + 150 - (i * 100) };
		break;
	default:
		break;
	}	

	m_angle = atan2(m_stoppos.y - m_pos.y, m_stoppos.x - m_pos.x);
	m_move.x = cosf(m_angle) * m_movespeed.x;
	m_move.y = sinf(m_angle) * m_movespeed.y;


	//サイズ
	m_scale = { 1,1 };
	//生存フラグ
	m_alive = true;
	//発射間隔時間
	m_shotintervaltime = 2 * 60;
	//発射間隔
	m_shotinterval = 0;

	m_inherentmove = InherentMove3::Start;

	m_atk = 5;

	//当たり判定
	switch (m_usetype)
	{
	case UseType::Player:
		m_hit = std::make_shared<C_EnemyHit>();
		m_hit->SetType(HitType::S_PlayerGenerateEnemy);
		m_hit->SetRadius(m_rect.x * m_scale.x / 2);
		m_hit->SetAtk(m_atk);
		//当たり判定管理に渡す
		m_hitmanager->AddHit(m_hit);
		break;
	case UseType::Enemy:
		m_hit = std::make_shared<C_EnemyHit>();
		m_hit->SetType(HitType::Enemy);
		m_hit->SetRadius(m_rect.x * m_scale.x / 2);
		m_hit->SetAtk(m_atk);
		//当たり判定管理に渡す
		m_hitmanager->AddHit(m_hit);
		break;
	default:
		break;
	}

	
}

void C_EnemyMove3::Update()
{
	m_hit->SetPos(m_pos);

	switch (m_inherentmove)
	{
	case InherentMove3::Start:
		switch (m_usetype)
		{
		case UseType::Player:
			if (m_pos.x >= m_stoppos.x)
			{
				m_inherentmove = InherentMove3::Stop;
			}
			break;
		case UseType::Enemy:
			if (m_pos.x <= m_stoppos.x)
			{
				m_inherentmove = InherentMove3::Stop;
			}
			break;
		default:
			break;
		}

		//移動
		m_pos += m_move;
		break;
	case InherentMove3::Stop:
		//画面内なら
		if (!COMMONAPI.OutOfPlayArea(m_pos, m_rect * m_scale / 2))
		{
			if (m_shotinterval <= 0)
			{
				switch (m_usetype)
				{
				case UseType::Player:
					m_shot->ShotManager(ShotType::NormalShot, ShotTextureType::Bolt, { 4,0 }, { 48,32 },
						m_pos, { m_pos.x + 100,m_pos.y }, 6);
					break;
				case UseType::Enemy:
					m_shot->ShotManager(ShotType::NormalShot, ShotTextureType::Bolt, { 4,0 }, { 48,32 },
						m_pos, { m_pos.x - 100,m_pos.y }, 6);
					break;
				default:
					break;
				}
				m_shotinterval = m_shotintervaltime;
			}
		}
		break;
	default:
		break;
	}

	

	//弾更新
	m_shot->Update();

	//発射間隔減少
	if (m_shotinterval > 0)
	{
		m_shotinterval--;
		if (m_shotinterval <= 0)
		{
			m_shotinterval = 0;
		}
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

	//行列
	m_scalemat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1);
	m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scalemat * m_transmat;
}

void C_EnemyMove3::Draw()
{
	//弾描画
	m_shot->Draw();

	//発生中なら
	if (m_alive)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_tex, 0, 0,
			&Math::Rectangle((int)m_anim.x * m_rect.x, (int)m_anim.y * m_rect.y, m_rect.x, m_rect.y),
			&m_color);
	}
}

void C_EnemyMove3::Release()
{

}

