#include "SceneManager.h"
#include"Application/Scenes/Title/Title.h"
#include"Application/Scenes/Game/Game.h"
#include"GamePause/GamePause.h"
#include"Application/Scenes/Result/Result.h"
#include"Application/Ui/Feed.h"
#include"../Effect/EffectManager.h"

C_SceneManager::~C_SceneManager()
{
}

void C_SceneManager::Init()
{
    scenes.push_back(CreateScene(SceneType::Title));
    scenes.back()->Init();
}

void C_SceneManager::Update()
{
    //空じゃなければ
    if (!scenes.empty())
    {
        if (FEED.GetFeedState() == FeedOut)return;

        scenes.back()->Update();
    }
}
void C_SceneManager::Draw()
{
    //空じゃなければ
    if (!scenes.empty())
    {
        for (auto& s : scenes)
        {
            s->Draw();
        }
       
    }
}

void C_SceneManager::ImGui()
{
    //空じゃなければ
    if (!scenes.empty())
    {
        scenes.back()->ImGui();
    }

  
}

void C_SceneManager::push(SceneType type, bool popflg, bool Allpopflg)
{
    FEED.FeedOutInit(30, [this, type, popflg,Allpopflg]()
        {
            //popフラグがtrueなら今のシーンを消す
            if (popflg)
            {
                if (Allpopflg)
                {
                    //全部削除
                    scenes.clear();
                }
                else
                {
                    if (!scenes.empty())
                    {
                        scenes.pop_back();
                    }
                }
            }


            //指定したシーンを作りそれを格納する
            auto scene = CreateScene(type);

            //存在するか
            if (scene != nullptr)
            {
                //タイトルに戻る時
                if (type == SceneType::Title)
                {
                    //スコアリセット
                    ResetScoreData();
                }

                //シーン初期化
                scene->Init();
                //scenesに作ったシーンを移動
                scenes.push_back(scene);

                FEED.FeedInInit(30);
            }
        });
}

void C_SceneManager::NoFeedpush(SceneType type, bool popflg, bool Allpopflg)
{
    //popフラグがtrueなら今のシーンを消す
    if (popflg)
    {
        if (Allpopflg)
        {
            //全部削除
            while (!scenes.empty())
            {
                scenes.pop_back();
            }
        }
        else
        {
            if (!scenes.empty())
            {
                scenes.pop_back();
            }
        }
    }

    //指定したシーンを作りそれを格納する
    auto scene = CreateScene(type);

    //存在するか
    if (scene != nullptr)
    {
        //タイトルに戻る時
        if (type == SceneType::Title)
        {
            //スコアリセット
            ResetScoreData();
        }

        //シーン初期化
        scene->Init();
        //scenesに作ったシーンを移動
        scenes.push_back(scene);
    }
}

void C_SceneManager::pop()
{
    //空じゃなければ
    if (!scenes.empty())
    {
        scenes.pop_back();
    }
}

std::shared_ptr<C_SceneBase> C_SceneManager::CreateScene(SceneType type)
{
    switch (type) {
    case SceneType::Title:
        EFFECTMANAGER.Release();
        return make_shared<C_Title>();

    case SceneType::Game:
        return make_shared<C_Game>();

    case SceneType::GamePause:
        return make_shared<C_GamePause>();

    case SceneType::Result:
        return make_shared<C_Result>();

    default:
        return nullptr;
    }
}

void C_SceneManager::SetScore(int value)
{
    if (value > 0)
    {
        EFFECTMANAGER.ScoreEffect(value);
    }
    m_score += value;
}
