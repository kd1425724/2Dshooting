#pragma once
#include"../SceneBase.h"

class C_StageSelectUi;

class C_StageSelect :public C_SceneBase
{
public:
	C_StageSelect(){}
    ~C_StageSelect()override { Release(); }

    void Init() override;
    void Update() override;
    void Draw() override;

private:
    void Release() override;

    std::shared_ptr<C_StageSelectUi> m_stageselectui = nullptr;
};