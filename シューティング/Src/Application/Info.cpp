#include "Info.h"

void C_Info::Release()
{

}

void C_Info::Save()
{
	//プレイヤー情報セーブ
	PlayerInfoSave();
	//スコアアタック・タイムアタックユーザースター情報セーブ
	UserStarInfoSave();
}

void C_Info::Init()
{
	//プレイヤー情報ロード
	PlayerInfoLoad();
	//スコアアタック・タイムアタックユーザースター情報ロード
	UserStarInfoLoad();
}

void C_Info::UserStarInfoLoad()
{
	FILE* fp;
	if (fopen_s(&fp, "Data/UserData/UserStarData.csv", "r") == 0)
	{
		char dummy[255];
		//fgets(dummy, 255, fp);				//1行飛ばす
		fscanf_s(fp, "%*[^,],%d", &ScoreAttackUserStarInfo);
		fscanf_s(fp, "%*[^,],%d", &TimeAttackUserStarInfo);
		fclose(fp);
	}
}
void C_Info::UserStarInfoSave()
{
	FILE* fp;
	if (fopen_s(&fp, "Data/UserData/UserStarData.csv", "w") == 0)
	{
		fprintf(fp, "UserStar情報,値\n");
		fprintf(fp, "ScoreAttackUserStar情報,%d\nTimeAttackUserStar情報,%d\n", ScoreAttackUserStarInfo, TimeAttackUserStarInfo);
		fclose(fp);
	}
}

void C_Info::PlayerInfoLoad()
{
}

void C_Info::PlayerInfoSave()
{
	FILE* fp;

	if (fopen_s(&fp, "Data/PlayerData/PlayerEnhancementData.csv", "w") == 0)
	{
		fprintf(fp, "プレイヤー情報,値\n");
		fprintf(fp, "プレイヤーHp強化値,%d\nプレイヤーPower強化値,%d\nプレイヤーSpeed強化値,%d\n", PlayerHpEnhancement, PlayerPowerEnhancement, PlayerSpeedEnhancement);

		fclose(fp);
	}
}

