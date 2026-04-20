#include "Input.h"
#include"Application/Info.h"

C_Input::~C_Input()
{
	PlayerKeySave();
}

void C_Input::Init()
{
	//マウス座標
	mouse = { 0,0 };

	//クリックフラグ
	m_mouseclickflg = false;

	//プレイヤーキーロード
	PlayerKeyLoad();
}
void C_Input::Update(HWND hwnd)
{
	//アドレス渡しでマウス座標取得
	GetMousePos(&mouse, hwnd);

	//クリックフラグ
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		m_mouseclickflg = true;
	}
	else
	{
		m_mouseclickflg = false;
	}
}
void C_Input::Draw()
{
}

void C_Input::PlayerKeyLoad()
{
	FILE* fp;

	if (fopen_s(&fp, "Data/PlayerData/PlayerKeyData.csv", "r") == 0)
	{
		char dummy[255];

		static const int num = (int)PlayerKeyType::PlayerKeyNum;

		int setkey[num] = {};

		fgets(dummy, 255, fp);				//1行飛ばす

		for (int i = 0; i < num; i++)
		{
			fscanf_s(fp, "%*[^,],%d", &setkey[i]);

			m_playerkey[i] = setkey[i];
		}

		fclose(fp);
	}
	else
	{
		//デバッグ用
		//OutputDebugStringA("CSV読み込み失敗\n");

		//デフォルトキーセット
		PlayerDefaultKeySet();
	}
}

void C_Input::PlayerKeySave()
{
	FILE* fp;

	//enum class PlayerKeyTypeと連動
	const char* name[(int)PlayerKeyType::PlayerKeyNum] = {
	"上移動",
	"下移動",
	"左移動",
	"右移動",
	"通常攻撃"
	};

	if (fopen_s(&fp, "Data/PlayerData/PlayerKeyData.csv", "w") == 0)
	{
		fprintf(fp, "プレイヤーキー,値\n");

		//プレイヤーキーを順に格納
		for (int i = 0; i < (int)PlayerKeyType::PlayerKeyNum; i++)
		{
			fprintf(fp, "%s,%d\n", name[i], m_playerkey[i]);
		}

		fclose(fp);
	}
}

void C_Input::PlayerDefaultKeySet()
{
	static const int num = (int)PlayerKeyType::PlayerKeyNum;

	int defaultkey[num] = { (int)PlayerKeyDefaultType::Top,
						(int)PlayerKeyDefaultType::Bottom,
						(int)PlayerKeyDefaultType::Left,
						(int)PlayerKeyDefaultType::Right,
						(int)PlayerKeyDefaultType::NormalShot};

	for (int i = 0; i < num; i++)
	{
		m_playerkey[i] = defaultkey[i];
	}
}

void C_Input::GetMousePos(POINT* mousePos, HWND hwnd)
{
	//ディスプレイ上のマウス座標を取得(PC画面の左上が(0,0))
	GetCursorPos(mousePos);

	//指定のウィンドウ基準のマウス座標に変換(実行画面の左上が(0,0))
	ScreenToClient(hwnd, mousePos);

	//マウスの座標系を実行ウィンドウの座標系(中心が 0 , 0)に補正
	mousePos->x -= INFO.ScrWidth / 2;
	mousePos->y -= INFO.ScrHeight / 2;
	mousePos->y *= -1;
}
