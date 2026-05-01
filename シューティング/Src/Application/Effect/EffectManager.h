#pragma once

class C_EffectBase;

enum class EffectType
{
	Explosion,
	BoltHitEffect,
};

class C_EffectManager
{
public:

	void Init();
	void Update();
	void Draw();
	void Release();

	// 追加（外からエフェクトを入れる）
	void AddEffect(EffectType type, Math::Vector2 pos);

private:

	std::vector<std::shared_ptr<C_EffectBase>> m_effects;


	//爆発画像
	std::shared_ptr<KdTexture> m_explosiontex;

	//ヒットエフェクト
	//Bolt
	std::shared_ptr<KdTexture> m_bolthiteffcttex;

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