#include "EnemyMove1.h"
#include"../../../Player/Player.h"
#include"Application/Enemy/EnemyManager.h"
#include"../../../Skill/Shot/Shot.h"
#include"Application/Common/CommonAPI.h"
#include"Application/Info.h"
#include"../../../Skill/SkillManager.h"
#include"../../../Hit/HitManager.h"
#include"../../../Hit/EnemyHit/Enemy/EnemyHit.h"

void C_EnemyMove1::Init(PosPattern pospattern,MovePattern movepattern,std::shared_ptr<C_Player> player,int i)
{
	//スキル初期化
	//m_skillmanager = nullptr;
	m_skilltype = SkillType::None;

	//プレイヤーのインスタンス
	m_player = move(player);

	m_shot = std::make_shared<C_Shot>();

	m_shot->SetHitManager(m_hitmanager);

	//アニメーション用
	m_anim = { 0,0 };

	//座標
	switch (pospattern)
	{
	case PosPattern::Pattern1:
		m_pos = { (float)(i * 60) + 700, (float)200-INFO.HUDAreaHeight };
		break;
	case PosPattern::Pattern2:
		m_pos = { (float)(i * 60) + 700, (float)-200  };
		break;
	case PosPattern::Pattern3:
		m_pos = { 0,(float)(i * 60) + 640 - INFO.HUDAreaHeight };
		break;
	case PosPattern::Pattern4:
		m_pos = { 100,(float)(i * 60) - 640 };
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
		m_movespeed = { -4,1 };
		m_move = m_movespeed;
		break;
	case MovePattern::Pattern4:
		m_movespeed = { 0,-5 };
		m_move = m_movespeed;
		break;
	case MovePattern::Pattern5:
		m_movespeed = { 0,5 };
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

	m_atk = 5;

	m_hit = std::make_shared<C_EnemyHit>();
	m_hit->SetType(HitType::Enemy);
	m_hit->SetRadius(m_rect.x * m_scale.x / 2);
	m_hit->SetAtk(m_atk);
	//当たり判定管理に渡す
	m_hitmanager->AddHit(m_hit);
}

void C_EnemyMove1::Update()
{
	m_hit->SetPos(m_pos);

	//画面内なら
	if (!COMMONAPI.OutOfPlayArea(m_pos, m_rect * m_scale / 2))
	{
		if (m_shotinterval <= 0)
		{
			m_shot->ShotManager(ShotType::NormalShot, ShotTextureType::Bolt, { 4,0 }, { 48,32 },
				m_pos, m_player->GetPos(),6);//{ m_pos.x,m_pos.y - 100 });

			m_shotinterval = m_shotintervaltime;
		}
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

	//移動
	m_pos += m_move;

	//行列
	m_scalemat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1);
	m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scalemat * m_transmat;
}

void C_EnemyMove1::Draw()
{
	//弾描画
	m_shot->Draw();

	//発生中なら
	if (m_alive)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_tex, 0, 0,
			&Math::Rectangle((int)m_anim.x * m_rect.x, (int)m_anim.y * m_rect.y, m_rect.x,m_rect.y),
			&m_color);
	}
}

void C_EnemyMove1::Release()
{

}

