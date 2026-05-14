#pragma once
#include<vector>

using namespace std;

class C_HitManager;

enum class ShotType
{
	NormalShot,
	EnemyNormalShot,
	CopyShot,
	ShotNum	//数
};

enum class ShotTextureType
{
	Bolt,
	Pulse,
	Copy
};

struct Shot : public std::enable_shared_from_this<Shot>
{
	KdTexture* tex;
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
	void SetTexture(KdTexture* _tex) { tex = _tex; }
	float texangle=0;

	//アニメーション用
	Math::Vector2 anim = { 0,0 };
	Math::Vector2 animmaxnum = { 0,0 };
	float animspeed=0;

	//半径
	float m_radius;
	Math::Vector2 m_halfsize;

	//初期化（targetpos指定バージョン）
	void Init(ShotType a_type,ShotTextureType a_texturetype,Math::Vector2 a_animmaxnum, Math::Vector2 a_rect, Math::Vector2 a_pos, Math::Vector2 target,int movespeed);
	//初期化（angle指定バージョン）
	void Init(ShotType a_type,ShotTextureType a_texturetype,Math::Vector2 a_animmaxnum, Math::Vector2 a_rect, Math::Vector2 a_pos, float a_angle, int movespeed);
	
	//当たり管理用
	std::weak_ptr<C_HitManager> m_hitmanager;

	void SetHitManager(std::shared_ptr<C_HitManager> hitmanager) { m_hitmanager = hitmanager; }

	bool GetAlive() { return alive; }

	//弾消し
	void SetAlive(bool flg) { alive = flg; }

	//座標取得用
	Math::Vector2 GetPos() { return pos; }

	//半径x,y別（矩形）
	Math::Vector2 GetSize() { return m_halfsize; }

	//半径（円判定）
	float GetRadius() { return m_radius; }

	
};


class C_Shot
{
public:
	C_Shot();
	~C_Shot() { Release(); }

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

	void Release();

	//当たり管理用
	std::shared_ptr<C_HitManager> m_hitmanager;

	//弾テクスチャ一覧
	KdTexture m_bolttex;
	KdTexture m_pulsetex;
	KdTexture m_copyshottex;

	//通常ショット（弾一発）
	vector<std::shared_ptr<Shot>> m_normalshot;

	//一発発射
	void NormalShotInit(ShotType shottype, ShotTextureType a_texturetype,Math::Vector2 a_animmaxnum, Math::Vector2 a_rect, Math::Vector2 a_pos, Math::Vector2 target, int movespeed);
	//アングル指定バージョン
	void NormalShotInit(ShotType shottype, ShotTextureType a_texturetype,Math::Vector2 a_animmaxnum, Math::Vector2 a_rect, Math::Vector2 a_pos, float a_angle, int movespeed);
	void NormalShotUpdate();
	void NormalShotDraw();

	KdTexture* SetTextureType(ShotTextureType type);
};
