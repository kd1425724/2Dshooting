#pragma once
#include"../HitBase.h"

class C_Player;

class C_PlayerHit : public C_HitBase
{
public:
	C_PlayerHit();
	~C_PlayerHit()override;

	void Init() override;
	void Update() override;

	void OnHit(std::shared_ptr<C_HitBase> other) override;

	// Š—LÒ
	void SetOwner(std::shared_ptr<C_Player> player) { m_player = player; }

private:
	std::shared_ptr<C_Player> m_player;
};