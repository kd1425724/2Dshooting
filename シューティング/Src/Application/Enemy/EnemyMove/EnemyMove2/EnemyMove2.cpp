#include"Application/Enemy/EnemyMove/EnemyMove2/EnemyMove2.h"
#include"Application/Info.h"
#include"../../../Player/Player.h"
#include"Application/Enemy/EnemyManager.h"
#include"../../../Skill/Shot/Shot.h"
#include"Application/Common/CommonAPI.h"
#include"Application/Input/Input.h"
#include"../../../Skill/SkillManager.h"
#include"../../../Hit/HitManager.h"
#include"../../../Scenes/Game/Game.h"
#include"../../../Scenes/SceneManager.h"
#include"../../../Effect/EffectManager.h"
void C_EnemyMove2::Init(PosPattern pospattern, MovePattern movepattern, std::shared_ptr<C_Player> player, int i)
{
	//ステータス
	m_hp = 1;
	m_score = 10000;

	//スキル初期化
	//m_skillmanager = nullptr;

	m_skilltype = SkillType::None;

	//プレイヤーのインスタンス
	m_player = move(player);

	//アニメーション用
	m_anim = { 0,0 };
	m_engineanim = { 0,0 };
	m_engineanimmaxnum = { 10,0 };

	//座標
	switch (pospattern)
	{
	case PosPattern::Pattern1:
		m_pos = { /*(float)(i * 60) +*/ 700, (float)0 - 80 + 200};
		break;
	case PosPattern::Pattern2:
		m_pos = { /*(float)(i * 60) + */ 700, (float)0 - 80 + 200 - (1 * 400) };
		break;
	case PosPattern::Pattern3:
		//m_pos = { 0,(float)(i * 60) + 400 };
		break;
	case PosPattern::Pattern4:
		//m_pos = { 0,(float)(i * 60) - 400 };
		break;
	default:
		break;
	}

	//移動量
	switch (movepattern)
	{
	case MovePattern::Pattern1:
		m_movespeed = { 7,7 };
		m_shotpos = { 400,(float)0 - 80 + 200 };
		m_angle = atan2(m_shotpos.y - m_pos.y, m_shotpos.x - m_pos.x);
		m_move.x = cosf(m_angle) * m_movespeed.x;
		m_move.y = sinf(m_angle) * m_movespeed.y;
		break;
	case MovePattern::Pattern2:
		m_movespeed = { 7,7 };
		m_shotpos = { 400,(float)0 - 80 + 200 - (1 * 400) };
		m_angle = atan2(m_shotpos.y - m_pos.y, m_shotpos.x - m_pos.x);
		m_move.x = cosf(m_angle) * m_movespeed.x;
		m_move.y = sinf(m_angle) * m_movespeed.y;
		break;
	case MovePattern::Pattern3:
		m_movespeed = { -2,1 };
		m_move = m_movespeed;
		break;
	case MovePattern::Pattern4:
		m_movespeed = { 0,-2 };
		m_move = m_movespeed;
		break;
	case MovePattern::Pattern5:
		m_movespeed = { 0,2 };
		m_move = m_movespeed;
		break;
	default:
		break;
	}

	//サイズ
	m_scale = { 1,1 };
	//カラー
	m_color = { 1,1,1,1 };
	//生存フラグ
	m_alive = true;
	//発射間隔時間
	m_shotintervaltime = 5 * 60;
	//発射間隔
	m_shotinterval = 0;

	//固有行動
	m_inherentmove = InherentMove2::Start;
	//ストップカウント
	m_stopcount = 0;

	//半径
	m_halfsize = m_rect * m_scale / 2;
	m_radius = m_rect.x * m_scale.x / 2;

	//当たり判定管理に渡す
	if (auto hm = m_hitmanager.lock())
	{
		hm->SetEnemy(shared_from_this());
	}

	m_rotatemat = Math::Matrix::CreateRotationZ(m_angle + COMMONAPI.GetTextureAngleAdjustment(TextureAngle::Top));
	m_mat = m_rotatemat * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);

}
void C_EnemyMove2::Update()
{
	if (m_inherentmove == InherentMove2::Start)
	{
		m_pos += m_move;

		if (m_pos.x < m_shotpos.x)
		{
			m_inherentmove = InherentMove2::Stop;
			m_move = { 0,0 };
			m_stopcount = m_stopcountmax;
		}
	}
	else if (m_inherentmove == InherentMove2::Stop)
	{
		m_stopcount--;

		if (m_stopcount < 0)
		{
			m_inherentmove = InherentMove2::Shot;
		
		}
	}
	else if (m_inherentmove == InherentMove2::Shot)
	{
		if (auto p = m_player.lock())
		{
			m_shotangle = atan2(p->GetPos().y - m_pos.y, p->GetPos().x - m_pos.x) - DirectX::XMConvertToRadians(90);
		}
		for (int i = 0; i < 5; i++)
		{
			float keep = m_shotangle;

			auto s = std::make_shared<C_Shot>();
			auto o = m_owner.lock();
			auto hm = m_hitmanager.lock();

			m_shotangle += DirectX::XMConvertToRadians(i * 45);

			if (o && s && hm)
			{
				s->SetHitManager(hm);
				s->ShotManager(ShotType::EnemyNormalShot, ShotTextureType::Bolt, { 4,0 }, { 48,32 },
					m_pos, m_shotangle, 6);

				o->SetShot(s);
				m_shotangle = keep;
			}
		}

		m_stopcount = m_stopcountmax;

		m_inherentmove = InherentMove2::Stop2;
	}
	else if (m_inherentmove == InherentMove2::Stop2)
	{
		m_stopcount--;

		if (auto p = m_player.lock())
		{
			// プレイヤー方向
			float targetAngle = atan2(
				p->GetPos().y - m_pos.y,
				p->GetPos().x - m_pos.x
			);

			// 角度差
			float diff = targetAngle - m_angle;

			// -π ～ π に補正
			while (diff > DirectX::XM_PI)  diff -= DirectX::XM_2PI;
			while (diff < -DirectX::XM_PI) diff += DirectX::XM_2PI;

			// 回転速度
			float rotateSpeed = 0.08f;

			// 少しずつ向ける
			m_angle += diff * rotateSpeed;
		}
		m_move.x = cosf(m_angle) * m_movespeed.x * 2;
		m_move.y = sinf(m_angle) * m_movespeed.y * 2;

		if (m_stopcount < 0)
		{
			m_inherentmove = InherentMove2::ReStart;
		}
	}
	else if(m_inherentmove==InherentMove2::ReStart)
	{
		m_pos += m_move;
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

	//hpが０になったら
	if (m_hp <= 0)
	{
		m_alive = false;
		EFFECTMANAGER.AddEffect(EffectType::Explosion, m_pos);
		SCENEMANAGER.SetScore(m_score);
	}
	m_rotatemat = Math::Matrix::CreateRotationZ(m_angle+COMMONAPI.GetTextureAngleAdjustment(TextureAngle::Top));
	m_mat = m_rotatemat * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}
void C_EnemyMove2::Draw()
{
	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_mat);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_tex,0,0,&Math::Rectangle(0,0,m_rect.x,m_rect.y), &m_color);
	
	//エンジン
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_enginetex, 0, 0,
		&Math::Rectangle((int)m_engineanim.x * m_rect.x, (int)m_engineanim.y * m_rect.y, m_rect.x, m_rect.y), &m_color);

}
void C_EnemyMove2::Release()
{

}
