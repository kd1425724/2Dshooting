#pragma once

enum class PlayerKeyType
{
	Top,			//上移動
	Bottom,			//下移動
	Left,			//左移動
	Right,			//右移動
	NormalShot,		//通常攻撃
	Skill,			//スキル
	PlayerKeyNum	//数
};

enum class PlayerKeyDefaultType
{
	Top			= 'W',			//上移動
	Bottom		= 'S',			//下移動
	Left		= 'A',			//左移動
	Right		= 'D',			//右移動
	NormalShot	= VK_LBUTTON,	//通常攻撃
	Skill		= 'E',			//スキル
};

class C_Input
{
public:

	~C_Input();

	void Init();
	void Update(HWND hwnd);
	void Draw();

	//プレイヤーキーロード
	void PlayerKeyLoad();
	//セーブ
	void PlayerKeySave();

	//アドレス渡しでマウス座標取得
	void GetMousePos(POINT* mousePos,HWND hwnd);

	//マウス座標取得用
	POINT GetMousePos() { return mouse; }

	//クリックフラグ取得用
	bool GetClickFlg() { return m_mouseclickflg; }

	//プレイヤーキー取得用
	SHORT GetPlayerKey(PlayerKeyType playerkeytype) { return GetAsyncKeyState(m_playerkey[(int)playerkeytype]) & 0x8000; }
	
	bool GetPlayerKeyFlg(PlayerKeyType playerkeytype) { return m_playerkeyflg[(int)playerkeytype]; }
	
	//プレイヤーデフォルトキーセット用
	void PlayerDefaultKeySet();

private:

	//マウス座標
	POINT mouse;

	//クリックフラグ
	bool m_mouseclickflg;
	
	//プレイヤーキー
	int m_playerkey[(int)PlayerKeyType::PlayerKeyNum];

	int m_playerkeyflg[(int)PlayerKeyType::PlayerKeyNum];

	 
//シングルトン
private:
	
	C_Input() {}
public:

	static C_Input& GetInstans()
	{
		static C_Input instans;
		return instans;
	}
};

#define Input C_Input::GetInstans()
