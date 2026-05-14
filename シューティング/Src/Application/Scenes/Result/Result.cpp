#include "Result.h"
#include"../SceneManager.h"
#include"../../Ui/ScenesUi/ResultUi.h"
#include"../../Common/CommonAPI.h"
#include"../../Effect/EffectManager.h"
#include"../../Input/Input.h"
void C_Result::Init()
{


	m_resultui = std::make_shared<C_ResultUi>();

	//オーナーセット
	m_resultui->SetOwner(shared_from_this());

	m_resultui->Init();

	
}

void C_Result::Update()
{
	EFFECTMANAGER.Update();

	m_resultui->Update();

	if (Input.GetUserKey(UserKeyType::ENTER) && !Input.GetUserKeyFlg(UserKeyType::ENTER))
	{
		SCENEMANAGER.push(SceneType::Title, true);
	}
}

void C_Result::Draw()
{
	EFFECTMANAGER.Draw();

	m_resultui->Draw();
}

void C_Result::Release()
{
	m_resultui.reset();
}
