#include "HitManager.h"
#include"../Player/Player.h"
#include"../Enemy/EnemyMoveBase.h"
#include"../Skill/Shot/Shot.h"
#include"../Skill/Laser1/Laser.h"
#include"../Skill/Barrier/Barrier.h"
#include"../Effect/EffectManager.h"
#include"../Skill/SkillManager.h"

C_HitManager::C_HitManager()
{
	m_DrawHitdebugflg = false;
}

C_HitManager::~C_HitManager()
{
}

void C_HitManager::Init()
{
}

void C_HitManager::Update()
{
	//プレイヤー当たり判定
	PlayerHit();

	//プレイヤーの弾の当たり判定
	PlayerShotHit();

	//敵の弾の当たり判定
	EnemyShotHit();

	//コピー弾の当たり判定
	CopyHit();
}



void C_HitManager::Clear()
{
	
}

void C_HitManager::PlayerHit()
{
	//weakからsharedに変換
	std::shared_ptr<C_Player> p = m_player.lock();

	//プレイヤー判定
	//存在してたら
	if (p)
	{
		Math::Vector2 p_pos = p->GetPos();
		Math::Vector2 p_size = p->GetSize();
		float p_radius = p->GetRadius();

		//敵との当たり判定
		for (auto it = m_enemys.begin(); it != m_enemys.end(); )
		{
			std::shared_ptr<C_EnemyMoveBase> e = it->lock();
			if (e)
			{
				if (!e->GetAlive())
				{
					it = m_enemys.erase(it);
					continue;
				}
				if (IsHit(p_pos, p_radius, e->GetPos(), e->GetRadius()))
				{
					//プレイヤーのダメージ
					p->Damage();
					//敵のダメージ
					e->Damage(1);
				}
				++it;
			}
			else
			{
				it = m_enemys.erase(it);
			}
		}
		
		//敵の弾との当たり判定
		for (auto it = m_enemyshot.begin(); it != m_enemyshot.end(); )
		{
			std::shared_ptr<Shot> enemy3 = it->lock();
			if (enemy3)
			{
				if (!enemy3->GetAlive())
				{
					it = m_enemyshot.erase(it);
					continue;
				}
				if (IsHit(p_pos, p_radius, enemy3->GetPos(), enemy3->GetRadius()))
				{
					p->Damage();
					//s->SetAlive(false);
				}
				++it;
			}
			else
			{
				it = m_enemyshot.erase(it);
			}
		}

		//敵のレーザーとの当たり判定
		for (auto it = m_enemylaser.begin(); it != m_enemylaser.end(); )
		{
			std::shared_ptr<C_Laser> l = it->lock();
			if (l)
			{
				if (!l->GetAlive())
				{
					it = m_enemylaser.erase(it);
					continue;
				}
				if (IsHitLaser(l->GetStart(),l->GetEnd(),l->GetThick(), p->GetPos(), p->GetRadius()))
				{
					p->Damage();
				}
				++it;
			}
			else
			{
				it = m_enemylaser.erase(it);
			}
		}

		//バリアとの当たり判定
		for (auto it = m_enemybarrier.begin(); it != m_enemybarrier.end(); )
		{
			std::shared_ptr<C_Barrier> eb = it->lock(); 
			if (eb)
			{
				if (!eb->GetAlive())
				{
					it = m_enemybarrier.erase(it);
					continue;
				}
				if (IsHit(p->GetPos(), p->GetRadius(),eb->GetPos(),eb->GetRadius()))
				{
					
				}
				++it;
			}
			else
			{
				it = m_enemybarrier.erase(it);
			}
		}
	}

}

