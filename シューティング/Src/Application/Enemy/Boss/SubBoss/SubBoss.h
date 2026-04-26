#pragma once
#include"Application/Enemy/Boss/BossBase.h"

class C_SubBoss :public C_BossBase
{
public:
	C_SubBoss() {}
	~C_SubBoss() { Release(); }

	void Init(Math::Vector2 pos)		override;
	void Update()	override;
	void Draw()		override;


private:

	void Release()	override;

	//é~Ç‹ÇÈç¿ïW
	Math::Vector2 m_stoppos;

};
