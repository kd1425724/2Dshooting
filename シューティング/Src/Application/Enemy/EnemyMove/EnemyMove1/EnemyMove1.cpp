#include "EnemyMove1.h"
#include"../../../Player/Player.h"
#include"Application/Enemy/EnemyManager.h"
#include"../../../Skill/Shot/Shot.h"
#include"Application/Common/CommonAPI.h"
#include"Application/Info.h"
#include"../../../Skill/SkillManager.h"
#include"../../../Hit/HitManager.h"
#include"../../../Scenes/SceneManager.h"
#include"../../../Scenes/Game/Game.h"
#include"../../../Effect/EffectManager.h"
#include"../../../Sound/Sound.h"

void C_EnemyMove1::Release()
{

}

void C_EnemyMove1::Init(PosPattern pospattern,MovePattern movepattern,std::shared_ptr<C_Player> player,int i)
{
	m_deathflg = false;
	//ステータス
	m_hp =1 ;
	m_score = 30000;


	//スキル初期化
	//m_skillmanager = nullptr;
	m_skilltype = SkillType::None;

	//プレイヤーのインスタンス
	m_player = player;

	if (auto hm = m_hitmanager.lock())
	{
		hm->SetEnemy(shared_from_this());
	}
	//アニメーション用
	m_anim = { 0,0 };
	m_engineanim = {0,0};
	m_engineanimmaxnum = { 10,0 };


	//座標
	switch (pospattern)
	{
	case PosPattern::Pattern1:
		m_pos = { (float)(i * 70) + 700, (float)200-INFO.HUDAreaHeight };
		m_angle = 180;
		break;
	case PosPattern::Pattern2:
		m_pos = { (float)(i * 70) + 700, (float)-200  };
		m_angle = 0;
		break;
	case PosPattern::Pattern3:
		m_pos = { 0,(float)(i * 70) + 640 - INFO.HUDAreaHeight };
		break;
	case PosPattern::Pattern4:
		m_pos = { 100,(float)(i * 70) - 640 };
		break;
	default:
		break;
	}
	
	//移動量
	switch (movepattern)
	{
	case MovePattern::Pattern1:
		m_movespeed = { -4,0 };
		m_move = m_movespeed;
		break;
	case MovePattern::Pattern2:
		m_movespeed = { -4,-1 };
		m_move = m_movespeed;
		break;
	case MovePattern::Pattern3:
		m_movespeed = { -7,1 };
		m_move = m_movespeed;
		break;
	case MovePattern::Pattern4:
		m_movespeed = { 0,-4 };
		m_move = m_movespeed;
		m_angle = 90;
		break;
	case MovePattern::Pattern5:
		m_movespeed = { 0,4 };
		m_move = m_movespeed;
		m_angle = 90;
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

	//半径
	m_halfsize = m_rect * m_scale / 2;
	m_radius = m_rect.x * m_scale.x / 2;

	//行列
	m_scalemat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1);
	m_rotatemat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_angle));
	m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scalemat * m_rotatemat * m_transmat;


}

void C_EnemyMove1::Update()
{

	//画面内なら
	if (!COMMONAPI.OutOfScreen(m_pos, m_rect * m_scale / 2))
	{
		if (m_shotinterval <= 0)
		{
			auto hm = m_hitmanager.lock();
			auto s = std::make_shared<C_Shot>();
			auto o = m_owner.lock();
			if (o && hm && s)
			{


				if (auto p = m_player.lock())
				{
					s->SetHitManager(hm);
					s->ShotManager(ShotType::EnemyNormalShot, ShotTextureType::Bolt, { 4,0 }, { 48,32 },
						m_pos, p->GetPos(), 6);//{ m_pos.x,m_pos.y - 100 });
					o->SetShot(s);
				}
			}
			m_shotinterval = m_shotintervaltime;
		}
	}

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
	if (m_hp <= 0&&!m_deathflg)
	{
		m_deathflg = true;
		m_alive = false;
		EFFECTMANAGER.AddEffect(EffectType::Explosion, m_pos);
		SCENEMANAGER.SetScore(m_score);
		SOUND.SetPlaySE(SEType::NormalExplosionSE);
	}

	//移動
	m_pos += m_move;

	//行列
	m_scalemat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1);
	m_rotatemat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_angle));
	m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scalemat*m_rotatemat * m_transmat;
}

void C_EnemyMove1::Draw()
{
	//発生中なら
	if (m_alive)
	{
		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_mat);
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_tex, 0, 0,
			&Math::Rectangle((int)m_anim.x * m_rect.x, (int)m_anim.y * m_rect.y, m_rect.x,m_rect.y),
			&m_color);

		//エンジン
		//KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_enginetex, 0, 0,
			//&Math::Rectangle((int)m_engineanim.x * m_rect.x, (int)m_engineanim.y * m_rect.y, m_rect.x, m_rect.y), &m_color);
	}
}

