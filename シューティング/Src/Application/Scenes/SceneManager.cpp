#include "SceneManager.h"
#include"Application/Scenes/Title/Title.h"
#include"Application/Scenes/Game/Game.h"
#include"Application/Scenes/Result/Result.h"
#include"Application/Ui/Feed.h"

C_SceneManager::~C_SceneManager()
{
}

void C_SceneManager::Init()
{
    scenes.push(CreateScene(SceneType::Game));
    scenes.top()->Init();
}

void C_SceneManager::Update()
{
    //空じゃなければ
    if (!scenes.empty())
    {
        scenes.top()->Update();
    }
}
void C_SceneManager::Draw()
{
    //空じゃなければ
    if (!scenes.empty())
    {
        scenes.top()->Draw();

        scenes.top()->Draw();
    }
}

void C_SceneManager::ImGui()
{
    //空じゃなければ
    if (!scenes.empty())
    {
        scenes.top()->ImGui();
    }
}

void C_SceneManager::push(SceneType type,bool popflg)
{
    FEED.FeedOutInit(30,[this,type,popflg]()
        {
            //popフラグがtrueなら今のシーンを消す
            if (popflg)
            {
                scenes.pop();
            }

            //指定したシーンを作りそれを格納する
            auto scene = CreateScene(type);

            //存在するか
            if (scene != nullptr)
            {
                //シーン初期化
                scene->Init();
                //scenesに作ったシーンを移動
                scenes.push(move(scene));

                FEED.FeedInInit(30);
            }
        });
   
}

void C_SceneManager::pop()
{
    //空じゃなければ
    if (!scenes.empty())
    {
        scenes.pop();
    }
}

std::shared_ptr<C_SceneBase> C_SceneManager::CreateScene(SceneType type)
{
    switch (type) {
    case SceneType::Title:
        return make_shared<C_Title>();

    case SceneType::Game:
        return make_shared<C_Game>();

    case SceneType::Result:
        return make_shared<C_Result>();

    default:
        return nullptr;
    }
}
