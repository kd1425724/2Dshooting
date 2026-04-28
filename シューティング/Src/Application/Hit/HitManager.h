#pragma once

class C_HitBase;
enum class HitType;

class C_HitManager
{
public:
	C_HitManager();
	~C_HitManager();

	void Init();
	void Update();

	// 登録・解除
	void AddHit(std::shared_ptr<C_HitBase> hit);
	void Clear();

	void RemoveHit(std::shared_ptr<C_HitBase> hit);

private:
	std::vector<std::shared_ptr<C_HitBase>> m_hits;

	// 当たり判定組み合わせチェック
	bool CanHit(HitType a, HitType b);
};