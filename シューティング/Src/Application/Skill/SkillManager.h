#pragma once

enum class SkillType
{
	CopyShot,		//コピー
	EnemyGenerate,	//敵生成
	Barrier,		//バリア
};

class C_SkillBase;
class C_EnemyManager;

class C_SkillManager
{
public:
	C_SkillManager(){}
	~C_SkillManager(){}

	void Init();
	void Update();
	void Draw();

	//プレイヤースキルセット用
	void SetPlayerSkill(SkillType skilltype);

	//敵管理取得用
	void SetEnemyManager(std::shared_ptr<C_EnemyManager> manager) { m_manager = manager; }

private:

	std::shared_ptr<C_SkillBase> m_playerskills = nullptr;

	std::shared_ptr<C_EnemyManager> m_manager;

};
