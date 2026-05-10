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

    SHORT GetPlayerKey(PlayerKeyType playerkeytype)
    {
        return GetAsyncKeyState(m_playerkey[(int)playerkeytype]) & 0x8000;
    }

    bool GetPlayerKeyFlg(PlayerKeyType playerkeytype)
    {
        return m_playerkeyflg[(int)playerkeytype];
    }

    SHORT GetUserKey(UserKeyType userkeytype)
    {
        return GetAsyncKeyState(m_userkey[(int)userkeytype]) & 0x8000;
    }

    bool GetUserKeyFlg(UserKeyType userkeytype)
    {
        return m_userkeyflg[(int)userkeytype];
    }

    void PlayerDefaultKeySet();
    void UserDefaultKeySet();

private:
    // ===== マウス =====
    POINT mouse = { 0, 0 };
    bool m_mouseclickflg = false;

    // ===== キー =====
    int m_playerkey[(int)PlayerKeyType::PlayerKeyNum] = { 0 };
    bool m_playerkeyflg[(int)PlayerKeyType::PlayerKeyNum] = { false };

    //ユーザーキー
    int m_userkey[(int)UserKeyType::UserKeyNum] = { 0 };
    bool m_userkeyflg[(int)UserKeyType::UserKeyNum] = { 0 };

private:
    C_Input() {}
    ~C_Input();

public:
    static C_Input& GetInstans()
    {
        static C_Input instans;
        return instans;
    }
};

#define Input C_Input::GetInstans()