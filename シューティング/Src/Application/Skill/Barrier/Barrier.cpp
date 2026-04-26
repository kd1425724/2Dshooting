#include "Barrier.h"
#include"../../Prayer/Player.h"
#include "../../Enemy/EnemyMoveBase.h"
#include"../../Common/CommonAPI.h"

C_Barrier::C_Barrier()
{
    m_rect = { 64,64 };
    m_color = { 1,1,1,1 };

    m_rot = 0.0f;
    m_alpha = 1.0f;

    m_isActive = false;
}

C_Barrier::~C_Barrier()
{
}

void C_Barrier::Init()
{
    m_anim = 0;
    m_flashing = Flashing::Up;
}

void C_Barrier::SetTexture(std::shared_ptr<KdTexture> tex)
{
    m_tex = tex;
}

void C_Barrier::SkillActivate()
{
    m_isActive = true;
    m_scale = { 1.5f,1.5f };
    m_dir = { 1.0f,0.0f };

    m_rot = atan2(m_dir.y, m_dir.x) + COMMONAPI.GetTextureAngleAdjustment(TextureAngle::Top);

    m_pos = m_player->GetPos();
}

void C_Barrier::EnemySkillActivate()
{
    m_isActive = true;
    m_scale = { 4.3f,4.3f };
    m_dir = { -1.0f,0.0f };

    m_rot = atan2(m_dir.y, m_dir.x) + COMMONAPI.GetTextureAngleAdjustment(TextureAngle::Top);
   
    m_pos = { m_enemy->GetPos().x - m_enemy->GetRadius().x+100,m_enemy->GetPos().y };
}

void C_Barrier::Update()
{
    if (!m_isActive) return;

    // =========================
    // プレイヤー追従
    // =========================
    if (m_usetype == UseType::Player && m_player)
    {
        m_pos = m_player->GetPos();
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

void C_Barrier::Draw()
{
    if (!m_isActive || !m_tex) return;

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
        m_tex.get(),
        0,
        0,
        &Math::Rectangle((int)m_anim*m_rect.x, 0, m_rect.x, m_rect.y),
        &m_color
    );
}