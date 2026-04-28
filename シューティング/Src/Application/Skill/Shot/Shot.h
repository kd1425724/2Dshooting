#pragma once
#include<vector>

using namespace std;

class C_ShotHit;
class C_HitManager;

enum class ShotType
{
	NormalShot,
	EnemyNormalShot,
	ShotNum	//数
};

enum class ShotTextureType
{
	Bolt,

};

struct Shot : public std::enable_shared_from_this<Shot>
{
	//座標
	Math::Vector2 pos = {0,0};
	//移動量
	Math::Vector2 move = {0,0};
	//スピード
	float speed = 0;
	//フラグ
	bool alive = false;
	//サイズ
	Math::Vector2 scale = { 1,1 };
	//行列
	Math::Matrix scalemat;
	Math::Matrix transmat;
	Math::Matrix rotatemat;
	Math::Matrix mat;
	//切り取り範囲
	Math::Vector2 rect = { 0,0 };
	//カラー
	Math::Color color = { 1,1,1,1 };
	//角度
	float angle = 0;
	//テクスチャ設定セット
	void SetTextureSetting(ShotTextureType type);
	float texangle=0;

	//アニメーション用
	Math::Vector2 anim = { 0,0 };
	Math::Vector2 animmaxnum = { 0,0 };
	float animspeed=0;

	//当たり判定
	std::shared_ptr<C_ShotHit> m_hit;

	//初期化（targetpos指定バージョン）
	void Init(ShotType a_type,ShotTextureType a_texturetype,Math::Vector2 a_animmaxnum, Math::Vector2 a_rect, Math::Vector2 a_pos, Math::Vector2 target,int movespeed);
	//初期化（angle指定バージョン）
	void Init(ShotType a_type,ShotTextureType a_texturetype,Math::Vector2 a_animmaxnum, Math::Vector2 a_rect, Math::Vector2 a_pos, float a_angle, int movespeed);
	
	//当たり管理用
	std::shared_ptr<C_HitManager> m_hitmanager;

	void SetHitManager(std::shared_ptr<C_HitManager> hitmanager) { m_hitmanager = hitmanager; }

	//弾消し
	void SetAlive(bool flg) { alive = flg; }
	
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
	//a_texturetype...どの弾画像か
	//a_animmaxnum...画像のアニメーション最大値
	//a_rect...画像の切り取り範囲
	//a_pos...発生位置
	//a_target...狙い
	void ShotManager(ShotType a_type, ShotTextureType a_texturetype, Math::Vector2 a_animmaxnum, Math::Vector2 a_rect, Math::Vector2 a_pos, Math::Vector2 target, int movespeed);
	//アングル指定バージョン
	void ShotManager(ShotType a_type, ShotTextureType a_texturetype, Math::Vector2 a_animmaxnum, Math::Vector2 a_rect, Math::Vector2 a_pos, float a_angle, int movespeed);

	void SetHitManager(std::shared_ptr<C_HitManager> hitmanager) { m_hitmanager = hitmanager; }

private:

	//当たり管理用
	std::shared_ptr<C_HitManager> m_hitmanager;

	//弾テクスチャ一覧
	//入れ物
	KdTexture m_tex;
	KdTexture* m_bolttex;

	void SetTexture(ShotTextureType type);

	//通常ショット（弾一発）
	vector<std::shared_ptr<Shot>> m_normalshot;

	//一発発射
	void NormalShotInit(ShotTextureType a_texturetype,Math::Vector2 a_animmaxnum, Math::Vector2 a_rect, Math::Vector2 a_pos, Math::Vector2 target, int movespeed);
	//アングル指定バージョン
	void NormalShotInit(ShotTextureType a_texturetype,Math::Vector2 a_animmaxnum, Math::Vector2 a_rect, Math::Vector2 a_pos, float a_angle, int movespeed);
	void NormalShotUpdate();
	void NormalShotDraw();

};
