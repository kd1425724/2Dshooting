#include "CommonAPI.h"
#include"Application/Info.h"
#include"CommonTexture.h"

bool C_CommonAPI::OutOfScreen(Math::Vector2 pos, Math::Vector2 radius)
{
	//画面外に出たら
	if (pos.x + radius.x < -INFO.ScrWidth / 2 || pos.x - radius.x> INFO.ScrWidth / 2 ||
		pos.y + radius.y < -INFO.ScrHeight / 2 || pos.y - radius.y> INFO.ScrHeight / 2)
	{
		return true;
	}

	return false;
}

bool C_CommonAPI::OutOfPlayArea(Math::Vector2 pos, Math::Vector2 radius)
{
	//画面外に出たら
	if (pos.x + radius.x < -INFO.PlayAreaWidth / 2 || pos.x - radius.x > INFO.PlayAreaWidth / 2 ||
		pos.y + radius.y < -INFO.PlayAreaHeight / 2 - INFO.HUDAreaHeight || pos.y - radius.y > INFO.PlayAreaHeight / 2 - INFO.HUDAreaHeight)
	{
		return true;
	}

	return false;
}

bool C_CommonAPI::OutOfScreenPlusMargin(Math::Vector2 pos, Math::Vector2 radius)
{
	//画面外に出たら
	if (pos.x + radius.x + margin < -INFO.ScrWidth / 2 || pos.x - radius.x - margin> INFO.ScrWidth / 2 ||
		pos.y + radius.y + margin < -INFO.ScrHeight / 2 || pos.y - radius.y - margin > INFO.ScrHeight / 2)
	{
		return true;
	}

	return false;
}

bool C_CommonAPI::OutOfPlayAreaPlusMargin(Math::Vector2 pos, Math::Vector2 radius)
{
	//画面外に出たら
	if (pos.x + radius.x + margin < -INFO.PlayAreaWidth / 2 || pos.x - radius.x - margin > INFO.PlayAreaWidth / 2 ||
		pos.y + radius.y + margin < -INFO.PlayAreaHeight / 2-INFO.HUDAreaHeight || pos.y - radius.y - margin > INFO.PlayAreaHeight / 2 - INFO.HUDAreaHeight)
	{
		return true;
	}

	return false;
}

float C_CommonAPI::GetTextureAngleAdjustment(TextureAngle angle)
{
	switch (angle)
	{
	case TextureAngle::Top:
		return -DirectX::XM_PIDIV2;

	case TextureAngle::Bottom:
		return	DirectX::XM_PIDIV2;

	case TextureAngle::Left:
		return  DirectX::XM_PI;
		
	case TextureAngle::Right:
		return 0.0f;
		
	default:
		return 0.0f;
		break;
	}
}

void C_CommonAPI::NumDraw(int num, Math::Vector2 startpos, Math::Vector2 scale,int maxdigits)
{

	Math::Matrix s;
	Math::Matrix t;
	Math::Matrix mat;

	Math::Rectangle Srect = CommonTex.GetNumRect();

	//マイナスなら強制＋に
	if (num < 0)
	{
		num = abs(num);
	}

	

	// 0対策（0の場合は0のみ表示）
	if (num == 0)
	{
		s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
		t = Math::Matrix::CreateTranslation(startpos.x, startpos.y, 0);
		mat = s * t;

		Math::Rectangle rect = { num * Srect.width,Srect.y,Srect.width,Srect.height };

		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(&CommonTex.GetNumTex(), 0, 0,
			&rect);

		return;
	}

	std::vector<int> digits;

	//numが０になるまでループ
	while (num > 0)
	{
		digits.push_back(num % 10);
		num /= 10;
	}

	//最大桁数まで０代入
	while (digits.size() < maxdigits)
	{
		digits.push_back(0);
	}

	for (int i = 0; i < digits.size(); i++)
	{
		Math::Vector2 pos = startpos;
		pos.x -= Srect.width * scale.x * i;

		s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
		t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
		mat = s * t;

		Math::Rectangle rect = { digits[i] * Srect.width,Srect.y,Srect.width,Srect.height };

		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(&CommonTex.GetNumTex(), 0, 0,
			&rect);
	}
}
