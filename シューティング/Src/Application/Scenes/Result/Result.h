#pragma once
#include"Application/Scenes/SceneBase.h"

class C_Result:public C_SceneBase
{
public:
	C_Result(){}
	~C_Result(){}

	void Init()override;
	void Update()override;
	void Draw()override;

private:


	void TextureLoad()override;

	void Release()override;

};
