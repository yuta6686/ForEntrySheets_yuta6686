#include "E_AddTime.h"

void E_AddTime::Initialize(void)
{
	m_TexIndex = LoadTexture(m_TexName);

	m_Vertex.pos = D3DXVECTOR2(0.0f, 0.0f);
	m_Vertex.size = D3DXVECTOR2(480.0f, 270.0f);
	m_Vertex.alpha = 2.0f;
	m_Vertex.use = false;
}

void E_AddTime::Finalize(void)
{
}

void E_AddTime::Update(void)
{
	if (m_Vertex.alpha <= 0.0f) {
		m_Vertex.alpha = 0.0f;
		m_Vertex.use = false;
	}
	else {
		m_Vertex.alpha -= DECLEASE_ALPHA;
		m_Vertex.size.x += ZOOM_VALUE;
		m_Vertex.size.y += ZOOM_VALUE;

		m_Vertex.pos.x += ZOOM_VALUE;
	}
}

void E_AddTime::Draw(void)
{
	if (m_Vertex.use == false)return;

	SetBlendState(BLEND_MODE_ADD);

	
	DrawSpriteColor(m_TexIndex, m_Vertex.pos.x, m_Vertex.pos.y,
		m_Vertex.size.x, m_Vertex.size.y, 1.0f, 1.0f, 1.0f, 1.0f,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Vertex.alpha));

	SetBlendState(BLEND_MODE_ALPHABLEND);
}
