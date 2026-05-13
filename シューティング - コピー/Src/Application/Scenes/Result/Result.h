#pragma once
#include "Application/Scenes/SceneBase.h"

class C_ResultUi;

class C_Result : public C_SceneBase, public std::enable_shared_from_this<C_Result>
{
public:
    C_Result() {}
    ~C_Result() override { Release(); }

    void Init() override;
    void Update() override;
    void Draw() override;

private:
    void Release() override;

    std::shared_ptr<C_ResultUi> m_resultui = nullptr;
};