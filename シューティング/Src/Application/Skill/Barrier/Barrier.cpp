#include "Barrier.h"
#include"../../Player/Player.h"
#include "../../Enemy/EnemyMoveBase.h"
#include"../../Common/CommonAPI.h"
#include"../../Hit/HitManager.h"

C_Barrier::C_Barrier()
{
    m_rect = { 128,128 };
    m_color = { 1,1,1,1 };

    m_rot = 0.0f;
    m_alpha = 0.8f;

    m_alive = false;

    m_finished = false;
}

void C_Barrier::Init()
{
    m_anim = 0;
    m_flashing = Flashing::Down;
    m_time = MaxTime;
}

void C_Barrier::SetTexture(std::shared_ptr<KdTexture> tex)
{
    m_tex = tex;
}

void C_Barrier::SkillActivate()
{
    m_alive = true;
    m_scale = { 1.0f,1.0f };
    m_dir = { 1.0f,0.0f };
    m_alpha = 0.8f;
    m_rot = atan2(m_dir.y, m_dir.x) + COMMONAPI.GetTextureAngleAdjustment(TextureAngle::Top);

    //半径
    m_halfsize = m_rect * m_scale / 2;
    m_radius = m_rect.x * m_scale.x / 2;

    auto p = m_player.lock();
    auto hm = m_hitmanager.lock();

    m_time = MaxTime;

    if (p&&hm)
    {
        m_pos = p->GetPos();
        hm->SetPlayerBarrier(shared_from_this());
    }
}

void C_Barrier::EnemySkillActivate(Math::Vector2 scale)
{
    m_alive = true;
    m_scale = scale;
    m_dir = { -1.0f,0.0f };
    m_alpha = 0.8f;
    m_rot = atan2(m_dir.y, m_dir.x) + COMMONAPI.GetTextureAngleAdjustment(TextureAngle::Top);

    //半径
    m_halfsize = m_rect * m_scale / 2;
    m_radius = m_rect.x * m_scale.x / 2.1f;

    auto e = m_enemy.lock();
    auto hm = m_hitmanager.lock();

    m_time = MaxTime;

    if (e&&hm)
    {
        m_pos = { e->GetPos().x,e->GetPos().y };
        hm->SetEnemyBarrier(shared_from_this());
    }
}

void C_Barrier::Update()
{
    if (!m_alive) return;

    auto p = m_player.lock();
    auto e = m_enemy.lock();

    if (m_usetype == UseType::Player && p)
    {
        m_pos = p->GetPos();
    }
    else if (m_usetype == UseType::Enemy && e)
    {
        m_pos = { e->GetPos().x , e->GetPos().y };
    }
    //アニメーション用
    m_anim += 0.1f;
    if (m_anim >= AnimMaxNum)
    {
        m_anim = 0;
    }


    // =========================
    // 点滅（アルファ）
    // =========================
    if (m_time < 120)
    {
        if (m_flashing == Flashing::Up)
        {
            m_alpha += 0.01f;
            if (m_alpha >= 0.6f)
            {
                m_alpha = 0.6f;
                m_flashing = Flashing::Down;
            }
        }
        else if (m_flashing == Flashing::Down)
        {
            m_alpha -= 0.01f;
            if (m_alpha <= 0.3f)
            {
                m_alpha = 0.3f;
                m_flashing = Flashing::Up;
            }
        }
    }

    //発生時間
    if (m_time > 0)
    {
        m_time--;
        if (m_time <= 0)
        {
            m_time = 0;
            m_alive = false;

            m_finished = true;
        }
    }
}

void C_Barrier::Draw()
{
    auto t = m_tex.lock();

    if (!m_alive || !t) return;

    // =========================
    // 行列作成
    // =========================
    Math::Matrix scale = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1);
    Math::Matrix rot = Math::Matrix::CreateRotationZ(m_rot);
    Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);

    Math::Matrix mat = scale* rot;
    mat = mat * trans;

    // =========================
    // 色反映（透明度）
    // =========================
    m_color = { 1,1,1,m_alpha };

    // =========================
    // 描画
    // =========================
    KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);

    KdShaderManager::GetInstance().m_spriteShader.DrawTex(
        t.get(),
        0,
        0,
        &Math::Rectangle((int)m_anim*m_rect.x, 0, m_rect.x, m_rect.y),
        &m_color
    );
}