#pragma once

class C_EnemyManager;
class C_Player;

enum class UseType
{
	Player,
	Enemy
};

class C_SkillBase
{
public:
	C_SkillBase(){}
	~C_SkillBase(){}

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	virtual void SkillActivate(){}

	void SetUseType(UseType type) { m_usetype = type; }

	//敵管理取得用
	virtual void SetEnemyMagager(std::shared_ptr<C_EnemyManager> manager) {}

	//プレイヤーインスタンス取得用
	virtual void SetPlayer(std::shared_ptr<C_Player> player) { m_player = player; }

protected:
	
	UseType m_usetype;

	std::shared_ptr<C_Player> m_player;

private:



};
