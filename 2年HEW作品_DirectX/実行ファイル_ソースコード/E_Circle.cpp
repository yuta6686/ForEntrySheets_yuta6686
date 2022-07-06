#include "E_Circle.h"

void E_Circle::Initialize(void)
{
	m_TexIndex = LoadTexture(m_pTexName);

	m_Vertex.pos = D3DXVECTOR2(0.0f, 0.0f);
	m_Vertex.size = D3DXVECTOR2(0.0f, 0.0f);
	m_Vertex.alpha = 1.0f;
	m_Vertex.frame = 0;
	m_Vertex.use = false;

	m_AddSize = 5.0f;
}

void E_Circle::Finalize(void)
{
}

void E_Circle::Update(void)
{
	if (m_Vertex.use) 
	{
		if (m_Vertex.alpha <= 0.0f) {
			m_Vertex.alpha = 0.0f;
			m_AddSize = 5.0f;
			m_Vertex.use = false;
		}
		else {
			m_Vertex.alpha -= 0.06f;
			m_AddSize += SIZE_ACCELERATION;
			m_Vertex.size.y += m_AddSize;
		}
	}

	m_Vertex.size.x = m_Vertex.size.y;
}

void E_Circle::Draw(void)
{
	SetBlendState(BLEND_MODE_ADD);

	if (m_Vertex.use) 
	{
		DrawSpriteColor(m_TexIndex, m_Vertex.pos.x, m_Vertex.pos.y,
			m_Vertex.size.x, m_Vertex.size.y, 1.0f, 1.0f, 1.0f, 1.0f,
			D3DXCOLOR(1.0f,1.0f,1.0f,m_Vertex.alpha));
	}

	SetBlendState(BLEND_MODE_ALPHABLEND);
}
