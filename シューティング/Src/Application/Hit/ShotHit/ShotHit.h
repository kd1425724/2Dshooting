#pragma once
#include"../HitBase.h"

struct Shot;

class C_ShotHit : public C_HitBase
{
public:
	C_ShotHit();
	~C_ShotHit()override;

	void Init() override;
	void Update() override;

	void OnHit(std::shared_ptr<C_HitBase> other) override;

	// èäóLé“
	void SetOwner(std::shared_ptr<Shot> shot) { m_shot = shot; }

private:
	std::shared_ptr<Shot> m_shot;
};