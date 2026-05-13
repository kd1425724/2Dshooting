#pragma once
#include "Application/Scenes/SceneBase.h"

class C_GamePauseUi;

class C_GamePause : public C_SceneBase, public std::enable_shared_from_this<C_GamePause>
{
public:
    C_GamePause() {}
    ~C_GamePause() override { Release(); }

    void Init() override;
    void Update() override;
    void Draw() override;

private:
    void Release() override;

    std::shared_ptr<C_GamePauseUi> m_gamepauseui = nullptr;
};