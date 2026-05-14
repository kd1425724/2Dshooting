#pragma once

enum class PlayerKeyType
{
    Top,
    Bottom,
    Left,
    Right,
    NormalShot,
    Skill,
    PlayerKeyNum
};

enum class PlayerKeyDefaultType
{
    Top = VK_UP,
    Bottom = VK_DOWN,
    Left = VK_LEFT,
    Right = VK_RIGHT,
    NormalShot = VK_SPACE,
    Skill = 'E',
};

enum class UserKeyType
{
    Top ,
    Bottom ,
    Left ,
    Right,
    ENTER ,
    ESCAPE,
    UserKeyNum
};
enum class UserKeyDefaultType
{
    Top = VK_UP,
    Bottom = VK_DOWN,
    Left = VK_LEFT,
    Right = VK_RIGHT,
    ENTER = VK_RETURN,
    ESCAPE=VK_ESCAPE,
};

enum class DebugKeyType
{
    Pkey,   //レーザーに変更
    Okey,   //バリアーに変更
    Ikey,   //敵生成に変更
    Ukey,   //リザルトへ
    ZEROKey,  //ボスを倒す
    NINEKey,  //プレイヤーの死亡フラグをONOFF
    DebugKeyNum,
};
enum class DebugKeyDefaultType
{
    Pkey='P',   //レーザーに変更
    Okey='O',   //バリアーに変更
    Ikey='I',   //敵生成に変更
    Ukey='U',   //次のシーンへ
    ZEROKey = '0',  //ボスを倒す
    NINEKey = '9',  //プレイヤーの死亡フラグをONOFF
};

class C_Input
{
public:
 
    void Init();
    void Update(HWND hwnd);
    void Draw();

    // プレイヤーキーロード
    void PlayerKeyLoad();

    // セーブ
    void PlayerKeySave();

    void GetMousePos(POINT* mousePos, HWND hwnd);

    POINT GetMousePos() { return mouse; }

    bool GetClickFlg() { return m_mouseclickflg; }

   /* SHORT GetPlayerKey(PlayerKeyType playerkeytype)
    {
        return GetAsyncKeyState(m_playerkey[(int)playerkeytype]) & 0x8000;
    }*/

    bool GetPlayerKey(PlayerKeyType playerkeytype)
    {
        return m_playerkeyflg[(int)playerkeytype];
    }

    bool GetPlayerKeyDown(PlayerKeyType type)
    {
        return m_playerkeyflg[(int)type] &&
            !m_oldplayerkeyflg[(int)type];
    }

    bool GetPlayerKeyUp(PlayerKeyType type)
    {
        return !m_playerkeyflg[(int)type] &&
            m_oldplayerkeyflg[(int)type];
    }

    SHORT GetUserKey(UserKeyType userkeytype)
    {
        return GetAsyncKeyState(m_userkey[(int)userkeytype]) & 0x8000;
    }

    bool GetUserKeyFlg(UserKeyType userkeytype)
    {
        return m_userkeyflg[(int)userkeytype];
    }

    SHORT GetDebugKey(DebugKeyType debugkeytype)
    {
        if (!m_olldebugkeyflg)return false;

        return GetAsyncKeyState(m_debugkey[(int)debugkeytype]) & 0x8000;
    }

    bool GetDebugKeyFlg(DebugKeyType debugkeytype)
    {
		if (!m_olldebugkeyflg)return false;

        return m_debugkeyflg[(int)debugkeytype];
    }

    void PlayerDefaultKeySet();
    void UserDefaultKeySet();
    void DebugDefaultKeySet();

private:

	void Release();

    // ===== マウス =====
    POINT mouse = { 0, 0 };
    bool m_mouseclickflg = false;

    // ===== キー =====
    int m_playerkey[(int)PlayerKeyType::PlayerKeyNum] = { 0 };
    bool m_playerkeyflg[(int)PlayerKeyType::PlayerKeyNum] = { false };
    bool m_oldplayerkeyflg[(int)PlayerKeyType::PlayerKeyNum] = { false };

    //ユーザーキー
    int m_userkey[(int)UserKeyType::UserKeyNum] = { 0 };
    bool m_userkeyflg[(int)UserKeyType::UserKeyNum] = { false };


    //デバッグキー
    int m_debugkey[(int)DebugKeyType::DebugKeyNum] = { 0 };
    bool m_debugkeyflg[(int)DebugKeyType::DebugKeyNum] = { false };

    //デバッグキーが使えるかどうかのフラグ
	bool m_olldebugkeyflg = false;

private:
    C_Input() {}
    ~C_Input(){ Release(); }

public:
    static C_Input& GetInstans()
    {
        static C_Input instans;
        return instans;
    }
};

#define Input C_Input::GetInstans()