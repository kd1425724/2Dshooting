#pragma once

class C_CommonAPI
{
public:
	~C_CommonAPI(){}

	//画面外判定
	bool OutOfScreen(Math::Vector2 pos, Math::Vector2 radius);
	//プレイエリア内判定
	bool OutOfPlayArea(Math::Vector2 pos, Math::Vector2 radius);

private:

	//画面外判定余剰分
	const float margin = 100.0f;

	


//シングルトン
private:
	C_CommonAPI(){}

public:

	static C_CommonAPI& GetInstans()
	{
		static C_CommonAPI instans;
		return instans;
	}
};
//共通関数
#define COMMONAPI C_CommonAPI::GetInstans()
