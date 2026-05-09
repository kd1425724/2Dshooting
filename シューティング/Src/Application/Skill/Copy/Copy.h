#pragma once
#include "Application/Skill/SkillBase.h"

class C_Shot;
class C_HitManager;

class C_Copy : public C_SkillBase
{
public:
    C_Copy() {}
    ~C_Copy() override {}

    void Init() override;
    void Update() override;
    void Draw() override;

    // ƒXƒLƒ‹”­“®
    void SkillActivate() override;
    void EnemySkillActivate() override;

    // •`‰æ‡
    bool IsTopDraw() override { return false; }

    void SetHitManager(std::shared_ptr<C_HitManager> hitmanager) override
    {
        m_hitmanager = hitmanager;
    }

private:
    std::shared_ptr<C_Shot> m_shot = nullptr;
    std::weak_ptr<C_HitManager> m_hitmanager;

    int m_time = 0;
};