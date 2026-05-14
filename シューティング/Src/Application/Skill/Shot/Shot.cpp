#include "Shot.h"
#include"Application/Common/CommonAPI.h"
#include"../../Hit/HitManager.h"

C_Shot::C_Shot()
{
	m_bolttex.Load("Texture/Skill/Attack/Bolt.png");
	m_pulsetex.Load("Texture/Skill/Attack/Pulse.png");
	m_copyshottex.Load("Texture/Skill/Attack/CopyShot.png");
}
void C_Shot::Release()
{
	m_hitmanager.reset();
	m_normalshot.clear();
}

void C_Shot::ShotManager(ShotType a_type,ShotTextureType a_texturetype, Math::Vector2 a_animmaxnum,Math::Vector2 a_rect, Math::Vector2 a_pos, Math::Vector2 target, int movespeed)
{
	switch (a_type)
	{
	case ShotType::NormalShot:
	case ShotType::EnemyNormalShot:
	case ShotType::CopyShot:
		//初期化
		NormalShotInit(a_type,a_texturetype,a_animmaxnum, a_rect, a_pos, target,movespeed);
		break;
	case ShotType::ShotNum:
		break;
	default:
		break;
	}
}

void C_Shot::ShotManager(ShotType a_type, ShotTextureType a_texturetype, Math::Vector2 a_animmaxnum, Math::Vector2 a_rect, Math::Vector2 a_pos, float a_angle, int movespeed)
{
	switch (a_type)
	{
	case ShotType::NormalShot:
	case ShotType::EnemyNormalShot:
	case ShotType::CopyShot:
		//初期化
		NormalShotInit(a_type,a_texturetype, a_animmaxnum, a_rect, a_pos, a_angle,movespeed);
		break;
	case ShotType::ShotNum:
		break;
	default:
		break;
	}
}

void Shot::Init(ShotType a_type, ShotTextureType a_texturetype, Math::Vector2 a_animmaxnum, Math::Vector2 a_rect, Math::Vector2 a_pos, Math::Vector2 target, int movespeed)
{
	switch (a_type)
	{
	case ShotType::NormalShot:

		//画像設定セット
		 SetTextureSetting(a_texturetype);

		rect = a_rect;
		speed = movespeed;
		pos = a_pos;
		pos.x += rect.x/2;
		angle = atan2(target.y - pos.y, target.x - pos.x);
		move.x = cosf(angle) * speed;
		move.y = sinf(angle) * speed;
		color = { 0,0.8,0,1 };
		alive = true;
		scale = { 1,1 };

		//アニメーション用
		anim = { 0,0 };
		animmaxnum = a_animmaxnum;

		scalemat = Math::Matrix::CreateScale(scale.x, scale.y, 1);
		rotatemat = Math::Matrix::CreateRotationZ(angle+texangle);
		transmat = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
		mat = scalemat * rotatemat * transmat;

		//半径
		m_halfsize = rect * scale / 2;
		m_radius = rect.x * scale.x / 2;

		if (auto hm = m_hitmanager.lock())
		{
			hm->SetPlayerShot(shared_from_this());
		}

		break;
	case ShotType::EnemyNormalShot:

		//画像設定セット
		SetTextureSetting(a_texturetype);

		rect = a_rect;
		speed = movespeed;
		pos = a_pos;
		angle = atan2(target.y - pos.y, target.x - pos.x);
		move.x = cosf(angle) * speed;
		move.y = sinf(angle) * speed;
		color = { 1,1,1,1 };
		alive = true;
		scale = { 1,1 };

		//アニメーション用
		anim = { 0,0 };
		animmaxnum = a_animmaxnum;

		scalemat = Math::Matrix::CreateScale(scale.x, scale.y, 1);
		rotatemat = Math::Matrix::CreateRotationZ(angle + texangle);
		transmat = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
		mat = scalemat * rotatemat * transmat;

		//半径
		m_halfsize = rect * scale / 2;
		m_radius = rect.x * scale.x / 2;

		if (auto hm = m_hitmanager.lock())
		{
			hm->SetEnemyShot(shared_from_this());
		}
		break;
	case ShotType::CopyShot:

		//画像設定セット
		SetTextureSetting(a_texturetype);

		rect = a_rect;
		speed = movespeed;
		pos = a_pos;
		angle = atan2(target.y - pos.y, target.x - pos.x);
		move.x = cosf(angle) * speed;
		move.y = sinf(angle) * speed;
		color = { 1,1,1,1 };
		alive = true;
		scale = { 2,2 };

		//アニメーション用
		anim = { 0,0 };
		animmaxnum = a_animmaxnum;

		scalemat = Math::Matrix::CreateScale(scale.x, scale.y, 1);
		rotatemat = Math::Matrix::CreateRotationZ(angle + texangle);
		transmat = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
		mat = scalemat * rotatemat * transmat;

		//半径
		m_halfsize = rect * scale / 2;
		m_radius = rect.x * scale.x / 2;

		if (auto hm = m_hitmanager.lock())
		{
			hm->SetCopyShot(shared_from_this());
		}
		break;
	case ShotType::ShotNum:
		break;
	default:
		break;
	}
}

