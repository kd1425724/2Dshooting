#pragma once

class C_SceneBase
{
public:
	C_SceneBase(){}
	~C_SceneBase(){}

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	//‰æ‘œƒ[ƒh
	virtual void TextureLoad();

protected:

private:

};
