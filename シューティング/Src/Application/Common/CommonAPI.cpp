#include "CommonAPI.h"
#include"Application/Info.h"

bool C_CommonAPI::OutOfScreen(Math::Vector2 pos, Math::Vector2 radius)
{
	//画面外に出たら
	if (pos.x + radius.x + margin < -INFO.ScrWidth / 2 || pos.x - radius.x - margin> INFO.ScrWidth / 2 ||
		pos.y + radius.y + margin < -INFO.ScrHeight / 2 || pos.y - radius.y - margin > INFO.ScrHeight / 2)
	{
		return true;
	}

	return false;
}

bool C_CommonAPI::OutOfPlayArea(Math::Vector2 pos, Math::Vector2 radius)
{
	//画面外に出たら
	if (pos.x + radius.x+margin < -INFO.PlayAreaWidth / 2 || pos.x - radius.x-margin > INFO.PlayAreaWidth / 2 ||
		pos.y + radius.y+margin < -INFO.PlayAreaHeight / 2 || pos.y - radius.y - margin > INFO.PlayAreaHeight / 2)
	{
		return true;
	}

	return false;
}