void Shot::Init(ShotType a_type, ShotTextureType a_texturetype, Math::Vector2 a_animmaxnum, Math::Vector2 a_rect, Math::Vector2 a_pos, float a_angle, int movespeed)
{
	switch (a_type)
	{
	case ShotType::NormalShot:

		//画像設定セット
		SetTextureSetting(a_texturetype);

		rect = a_rect;
		speed = movespeed;
		pos = a_pos;
		angle = a_angle;
		move.x = cosf(angle) * speed;
		move.y = sinf(angle) * speed;
		color = { 1,1,1,1 };
		alive = true;
		scale = { 1,1 };

		//アニメーション用
		anim = { 0,0 };
		animmaxnum = a_animmaxnum;

		scalemat = Math::Matrix::CreateScale(scale.x, scale.y, 1);
		rotatemat = Math::Matrix::CreateRotationZ(angle + texangle);
		transmat = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
		mat = scalemat * rotatemat * transmat;

		//半径
		m_halfsize = rect * scale / 2;
		m_radius = rect.x * scale.x / 2;

		if (auto hm = m_hitmanager.lock())
		{
			hm->SetPlayerShot(shared_from_this());
		}

		break;
	case ShotType::EnemyNormalShot:
		//画像設定セット
		SetTextureSetting(a_texturetype);

		rect = a_rect;
		speed = movespeed;
		pos = a_pos;
		angle = a_angle;
		move.x = cosf(angle) * speed;
		move.y = sinf(angle) * speed;
		color = { 1,1,1,1 };
		alive = true;
		scale = { 1,1 };

		//アニメーション用
		anim = { 0,0 };
		animmaxnum = a_animmaxnum;

		scalemat = Math::Matrix::CreateScale(scale.x, scale.y, 1);
		rotatemat = Math::Matrix::CreateRotationZ(angle + texangle);
		transmat = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
		mat = scalemat * rotatemat * transmat;

		//半径
		m_halfsize = rect * scale / 2;
		m_radius = rect.x * scale.x / 2;

		if (auto hm = m_hitmanager.lock())
		{
			hm->SetEnemyShot(shared_from_this());
		}

		break;
	case ShotType::CopyShot:
		//画像設定セット
		SetTextureSetting(a_texturetype);

		rect = a_rect;
		speed = movespeed;
		pos = a_pos;
		angle = a_angle;
		move.x = cosf(angle) * speed;
		move.y = sinf(angle) * speed;
		color = { 1,1,1,1 };
		alive = true;
		scale = { 1,1 };

		//アニメーション用
		anim = { 0,0 };
		animmaxnum = a_animmaxnum;

		scalemat = Math::Matrix::CreateScale(scale.x, scale.y, 1);
		rotatemat = Math::Matrix::CreateRotationZ(angle + texangle);
		transmat = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
		mat = scalemat * rotatemat * transmat;

		//半径
		m_halfsize = rect * scale / 2;
		m_radius = rect.x * scale.x / 2;

		if (auto hm = m_hitmanager.lock())
		{
			hm->SetCopyShot(shared_from_this());
		}

		break;
	case ShotType::ShotNum:
		break;
	default:
		break;
	}
}


void C_Shot::Update()
{
	//空じゃなければ
	if (!m_normalshot.empty())
	{
		NormalShotUpdate();
	}
}

void C_Shot::Draw()
{
	//空じゃなければ
	if (!m_normalshot.empty())
	{
		NormalShotDraw();
	}
}

void C_Shot::NormalShotInit(ShotType shottype, ShotTextureType a_texturetype, Math::Vector2 a_animmaxnum, Math::Vector2 a_rect, Math::Vector2 a_pos, Math::Vector2 target, int movespeed)
{
	m_normalshot.emplace_back(std::make_shared<Shot>());
	m_normalshot.back()->SetHitManager(m_hitmanager);
	m_normalshot.back()->SetTexture(SetTextureType(a_texturetype));
	m_normalshot.back()->Init(shottype, a_texturetype,a_animmaxnum, a_rect, a_pos, target,movespeed);
}

