#pragma once
#include"Application/Scenes/SceneBase.h"

class C_ResultUi;

class C_Result:public C_SceneBase
{
public:
	C_Result(){}
	~C_Result()override{}

	void Init()override;
	void Update()override;
	void Draw()override;

private:

	
	void Release()override;

	std::shared_ptr<C_ResultUi> m_resultui;

};
