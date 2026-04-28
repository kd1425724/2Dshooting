#pragma once
#include<functional>

using namespace std;

struct SpriteItem
{
	Math::Vector2 pos;
	Math::Rectangle rect;
	Math::Vector2 radius;
	Math::Vector2 scale;
	Math::Color color;

	const KdTexture* tex;

	Math::Matrix transMat;
	Math::Matrix scaleMat;
	Math::Matrix mat;

	//フレーム用
	Math::Vector2 framescale;
	Math::Matrix framescalemat;
	Math::Matrix framemat;

	//上に乗っているか
	bool GetIsOnTop();

	//何をするか
	function<void()> action;
};

class C_ScenesUiBase
{
public:
	C_ScenesUiBase() { m_frametex.Load("Texture/Ui/IsOnTopFrame.png"); }
	virtual ~C_ScenesUiBase(){}

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	
	//画像ロード
	virtual void TextureLoad();

	//背景用
	virtual void BackGroundInit();
	virtual void BackGroundUpdate();
	virtual void BackGroundDraw();

	//共通背景
	void BlackBackInit();
	void BlackBackUpdate();
	void BlackBackDraw();

	//押せるUiが押された
	void ClickableUi();
	//上に乗っている間描画
	void IsOnTopDraw();
	//Initを呼び出すたびに画像を増やせる
	void CreateSpriteItemInit(Math::Vector2 pos, Math::Rectangle rect, Math::Vector2 scale,const KdTexture* tex, Math::Color color);
	void CreateSpriteItemUpdate();
	void CreateSpriteItemDraw();

	//ボタンごとにactionを入れる
	void SetAction(int index, function<void()> action) { m_SpriteItem[index].action = action; };

protected:

	//背景用///
	
	//画像
	KdTexture m_backgroundtex;
	//切り取り範囲
	Math::Rectangle m_backgroundrect;
	//行列
	Math::Matrix m_backgroundscalemat;
	Math::Matrix m_backgroundtransmat;
	Math::Matrix m_backgroundmat;
	//座標
	Math::Vector2 m_backgroundpos;
	//サイズ
	Math::Vector2 m_backgroundscale;
	//アニメーション用
	Math::Vector2 m_backgroundanim;
	//カラー
	Math::Color m_backgroundcolor;
	////////////

	//押せるUi用////

	std::vector<SpriteItem> m_SpriteItem;

	////////////////

private:

	//共通背景用///
	//座標
	Math::Vector2 m_blackbackpos;
	//行列
	Math::Matrix m_blackbackmat;
	//カラー
	Math::Color m_blackbackcolor;
	///////////////

	//フレーム用///
	KdTexture m_frametex;
	Math::Rectangle m_framerect = { 0,0,360,360 };
	//////////////

};