void C_HitManager::PlayerShotHit()
{
	//プレイヤーの弾の当たり判定
	for (auto psit = m_playershot.begin(); psit != m_playershot.end(); )
	{
		std::shared_ptr<Shot> ps = psit->lock();

		if (ps)
		{
			Math::Vector2 ps_pos = ps->GetPos();
			Math::Vector2 ps_size = ps->GetSize();
			float ps_radius = ps->GetRadius();

			if (!ps->GetAlive())
			{
				psit = m_playershot.erase(psit);
				continue;
			}

			//敵との当たり判定
			for (auto it = m_enemys.begin(); it != m_enemys.end(); )
			{
				std::shared_ptr<C_EnemyMoveBase> e = it->lock();

				if (e)
				{
					if (!e->GetAlive())
					{
						it = m_enemys.erase(it);
						continue;
					}
					if (IsHit(ps_pos, ps_radius, e->GetPos(), e->GetSize().x))
					{
						ps->SetAlive(false);
						e->Damage(500);
						EFFECTMANAGER.AddEffect(EffectType::BoltHitEffect, ps_pos);
					}
					++it;
				}
				else
				{
					it = m_enemys.erase(it);
				}
			}

			//敵のレーザーとの当たり判定
			for (auto it = m_enemylaser.begin(); it != m_enemylaser.end(); )
			{
				std::shared_ptr<C_Laser> l = it->lock();
				if (l)
				{
					if (!l->GetAlive())
					{
						it = m_enemylaser.erase(it);
						continue;
					}
					if (IsHitLaser(l->GetStart(), l->GetEnd(), l->GetThick(), ps_pos, ps_radius))
					{
						ps->SetAlive(false);
					}
					++it;
				}
				else
				{
					it = m_enemylaser.erase(it);
				}
			}

			//敵バリアとの当たり判定
			for (auto it = m_enemybarrier.begin(); it != m_enemybarrier.end(); )
			{
				std::shared_ptr<C_Barrier> eb = it->lock();

				if (eb)
				{
					if (!eb->GetAlive())
					{
						it = m_enemybarrier.erase(it);
						continue;
					}

					if (IsHit(ps_pos, ps_radius, eb->GetPos(), eb->GetRadius()))
					{
						ps->SetAlive(false);
					}
					++it;
				}
				else
				{
					it = m_enemybarrier.erase(it);
				}
			}

			++psit;
		}
		else
		{
			psit = m_playershot.erase(psit);
			continue;
		}
	}
	//プレイヤーのレーザーの当たり判定
	for (auto plit = m_playerlaser.begin(); plit != m_playerlaser.end();)
	{
		std::shared_ptr<C_Laser> pl = plit->lock();

		if (pl)
		{
			Math::Vector2 pl_start = pl->GetStart();
			Math::Vector2 pl_end = pl->GetEnd();
			float pl_thick = pl->GetThick();

			//存在しなければ消去
			if (!pl->GetAlive())
			{
				plit = m_playerlaser.erase(plit);
				continue;
			}

			//敵との当たり判定
			for (auto it = m_enemys.begin(); it != m_enemys.end(); )
			{
				std::shared_ptr<C_EnemyMoveBase> e = it->lock();
				if (e)
				{
					if (!e->GetAlive())
					{
						it = m_enemys.erase(it);
						continue;
					}
					if (IsHitLaser(pl_start, pl_end, pl_thick, e->GetPos(), e->GetRadius()))
					{
						//敵のダメージ
						e->Damage(50);
					}
					++it;
				}
				else
				{
					it = m_enemys.erase(it);
				}
			}

			//敵の弾との当たり判定
			for (auto it = m_enemyshot.begin(); it != m_enemyshot.end(); )
			{
				std::shared_ptr<Shot> es = it->lock();
				if (es)
				{
					if (!es->GetAlive())
					{
						it = m_enemyshot.erase(it);
						continue;
					}

					if (IsHitLaser(pl_start, pl_end, pl_thick, es->GetPos(), es->GetRadius()))
					{
						es->SetAlive(false);
					}
					++it;
				}
				else
				{
					it = m_enemyshot.erase(it);
				}
			}


			++plit;
		}
		else
		{
			plit = m_playerlaser.erase(plit);
			continue;
		}
	}

	//プレイヤーの生成敵の当たり判定
	for (auto peit = m_playerenemys.begin(); peit != m_playerenemys.end();)
	{
		std::shared_ptr<C_EnemyMoveBase> pe = peit->lock();

		if (pe)
		{
			Math::Vector2 pe_pos = pe->GetPos();
			Math::Vector2 pe_size = pe->GetSize();
			float pe_radius = pe->GetRadius();

			if (!pe->GetAlive())
			{
				peit = m_playerenemys.erase(peit);
				continue;
			}

			//敵との当たり判定
			for (auto it = m_enemys.begin(); it != m_enemys.end(); )
			{
				std::shared_ptr<C_EnemyMoveBase> e = it->lock();

				if (e)
				{
					if (!e->GetAlive())
					{
						it = m_enemys.erase(it);
						continue;
					}
					if (IsHit(pe_pos, pe_radius, e->GetPos(), e->GetSize().x))
					{
						pe->Damage(20);
					}
					++it;
				}
				else
				{
					it = m_enemys.erase(it);
				}
			}


			//敵の弾との当たり判定
			for (auto esit = m_enemyshot.begin(); esit != m_enemyshot.end();)
			{
				std::shared_ptr<Shot> es = esit->lock();

				if (es)
				{
					Math::Vector2 es_pos = es->GetPos();
					Math::Vector2 es_size = es->GetSize();
					float es_radius = es->GetRadius();

					if (!es->GetAlive())
					{
						esit = m_enemyshot.erase(esit);
						continue;
					}
					if (IsHit(pe_pos, pe_radius, es->GetPos(), es->GetRadius()))
					{
						es->SetAlive(false);
						pe->Damage(10);
					}

					++esit;
				}
			}

			//敵のレーザーとの当たり判定
			for (auto it = m_enemylaser.begin(); it != m_enemylaser.end(); )
			{
				std::shared_ptr<C_Laser> l = it->lock();
				if (l)
				{
					if (!l->GetAlive())
					{
						it = m_enemylaser.erase(it);
						continue;
					}
					if (IsHitLaser(l->GetStart(), l->GetEnd(), l->GetThick(), pe_pos, pe_radius))
					{
						pe->Damage(10);
					}
					++it;
				}
				else
				{
					it = m_enemylaser.erase(it);
				}
			}


			++peit;
		}
		else
		{
			peit = m_playerenemys.erase(peit);
		}
	}
}

