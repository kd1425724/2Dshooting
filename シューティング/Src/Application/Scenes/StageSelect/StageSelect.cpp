#include"StageSelect.h"
#include"../../Ui/ScenesUi/StageSelectUi.h"

void C_StageSelect::Release()
{
	m_stageselectui.reset();
}

void C_StageSelect::Init()
{
	m_stageselectui = std::make_shared<C_StageSelectUi>();
	m_stageselectui->Init();
}

void C_StageSelect::Update()
{
	m_stageselectui->Update();
}

void C_StageSelect::Draw()
{
	m_stageselectui->Draw();
}

