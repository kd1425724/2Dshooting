#include"EnemyMove3.h"
#include"../../../Player/Player.h"
#include"Application/Enemy/EnemyManager.h"
#include"../../../Skill/Shot/Shot.h"
#include"Application/Common/CommonAPI.h"
#include"Application/Info.h"
#include"../../../Skill/SkillManager.h"
#include"../../../Skill/SkillBase.h"
#include"../../../Hit/HitManager.h"

void C_EnemyMove3::Init(Math::Vector2 pos, UseType type, int i)
{

	m_pos = pos;

	//ステータス
	m_hp = 20;

	m_shot = std::make_shared<C_Shot>();
	if (auto hm = m_hitmanager.lock())
	{
		m_shot->SetHitManager(hm);
	}
	//スキル初期化
	//m_skillmanager = nullptr;
	m_skilltype = SkillType::None;

	m_usetype = type;

	//アニメーション用
	m_anim = { 0,0 };



	m_movespeed = { 4,4 };

	switch (m_usetype)
	{
	case UseType::Player:
		m_texangle = DirectX::XMConvertToRadians(0);

		m_stoppos = { m_pos.x + 40,m_pos.y + 150 - (i * 100) };
		
		m_color = { 1.0,1.0,1,10 };
		break;
	case UseType::Enemy:

		m_texangle = DirectX::XMConvertToRadians(180);

		m_color = { 1,1,1,1 };
		m_stoppos = { m_pos.x - 200,m_pos.y + 150 - (i * 100) };
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

	//半径
	m_halfsize = m_rect * m_scale / 2;
	m_radius = m_rect.x * m_scale.x / 2;

	//当たり判定
	switch (m_usetype)
	{
	case UseType::Player:
		//当たり判定管理に渡す
		if (auto hm = m_hitmanager.lock())
		{
			hm->SetGenerateEnemy(shared_from_this());
		}
		break;
	case UseType::Enemy:
		//当たり判定管理に渡す
		if (auto hm = m_hitmanager.lock())
		{
			hm->SetEnemy(shared_from_this());
		}
		break;
	default:
		break;
	}

	m_deathanimmaxnum = { 9,0 };

	m_scalemat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1);
	m_rotatemat = Math::Matrix::CreateRotationZ(m_texangle + COMMONAPI.GetTextureAngleAdjustment(TextureAngle::Top));
	m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scalemat * m_rotatemat * m_transmat;
}

void C_EnemyMove3::Update()
{
	//hpが０になったら
	if (m_hp <= 0)
	{
		m_inherentmove = InherentMove3::Death;
	}

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
					m_shot->ShotManager(ShotType::EnemyNormalShot, ShotTextureType::Bolt, { 4,0 }, { 48,32 },
						m_pos, { m_pos.x - 100,m_pos.y }, 6);
					break;
				default:
					break;
				}
				m_shotinterval = m_shotintervaltime;
			}
		}
		break;
	case InherentMove3::Death:
		//死亡アニメーション用
		m_deathanim.x += 0.1f;
		//マックス以上になったら,4コマなら4
		if (m_deathanim.x >= m_deathanimmaxnum.x)
		{
			m_deathanim.x = 0;
			//死亡演出が終了したら消去
			m_alive = false;
			return;
		}
		break;
	default:
		break;
	}

	//弾更新
	m_shot->Update();

	//死亡演出じゃなかったら
	if (m_inherentmove != InherentMove3::Death)
	{
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
	}

	//行列
	m_scalemat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1);
	m_rotatemat = Math::Matrix::CreateRotationZ(m_texangle + COMMONAPI.GetTextureAngleAdjustment(TextureAngle::Top));
	m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scalemat*m_rotatemat * m_transmat;
}

void C_EnemyMove3::Draw()
{
	//弾描画
	m_shot->Draw();

	if (m_inherentmove == InherentMove3::Death)
	{
		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_mat);
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_deathtex, 0, 0,
			&Math::Rectangle((int)m_deathanim.x * m_rect.x, (int)m_deathanim.y * m_rect.y, m_rect.x, m_rect.y),
			&m_color);
	}
	else
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