void C_HitManager::CopyHit()
{
	for (auto it = m_copyshot.begin(); it != m_copyshot.end();)
	{
		std::shared_ptr<Shot> c = it->lock();

		if (c)
		{
			Math::Vector2 c_pos = c->GetPos();
			Math::Vector2 c_size = c->GetSize();
			float c_radius = c->GetRadius();

			if (!c->GetAlive())
			{
				it = m_copyshot.erase(it);
				continue;
			}

			//敵との当たり判定
			for (auto it = m_enemys.begin(); it != m_enemys.end(); )
			{
				std::shared_ptr<C_EnemyMoveBase> e = it->lock();

				if (e)
				{
					if (!e->GetAlive())
					{
						it = m_enemys.erase(it);
						continue;
					}

					if (IsHit(c_pos, c_radius, e->GetPos(), e->GetSize().x))
					{
						c->SetAlive(false);
						
						std::shared_ptr<C_Player> p = m_player.lock();

						std::shared_ptr<C_SkillManager> sm = m_skillmanager.lock();

						if (p && sm)
						{
							sm->SetPlayerSkill(e->GetSkillType());
						}
					//	EFFECTMANAGER.AddEffect(EffectType::Explosion, ps_pos);
					}
					++it;
				}
				else
				{
					it = m_enemys.erase(it);
				}
			}

			++it;
		}
		else
		{
			it = m_copyshot.erase(it);
			continue;
		}

	}
}

void C_HitManager::EnemyHit()
{
	
}

