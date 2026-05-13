#pragma once
#include "Application/Scenes/SceneBase.h"

class C_TitleUi;

class C_Title : public C_SceneBase
{
public:
    C_Title() {}
    ~C_Title() override { Release(); }

    void Init() override;
    void Update() override;
    void Draw() override;

private:
    void Release() override;

    // ===== UI =====
    std::shared_ptr<C_TitleUi> m_titleui = nullptr;

    // ===== テクスチャ =====
    std::shared_ptr<KdTexture> m_starttex = nullptr;
};