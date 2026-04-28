#pragma once
#include"../HitBase.h"

class C_Player;

class C_PlayerHit : public C_HitBase
{
public:
	C_PlayerHit();
	virtual ~C_PlayerHit();

	void Init() override;
	void Update() override;

	void OnHit(C_HitBase* other) override;

	// Š—LÒ
	void SetPlayer(C_Player* player) { m_player = player; }

private:
	C_Player* m_player;
};