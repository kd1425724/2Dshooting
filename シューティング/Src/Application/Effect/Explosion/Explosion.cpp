#include "Explosion.h"

void C_Explosion::Init(Math::Vector2 pos)
{
	//座標
	m_pos = pos;
	
	m_scale = 2.0f;   // 最初小さく
	m_anim = 0;
	m_rect = { 48,48 };
	m_alive = true;
	m_alpha = 1;
}

void C_Explosion::Update()
{
	//アニメーション用
	m_anim += 0.3f;
	//マックス以上になったら,4コマなら4
	if (m_anim >= AnimMax)
	{
		//終わったら消去
		Kill();
		return;
	}

}

void C_Explosion::Draw()
{
	if (!m_alive)return;

	std::shared_ptr<KdTexture> tex = m_tex.lock();

	if (tex)
	{
		//行列
		m_scalemat = Math::Matrix::CreateScale(m_scale);
		m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
		m_mat = m_scalemat * m_transmat;


		Math::Rectangle rect = { (int)m_anim * (long)m_rect.x,0,(long)m_rect.x,(long)m_rect.y };
		Math::Color color = { 1,1,1,m_alpha };

		// 実際はお前の環境の描画APIに合わせて書く
		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_mat);
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(tex.get(), 0, 0, &rect, &color);
	}
}

void C_Explosion::Release()
{

}
