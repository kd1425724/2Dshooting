#include "Laser.h"
#include "Application/Enemy/EnemyMoveBase.h"
#include "../../Player/Player.h"
#include"../../Common/CommonAPI.h"
#include"../../Hit/HitManager.h"
C_Laser::C_Laser()
{
    m_length = 0.0f;
    m_maxLength = 1280.0f;
    m_growSpeed = 100.0f;

    m_segmentHeight = 38.0f;
    m_drawCount = 0;

    m_tex = nullptr;
    m_rect = { 18,38 };
    m_color = { 1,1,1,1 };

    m_alive = false;
    m_scale = { 1,1 };

    m_finished = false;

    //スクロール用
    for (int i = 0; i < (int)1280 / 38; i++)
    {
        m_anim[i] = 0;
    }
}

C_Laser::~C_Laser()
{
}

void C_Laser::Init()
{

}

void C_Laser::SkillActivate()
{
    // プレイヤー用レーザー発動
  
    m_launchtime = LaunshTime;
    m_scale = { 2,2 };
    m_alive = true;
    m_length = 0.0f;
    m_color = { 0.2,0.7,1,1 };

    //太さ
    m_thick = m_rect.x * m_scale.x;

    //当たり判定管理に渡す
    if (auto hm = m_hitmanager.lock())
    {
        hm->SetPlayerLaser(shared_from_this());
    }

    if (auto p = m_player.lock())
    {
        m_start = { p->GetPos().x + p->GetSize().x + 40,p->GetPos().y };

        // 右方向
        m_dir = { 1.0f, 0.0f };
    }
}

void C_Laser::EnemySkillActivate()
{
    // 敵用レーザー発動

    m_launchtime = LaunshTime;
    m_scale = { 2,2 };
    m_alive = true;
    m_length = 0.0f;
    m_color = { 1,1,1,1 };

    //太さ
    m_thick = m_rect.x * m_scale.x;

    //当たり判定管理に渡す
    if (auto hm = m_hitmanager.lock())
    {
        hm->SetEnemyLaser(shared_from_this());
    }

    if (auto e = m_enemy.lock())
    {
        m_start = e->GetPos();

        // 左方向
        m_dir = { -1.0f, 0.0f };
    }
}

void C_Laser::Update()
{
    if (!m_alive) return;

    auto e = m_enemy.lock();
    auto p = m_player.lock();

    // 発射位置を追従させる
    if (m_usetype == UseType::Player &&p)
    {
        m_start = { p->GetPos().x + p->GetSize().x+40,p->GetPos().y };
    }
    else if (m_usetype == UseType::Enemy && e)
    {
        m_start.x = e->GetPos().x - 100;
        m_start.y = e->GetPos().y;
    }

    // レーザーを伸ばす
    if (m_length < m_maxLength)
    {
        m_length += m_growSpeed;
    }

    // 描画枚数計算
    m_drawCount = static_cast<int>(m_length / m_segmentHeight);

    //最後尾計算
    m_end = m_start + m_dir * m_length;


    // スクロール用
    for (int i = 0; i < (int)1280 / 38; i++)
    {
        m_anim[i] += 0.3f;
        if (m_anim[i] >= m_animmaxnum)
        {
            m_anim[i] = 0;
        }
    }

    //発射時間
    m_launchtime--;
    if (m_launchtime < 0)
    {
        m_launchtime = 0;

        m_scale.x -= 0.1f;
        if (m_scale.x < 0)
        {
            m_alive = false;
            m_finished = true;
        }
    }

    // 方向から回転角を作る
    float angle = atan2f(m_dir.y, m_dir.x) + COMMONAPI.GetTextureAngleAdjustment(TextureAngle::Top);

    // 基本行列
    m_scalemat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1);
    Math::Matrix rot = Math::Matrix::CreateRotationZ(angle);

    // ※平行移動はDrawで1本ずつやる
    m_mat = m_scalemat * rot;
}

void C_Laser::Draw()
{
    if (!m_alive) return;

    for (int i = 0; i < m_drawCount; i++)
    {
        // =========================
        // 各タイルの位置計算
        // =========================
        m_pos.x = m_start.x + m_dir.x * (i * m_segmentHeight);
        m_pos.y = m_start.y + m_dir.y * (i * m_segmentHeight);

  
        // =========================
        // 平行移動行列
        // =========================
        Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);

        // =========================
        // 最終行列（回転＋移動）
        // =========================
        Math::Matrix mat =m_scalemat* m_mat * trans;

        // =========================
        // シェーダに行列セット
        // =========================
        KdShaderManager::GetInstance().m_spriteShader.SetMatrix(mat);

        // =========================
        // 描画
        // =========================
        KdShaderManager::GetInstance().m_spriteShader.DrawTex(
            m_tex.get(),
            0,
            0,
            &Math::Rectangle((int)m_anim[i]*m_rect.x, 0, m_rect.x, m_rect.y),
            &m_color
        );
    }
}