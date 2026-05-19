#pragma once
#include"../EffectBase.h"

class C_ScanCompleteText : public C_EffectBase
{
public:

	C_ScanCompleteText() {}
	~C_ScanCompleteText() override { Release(); }

	void Init(Math::Vector2 pos) override;
	void Update() override;
	void Draw() override;

private:

	void Release() override;

}