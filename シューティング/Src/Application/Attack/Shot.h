#pragma once
#include<vector>

using namespace std;

enum class ShotType
{
	NormalShot,
	ShotNum	//数
};

enum class ShotTextureType
{
	Bolt,

};

//元画像の向き
enum class ShotTextureAngle
{
	Top,		//上
	Bottom,		//下
	Left,		//左
	Right 		//右
};

struct Shot
{
	//座標
	Math::Vector2 pos;
	//移動量
	Math::Vector2 move;
	//スピード
	float speed;
	//フラグ
	bool alive = false;
	//サイズ
	Math::Vector2 scale;
	//行列
	Math::Matrix scalemat;
	Math::Matrix transmat;
	Math::Matrix rotatemat;
	Math::Matrix mat;
	//切り取り範囲
	Math::Vector2 rect;
	//カラー
	Math::Color color;
	//角度
	float angle;
	//テクスチャ設定セット
	void SetTextureSetting(ShotTextureType type);
	float texangle;

	//アニメーション用
	Math::Vector2 anim;
	Math::Vector2 animmaxnum;
	float animspeed;

	//初期化
	void Init(ShotType a_type,ShotTextureType a_texturetype,Math::Vector2 a_animmaxnum, Math::Vector2 a_rect, Math::Vector2 a_pos, Math::Vector2 target);
};


class C_Shot
{
public:
	C_Shot();
	~C_Shot(){}

	void Update();
	void Draw();

	//指定した弾を発射
	//a_type...どの弾か
	//a_animmaxnum...画像のアニメーション最大値
	//a_rect...画像の切り取り範囲
	//a_pos...発生位置
	//a_target...狙い
	void ShotManager(ShotType a_type, ShotTextureType a_texturetype, Math::Vector2 a_animmaxnum, Math::Vector2 a_rect, Math::Vector2 a_pos, Math::Vector2 target);

	

private:

	//弾テクスチャ一覧
	//入れ物
	KdTexture m_tex;
	KdTexture* m_bolttex;

	void SetTexture(ShotTextureType type);

	//通常ショット（弾一発）
	vector<Shot> m_normalshot;

	//一発発射
	void NormalShotInit(ShotTextureType a_texturetype,Math::Vector2 a_animmaxnum, Math::Vector2 a_rect, Math::Vector2 a_pos, Math::Vector2 target);
	void NormalShotUpdate();
	void NormalShotDraw();

};
