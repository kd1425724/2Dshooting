#pragma once

class C_EnemyManager;
class C_EnemyMoveBase;
class C_Player;

enum class UseType
{
	Player,
	Enemy
};

class C_SkillBase
{
public:
	C_SkillBase() {
		m_usetype = UseType::Player;
		m_player = nullptr;
	}
	virtual ~C_SkillBase(){}

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	//スキル発動用
	virtual void SkillActivate(){}
	virtual void EnemySkillActivate(){}

	void SetUseType(UseType type) { m_usetype = type; }

	//敵管理取得用
	virtual void SetEnemyMagager(std::shared_ptr<C_EnemyManager> manager) {}
	//敵取得用
	virtual void SetEnemy(std::shared_ptr<C_EnemyMoveBase> enemybase) {}

	//プレイヤーインスタンス取得用
	void SetPlayer(std::shared_ptr<C_Player> player) { m_player = player; }

	//画像設定
	virtual void SetTexture(std::shared_ptr<KdTexture> tex){}

	//画像描画順調整
	virtual bool IsTopDraw() = 0;

protected:
	
	UseType m_usetype;

	std::shared_ptr<C_Player> m_player;



private:



};
