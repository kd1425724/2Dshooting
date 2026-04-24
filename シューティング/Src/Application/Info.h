#pragma once

class C_Info
{
public:
	~C_Info(){}

	//画面設定//

	static const int ScrWidth = 1280;
	static const int ScrHeight = 720;

	//HUDエリア設定
	static const int HUDAreaWidth = 1280;
	static const int HUDAreaHeight = 120;

	//プレイ画面設定
	static const int PlayAreaWidth = 1280;
	static const int PlayAreaHeight = ScrHeight-HUDAreaHeight;

	////////////


	//プレイヤー情報//
	
	//読み込み
	void PlayerInfoLoad();
	//書き込み
	void PlayerInfoSave();
	//HP強化幅保存用
	int PlayerHpEnhancement = 1;
	//Power強化幅保存用
	int PlayerPowerEnhancement = 5;
	//Speed強化幅保存用
	int PlayerSpeedEnhancement = 2;

	//////////////////



private:

//シングルトン
private:
	
	C_Info() {}

public:
	

	static C_Info& GetInstans()
	{
		static C_Info instans;
		return instans;
	}
};

//情報まとめ
#define INFO C_Info::GetInstans()

