#pragma once
#include <functional>
using namespace std;

struct SpriteItem
{
    Math::Vector2 pos = { 0, 0 };
    Math::Rectangle rect = { 0, 0, 0, 0 };
    Math::Vector2 radius = { 0, 0 };
    Math::Vector2 scale = { 1, 1 };
    Math::Color color = {};

    const KdTexture* tex = nullptr;

    Math::Matrix transMat = Math::Matrix::Identity;
    Math::Matrix scaleMat = Math::Matrix::Identity;
    Math::Matrix mat = Math::Matrix::Identity;

    //// ÉtÉåÅ[ÉÄóp
    //Math::Vector2 framescale = { 1, 1 };
    //Math::Matrix framescalemat = Math::Matrix::Identity;
    //Math::Matrix framemat = Math::Matrix::Identity;

    // è„Ç…èÊÇ¡ÇƒÇ¢ÇÈÇ©
    bool GetIsOnTop();

    // âΩÇÇ∑ÇÈÇ©
    function<void()> action = nullptr;
};

class C_ScenesUiBase
{
public:
    C_ScenesUiBase()
    {
    }

    virtual ~C_ScenesUiBase() { Release(); }

    virtual void Init();
    virtual void Update();
    virtual void Draw();

    // îwåióp
    virtual void BackGroundInit();
    virtual void BackGroundUpdate();
    virtual void BackGroundDraw();

    // ã§í îwåi
    void BlackBackInit();
    void BlackBackUpdate();
    void BlackBackDraw();

    void ClickableUi();
    void IsOnTopDraw();

    void CreateSpriteItemInit(
        Math::Vector2 pos,
        Math::Rectangle rect,
        Math::Vector2 scale,
        const KdTexture* tex,
        Math::Color color);

    void CreateSpriteItemUpdate();
    void CreateSpriteItemDraw();

    void SetAction(int index, function<void()> action)
    {
        m_SpriteItem[index].action = action;
    }

protected:
    virtual void Release() {}

    // ===== îwåi =====
    KdTexture m_backgroundtex;

    Math::Rectangle m_backgroundrect = { 0, 0, 0, 0 };
    Math::Matrix m_backgroundscalemat = Math::Matrix::Identity;
    Math::Matrix m_backgroundtransmat = Math::Matrix::Identity;
    Math::Matrix m_backgroundmat = Math::Matrix::Identity;

    Math::Vector2 m_backgroundpos = { 0, 0 };
    Math::Vector2 m_backgroundscale = { 1, 1 };
    Math::Vector2 m_backgroundanim = { 0, 0 };
    Math::Color m_backgroundcolor = {};

    // ===== UIÉXÉvÉâÉCÉg =====
    std::vector<SpriteItem> m_SpriteItem;

private:
    // ===== ã§í îwåi =====
    Math::Vector2 m_blackbackpos = { 0, 0 };
    Math::Matrix m_blackbackmat = Math::Matrix::Identity;
    Math::Color m_blackbackcolor = {};
};