#pragma once

class C_SceneBase
{
public:
	C_SceneBase(){}
	~C_SceneBase(){}

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	

protected:

	//画像ロード
	virtual void TextureLoad();

	//リリース
	virtual void Release();

private:

};
