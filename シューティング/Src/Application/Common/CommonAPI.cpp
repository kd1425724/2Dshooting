#include "CommonAPI.h"
#include"Application/Info.h"

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

	switch (angle)
	{
	case TextureAngle::Right:
		return 0.0f;

	case TextureAngle::Top:
		return -DirectX::XM_PIDIV2;   // -90度

	case TextureAngle::Left:
		return DirectX::XM_PI;        // 180度

	case TextureAngle::Bottom:
		return DirectX::XM_PIDIV2;    // +90度

	default:
		return 0.0f;
	}
	

}
