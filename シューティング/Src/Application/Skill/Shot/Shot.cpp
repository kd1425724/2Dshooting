#include "Shot.h"
#include"Application/Common/CommonAPI.h"

C_Shot::C_Shot()
{
	
}


void C_Shot::ShotManager(ShotType a_type,ShotTextureType a_texturetype, Math::Vector2 a_animmaxnum,Math::Vector2 a_rect, Math::Vector2 a_pos, Math::Vector2 target, int movespeed)
{
	SetTexture(a_texturetype);

	switch (a_type)
	{
	case ShotType::NormalShot:
		//初期化
		NormalShotInit(a_texturetype,a_animmaxnum, a_rect, a_pos, target,movespeed);
		break;
	case ShotType::ShotNum:
		break;
	default:
		break;
	}
}

void C_Shot::ShotManager(ShotType a_type, ShotTextureType a_texturetype, Math::Vector2 a_animmaxnum, Math::Vector2 a_rect, Math::Vector2 a_pos, float a_angle, int movespeed)
{
	SetTexture(a_texturetype);

	switch (a_type)
	{
	case ShotType::NormalShot:
		//初期化
		NormalShotInit(a_texturetype, a_animmaxnum, a_rect, a_pos, a_angle,movespeed);
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
		rotatemat = Math::Matrix::CreateRotationZ(angle+texangle);
		transmat = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
		mat = scalemat * rotatemat * transmat;

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

void C_Shot::SetTexture(ShotTextureType type)
{
	//元画像が何か、画像と元画像角度をセットする
	switch (type)
	{
	case ShotTextureType::Bolt:
		m_tex.Load("Texture/Skill/Attack/Bolt.png");
		break;
	default:
		break;
	}
}

void C_Shot::NormalShotInit(ShotTextureType a_texturetype, Math::Vector2 a_animmaxnum, Math::Vector2 a_rect, Math::Vector2 a_pos, Math::Vector2 target, int movespeed)
{
	m_normalshot.emplace_back(std::make_shared<Shot>());
	m_normalshot.back()->Init(ShotType::NormalShot, a_texturetype,a_animmaxnum, a_rect, a_pos, target,movespeed);
}

void C_Shot::NormalShotInit(ShotTextureType a_texturetype, Math::Vector2 a_animmaxnum, Math::Vector2 a_rect, Math::Vector2 a_pos, float a_angle, int movespeed)
{
	m_normalshot.emplace_back(std::make_shared<Shot>());
	m_normalshot.back()->Init(ShotType::NormalShot, a_texturetype, a_animmaxnum, a_rect, a_pos, a_angle,movespeed);

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


		//範囲外に出たら消去
		if (COMMONAPI.OutOfPlayAreaPlusMargin(m_normalshot[i]->pos, m_normalshot[i]->rect / 2))
		{
			m_normalshot.erase(m_normalshot.begin() + i);

			i--;
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
			SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, 
				&Math::Rectangle((int)m_normalshot[i]->anim.x*m_normalshot[i]->rect.x, (int)m_normalshot[i]->anim.y * m_normalshot[i]->rect.y, m_normalshot[i]->rect.x, m_normalshot[i]->rect.y),
				&m_normalshot[i]->color);
		}
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
	default:
		break;
	}

	//画像向き調整
	texangle = COMMONAPI.GetTextureAngleAdjustment(angle);
}
