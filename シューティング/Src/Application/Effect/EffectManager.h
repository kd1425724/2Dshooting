#pragma once

class C_EffectBase;

enum class EffectType
{
	Explosion,
	ExplosionTopDraw,
	LaserStartGreen,
	LaserStartRed,
	BoltHitBule,
	BoltHitGreen,
	CopyHit,
	WarningLine
};

class C_EffectManager
{
public:

	void Init();
	void Update();
	void Draw();

	void IsTopDraw();
	void IsBottomDraw();

	void Release();

	// 追加（外からエフェクトを入れる）
	void AddEffect(EffectType type, Math::Vector2 pos, Math::Vector2 scale = { 1.0f,1.0f }, int time = 0);

private:

	std::vector<std::shared_ptr<C_EffectBase>> m_effects;
	std::vector<std::shared_ptr<C_EffectBase>> m_topdraweffects;
	std::vector<std::shared_ptr<C_EffectBase>> m_bottomdraweffects;
	//エフェクト保管用
	std::vector<std::shared_ptr<C_EffectBase>> m_addeffects;
	std::vector<std::shared_ptr<C_EffectBase>> m_addtopdraweffects;
	std::vector<std::shared_ptr<C_EffectBase>> m_addbottomdraweffects;


	//爆発画像
	std::shared_ptr<KdTexture> m_explosiontex;

	//レーザー
	std::shared_ptr<KdTexture> m_laserstartgreeneffecttex;
	std::shared_ptr<KdTexture> m_laserstartredeffecttex;

	//予告線
	std::shared_ptr<KdTexture> m_warninglinetex;

	//ヒットエフェクト
	//Bolt青
	std::shared_ptr<KdTexture> m_boltbluehiteffecttex;
	//Bolt緑
	std::shared_ptr<KdTexture> m_boltgreenhiteffecttex;
	//コピー
	std::shared_ptr<KdTexture> m_copyhiteffecttex;
private:
	C_EffectManager() {}
	~C_EffectManager() { Release(); }

public:

	static C_EffectManager& GetInstance()
	{
		static C_EffectManager instance;
		return instance;
	}
};

#define EFFECTMANAGER C_EffectManager::GetInstance()