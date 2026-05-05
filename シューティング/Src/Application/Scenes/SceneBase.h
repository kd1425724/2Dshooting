#pragma once

class C_SceneBase
{
public:
	C_SceneBase(){}
	virtual ~C_SceneBase(){}

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	virtual void ImGui(){}

protected:

	//ƒŠƒŠ[ƒX
	virtual void Release();

private:

};
