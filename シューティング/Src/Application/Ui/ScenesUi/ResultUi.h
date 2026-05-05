#pragma once
#include"Application/Ui/ScenesUi/ScenesUiBase.h"

class C_ResultUi :public C_ScenesUiBase
{
public:
	C_ResultUi() {}
	~C_ResultUi()override { Release(); }

	void Init()override;
	void Update()override;
	void Draw()override;

	//îwåióp
	void BackGroundInit()override;
	void BackGroundUpdate()override;
	void BackGroundDraw()override;

private:
	
	void Release()override;

};
