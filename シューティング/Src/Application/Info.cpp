#include "Info.h"

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