void C_HitManager::EnemyShotHit()
{
	//敵の弾の判定
	for (auto esit = m_enemyshot.begin(); esit != m_enemyshot.end();)
	{
		std::shared_ptr<Shot> es = esit->lock();

		if (es)
		{
			Math::Vector2 es_pos = es->GetPos();
			Math::Vector2 es_size = es->GetSize();
			float es_radius = es->GetRadius();

			if (!es->GetAlive())
			{
				esit = m_enemyshot.erase(esit);
				continue;
			}

			//プレイヤーバリアとの当たり判定
			for (auto it = m_playerbarrier.begin(); it != m_playerbarrier.end(); )
			{
				std::shared_ptr<C_Barrier> pb = it->lock();

				if (pb)
				{
					if (!pb->GetAlive())
					{
						it = m_playerbarrier.erase(it);
						continue;
					}

					if (IsHit(es_pos, es_radius, pb->GetPos(), pb->GetRadius()))
					{
						es->SetAlive(false);
					}
					++it;
				}
				else
				{
					it = m_playerbarrier.erase(it);
				}
			}

			++esit;
		}
		else
		{
			esit = m_enemyshot.erase(esit);
		}
	}
}


//当たり判定処理（円判定用）
bool C_HitManager::IsHit(Math::Vector2 pos1, float r1, Math::Vector2 pos2, float r2)
{
	float dx = pos1.x - pos2.x;
	float dy = pos1.y - pos2.y;

	float distSq = dx * dx + dy * dy;
	float rSum = r1 + r2;

	return distSq <= (rSum * rSum);

	return false;
}
//矩形
bool C_HitManager::IsHit(Math::Vector2 pos1, Math::Vector2 halfSize1, Math::Vector2 pos2, Math::Vector2 halfSize2)
{
	return (abs(pos1.x - pos2.x) <= (halfSize1.x + halfSize2.x)) &&
		(abs(pos1.y - pos2.y) <= (halfSize1.y + halfSize2.y));

	return false;
}

bool C_HitManager::IsHitLaser(Math::Vector2 start,Math::Vector2 end,float laserThick,Math::Vector2 pos,	float radius)
{
	// 線分ベクトル
	Math::Vector2 ab = end - start;

	// 始点→対象
	Math::Vector2 ac = pos - start;

	float abLenSq = ab.x * ab.x + ab.y * ab.y;
	if (abLenSq == 0.0f) return false;

	// 最近点係数
	float t = (ac.x * ab.x + ac.y * ab.y) / abLenSq;
	t = std::max(0.0f, std::min(1.0f, t));

	// 最近点
	Math::Vector2 closest;
	closest.x = start.x + ab.x * t;
	closest.y = start.y + ab.y * t;

	// 距離
	float dx = pos.x - closest.x;
	float dy = pos.y - closest.y;

	float distSq = dx * dx + dy * dy;

	// ★ここが太さ
	float r = radius + laserThick;

	return distSq <= (r * r);
}

