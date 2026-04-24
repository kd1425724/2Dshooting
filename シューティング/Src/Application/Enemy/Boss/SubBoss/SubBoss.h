#pragma once
#include"Application/Enemy/Boss/BossBase.h"

class C_SubBoss :public C_BossBase
{
public:
	C_SubBoss() {}
	~C_SubBoss() { Release(); }

	//G‹›“G—p‚È‚Ì‚Åg‚í‚È‚¢
	void Init(PosPattern pospattern, MovePattern movepattern, std::shared_ptr<C_Player> player, int i)override {}

	void Init(Math::Vector2 pos)		override;
	void Update()	override;
	void Draw()		override;


private:

	void Release()	override;

	//~‚Ü‚éÀ•W
	Math::Vector2 m_stoppos;

};
