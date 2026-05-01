#include "Explosion.h"
// 必要なら描画用API include

void C_Explosion::Init(Math::Vector2 pos)
{
	//座標
	m_pos = pos;
	
	m_timer = 0;
	m_scale = 1.0f;   // 最初小さく
	m_anim = StartAnim;
	m_rect = { 64,64 };
	m_alive = true;
	m_alpha = 1;
}

void C_Explosion::Update()
{
	m_timer++;

	// 徐々に大きくする
	//m_scale += 0.05f;

	// フェードアウト的なこともここでやれる（今は省略）
	 
	//アニメーション用
	m_anim += 0.3f;
	//マックス以上になったら,4コマなら4
	if (m_anim >= AnimMax)
	{
		//終わったら消去
		Kill();
	}

	//行列
	m_scalemat = Math::Matrix::CreateScale(m_scale);
	m_transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scalemat * m_transmat;
}

void C_Explosion::Draw()
{
	std::shared_ptr<KdTexture> tex = m_tex.lock();

	if (tex)
	{
		// 仮：円とかテクスチャ描画
		// 例（擬似コード）:
		// DrawCircle(m_pos, m_scale * 20);
		Math::Rectangle rect = { (int)m_anim * (long)m_rect.x,0,(long)m_rect.x,(long)m_rect.y };
		Math::Color color = { 1,1,1,m_alpha };

		// 実際はお前の環境の描画APIに合わせて書く
		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_mat);
		KdShaderManager::GetInstance().m_spriteShader.DrawTex(tex.get(), 0, 0, &rect, &color);
	}
}