//当たり判定描画
void C_HitManager::Draw()
{
	if (!m_DrawHitdebugflg)return;

	Math::Matrix mat = Math::Matrix::Identity;
	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);

	// =========================
	// プレイヤー
	// =========================
	if (auto p = m_player.lock())
	{
		DrawCircle(p->GetPos(), p->GetRadius(), { 1,0,0,1 }); // 赤
	}

	// =========================
	// 敵
	// =========================
	for (auto& w : m_enemys)
	{
		if (auto e = w.lock())
		{
			DrawCircle(e->GetPos(), e->GetSize().x, { 0,1,0,1 }); // 緑
		}
	}

	// =========================
	// プレイヤー弾
	// =========================
	for (auto& w : m_playershot)
	{
		if (auto enemy3 = w.lock())
		{
			DrawCircle(enemy3->GetPos(), enemy3->GetRadius(), { 0,1,1,1 }); // 水色
		}
	}

	// =========================
	// コピー弾（追加）
	// =========================
	for (auto& w : m_copyshot)
	{
		if (auto enemy3 = w.lock())
		{
			DrawCircle(enemy3->GetPos(), enemy3->GetRadius(), { 1,0.5f,0,1 }); // オレンジ
		}
	}

	// =========================
	// 敵弾
	// =========================
	for (auto& w : m_enemyshot)
	{
		if (auto enemy3 = w.lock())
		{
			DrawCircle(enemy3->GetPos(), enemy3->GetRadius(), { 1,1,0,1 }); // 黄
		}
	}

	// =========================
	// プレイヤーバリア（追加）
	// =========================
	for (auto& w : m_playerbarrier)
	{
		if (auto b = w.lock())
		{
			DrawCircle(b->GetPos(), b->GetRadius(), { 0,0.5f,1,1 }); // 青っぽい
		}
	}

	// =========================
	// 敵バリア
	// =========================
	for (auto& w : m_enemybarrier)
	{
		if (auto b = w.lock())
		{
			DrawCircle(b->GetPos(), b->GetRadius(), { 1,0,1,1 }); // 紫
		}
	}

	// =========================
	// レーザー
	// =========================
	for (auto& w : m_enemylaser)
	{
		if (auto l = w.lock())
		{
			auto enemy3 = l->GetStart();
			auto e = l->GetEnd();
			float t = l->GetThick();

			Math::Color col = { 0,0,1,1 }; // 青

			// 中心線
			KdShaderManager::GetInstance().m_spriteShader.DrawLine(
				(int)enemy3.x, (int)enemy3.y,
				(int)e.x, (int)e.y,
				&col
			);

			// 太さ
			KdShaderManager::GetInstance().m_spriteShader.DrawLine(
				(int)enemy3.x, (int)(enemy3.y - t),
				(int)e.x, (int)(e.y - t),
				&col
			);

			KdShaderManager::GetInstance().m_spriteShader.DrawLine(
				(int)enemy3.x, (int)(enemy3.y + t),
				(int)e.x, (int)(e.y + t),
				&col
			);
		}
	}

	// =========================
	// プレイヤーレーザー（追加）
	// =========================
	for (auto& w : m_playerlaser)
	{
		if (auto l = w.lock())
		{
			auto enemy3 = l->GetStart();
			auto e = l->GetEnd();
			float t = l->GetThick();

			Math::Color col = { 1,0,0,1 }; // 赤（プレイヤー用）

			// 中心線
			KdShaderManager::GetInstance().m_spriteShader.DrawLine(
				(int)enemy3.x, (int)enemy3.y,
				(int)e.x, (int)e.y,
				&col
			);

			// 太さ（上下にオフセット）
			KdShaderManager::GetInstance().m_spriteShader.DrawLine(
				(int)enemy3.x, (int)(enemy3.y - t),
				(int)e.x, (int)(e.y - t),
				&col
			);

			KdShaderManager::GetInstance().m_spriteShader.DrawLine(
				(int)enemy3.x, (int)(enemy3.y + t),
				(int)e.x, (int)(e.y + t),
				&col
			);
		}
	}
}
void C_HitManager::DrawCircle(Math::Vector2 pos, float radius, Math::Color col)
{
	const int segment = 32;

	for (int i = 0; i < segment; i++)
	{
		float a1 = DirectX::XM_2PI * i / segment;
		float a2 = DirectX::XM_2PI * (i + 1) / segment;

		Math::Vector2 p1 = {
			pos.x + cosf(a1) * radius,
			pos.y + sinf(a1) * radius
		};

		Math::Vector2 p2 = {
			pos.x + cosf(a2) * radius,
			pos.y + sinf(a2) * radius
		};

		KdShaderManager::GetInstance().m_spriteShader.DrawLine(
			(int)p1.x, (int)p1.y,
			(int)p2.x, (int)p2.y,
			&col
		);
	}
}

void C_HitManager::ImGui()
{
	ImGui::Checkbox(u8"当たり判定描画", &m_DrawHitdebugflg);
}