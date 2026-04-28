#pragma once
#include"../../HitBase.h"

class C_EnemyMoveBase;

class C_EnemyHit : public C_HitBase
{
public:
	C_EnemyHit();
	~C_EnemyHit()override;

	void Init() override;
	void Update() override;

	void OnHit(std::shared_ptr<C_HitBase> other) override;

	// Š—LÒ
	void SetOwner(std::shared_ptr<C_EnemyMoveBase> enemy) { m_enemy= enemy; }

private:
	std::shared_ptr<C_EnemyMoveBase> m_enemy;
};