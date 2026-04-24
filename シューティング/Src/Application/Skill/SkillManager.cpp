#include"SkillManager.h"
#include"SkillBase.h"
#include"EnemyGenetate/EnemyGenerate.h"
#include"../Input/Input.h"

void C_SkillManager::Init() 
{
	m_playerskills = std::make_shared<C_SkillBase>();

	m_playerskills->Init();
}
void C_SkillManager::Update() 
{
	m_playerskills->Update();

	//ƒXƒLƒ‹”­“®
	if (Input.GetPlayerKey(PlayerKeyType::Skill))
	{
		m_playerskills->SkillActivate();
	}

}
void C_SkillManager::Draw() 
{
	m_playerskills->Draw();
}

void C_SkillManager::SetPlayerSkill(SkillType skilltype)
{
	switch (skilltype)
	{
	case SkillType::CopyShot:
		break;
	case SkillType::EnemyGenerate:
		m_playerskills = std::make_shared<C_EnemyGenerate>();
		m_playerskills->SetEnemyMagager(m_manager);
		break;
	case SkillType::Barrier:
		break;
	default:
		break;
	}
}
