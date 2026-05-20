#include "SceneManager.h"
#include"Application/Scenes/Title/Title.h"
#include"StageSelect/StageSelect.h"
#include"Application/Scenes/Game/Game.h"
#include"Application/Scenes/Game2/Game2.h"
#include"GamePause/GamePause.h"
#include"Application/Scenes/Result/Result.h"
#include"Application/Ui/Feed.h"
#include"../Effect/EffectManager.h"
#include"../Sound/Sound.h"

void C_SceneManager::Release()
{
    scenes.clear();
    m_scoredata.reset();
    m_score = 0;
}

void C_SceneManager::Init()
{
	m_oldscenetype = SceneType::Title;
	m_nowscenetype = SceneType::Title;
    scenes.push_back(CreateScene(m_nowscenetype));
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

            //前のシーンのタイプを保存
            m_oldscenetype = m_nowscenetype;

            //今のシーンのタイプを保存
            m_nowscenetype = type;

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
            auto scene = CreateScene(m_nowscenetype);

            //存在するか
            if (scene != nullptr)
            {
                //タイトルに戻る時
                if (m_nowscenetype == SceneType::Title)
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

    ////前のシーンのタイプを保存
    //m_oldscenetype = m_nowscenetype;

    ////今のシーンのタイプを保存
    //m_nowscenetype = type;

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
         SOUND.StopSE();
         SOUND.SetPlayBGM(BGMType::TitleBGM);
        return make_shared<C_Title>();

    case SceneType::StageSelect:
        EFFECTMANAGER.Release();
        SOUND.StopSE();
		return make_shared<C_StageSelect>();

    case SceneType::Game:
        SOUND.StopSE();
        SOUND.SetPlayBGM(BGMType::GameBGM);
        return make_shared<C_Game>();
    case SceneType::Game2:
        SOUND.StopSE();
        SOUND.SetPlayBGM(BGMType::GameBGM);
        return make_shared<C_Game2>();

    case SceneType::GamePause:
        return make_shared<C_GamePause>();

    case SceneType::Result:
        SOUND.StopSE();
        SOUND.SetPlayBGM(BGMType::ResultBGM);
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
