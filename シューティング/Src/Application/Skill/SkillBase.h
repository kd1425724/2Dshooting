#pragma once

class C_EnemyManager;
class C_EnemyMoveBase;
class C_Player;
class C_HitManager;

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
	}
	virtual ~C_SkillBase(){}

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	//スキル発動用
	virtual void SkillActivate(){}
	virtual void EnemySkillActivate(){}
	virtual void EnemySkillActivate(Math::Vector2 scale){}

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

	bool GetAlive() { return m_alive; }

	//終了フラグ
	bool GetFinishedFlg() { return m_finished; }

	Math::Vector2 GetPos() { return m_pos; }

	//半径x,y別（矩形）
	Math::Vector2 GetSize() { return m_halfsize; }

	//半径（円判定）
	float GetRadius() { return m_radius; }

	virtual void SetHitManager(std::shared_ptr<C_HitManager> hitmanager){}

protected:
	
	UseType m_usetype;

	std::weak_ptr<C_Player> m_player;

	bool m_alive;

	Math::Vector2 m_pos;

	//半径
	float m_radius;
	Math::Vector2 m_halfsize;

	//終了フラグ
	bool m_finished=false;


private:



};