void C_Shot::NormalShotInit(ShotType shottype, ShotTextureType a_texturetype, Math::Vector2 a_animmaxnum, Math::Vector2 a_rect, Math::Vector2 a_pos, float a_angle, int movespeed)
{
	m_normalshot.emplace_back(std::make_shared<Shot>());
	m_normalshot.back()->SetHitManager(m_hitmanager);
	m_normalshot.back()->SetTexture(SetTextureType(a_texturetype));
	m_normalshot.back()->Init(shottype, a_texturetype, a_animmaxnum, a_rect, a_pos, a_angle,movespeed);

}

void C_Shot::NormalShotUpdate()
{
	for (int i = 0; i < m_normalshot.size(); i++)
	{
		m_normalshot[i]->pos += m_normalshot[i]->move;

		m_normalshot[i]->anim.x += 0.1f;
		//マックス以上になったら,4コマなら4
		if (m_normalshot[i]->anim.x >= m_normalshot[i]->animmaxnum.x)
		{
			m_normalshot[i]->anim.x = 0;
			if (m_normalshot[i]->animmaxnum.y != 0)
			{
				m_normalshot[i]->anim.y++;
			}

		}
		if (m_normalshot[i]->animmaxnum.y != 0)
		{
			if (m_normalshot[i]->anim.y > m_normalshot[i]->animmaxnum.y)
			{
				m_normalshot[i]->anim = { 0,0 };
			}
		}

		m_normalshot[i]->scalemat = Math::Matrix::CreateScale(m_normalshot[i]->scale.x, m_normalshot[i]->scale.y, 1);
		m_normalshot[i]->rotatemat = Math::Matrix::CreateRotationZ(m_normalshot[i]->angle + m_normalshot[i]->texangle);
		m_normalshot[i]->transmat = Math::Matrix::CreateTranslation(m_normalshot[i]->pos.x, m_normalshot[i]->pos.y, 0);
		m_normalshot[i]->mat = m_normalshot[i]->scalemat * m_normalshot[i]->rotatemat * m_normalshot[i]->transmat;
	}


	//削除
	for (int i = 0; i < m_normalshot.size(); )
	{
		if (COMMONAPI.OutOfScreenPlusMargin(m_normalshot[i]->pos, m_normalshot[i]->rect / 2))
		{
			m_normalshot[i]->alive = false;
		}

		if (!m_normalshot[i]->alive )
		{
			m_normalshot.erase(m_normalshot.begin() + i);
			continue;
		}
		else
		{
			i++;
		}
	}
}

void C_Shot::NormalShotDraw()
{
	for (int i = 0; i < m_normalshot.size(); i++)
	{
		//発生中なら
		if (m_normalshot[i]->alive)
		{
			SHADER.m_spriteShader.SetMatrix(m_normalshot[i]->mat);
			SHADER.m_spriteShader.DrawTex(m_normalshot[i]->tex, 0, 0, 
				&Math::Rectangle((int)m_normalshot[i]->anim.x*m_normalshot[i]->rect.x, (int)m_normalshot[i]->anim.y * m_normalshot[i]->rect.y, m_normalshot[i]->rect.x, m_normalshot[i]->rect.y),
				&m_normalshot[i]->color);
		}
	}
}

KdTexture* C_Shot::SetTextureType(ShotTextureType type)
{
	switch (type)
	{
	case ShotTextureType::Bolt:
		return &m_bolttex;
	case ShotTextureType::Pulse:
		return &m_pulsetex;
	case ShotTextureType::Copy:
		return &m_copyshottex;
	default:
		break;
	}
}


void Shot::SetTextureSetting(ShotTextureType type)
{
	TextureAngle angle= TextureAngle::Left;

	//元画像が何か、画像と元画像角度をセットする
	switch (type)
	{
	case ShotTextureType::Bolt: 
		angle = TextureAngle::Left;
		break;
	case ShotTextureType::Pulse:
		angle = TextureAngle::Right;
		break;
	case ShotTextureType::Copy:
		angle = TextureAngle::Right;
		break;
	default:
		break;
	}

	//画像向き調整
	texangle = COMMONAPI.GetTextureAngleAdjustment(angle);
}
