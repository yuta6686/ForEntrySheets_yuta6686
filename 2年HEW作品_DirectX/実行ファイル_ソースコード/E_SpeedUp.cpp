#include "E_SpeedUp.h"

void E_SpeedUp::Initialize(void)
{
	m_TexIndex = LoadTexture(m_pTexName);

	m_Vertex.pos = D3DXVECTOR2(0.0f, 0.0f);
	m_Vertex.size = D3DXVECTOR2(250.0f, 250.0f);
	m_Vertex.use = false;
	m_Vertex.alpha = 1.0f;
	m_Vertex.frame = 0;
	m_Vertex.u = m_Vertex.v = 0.0f;

	m_numTime = 0;

	IsMousePlace = false;
}

void E_SpeedUp::Finalize(void)
{
}

void E_SpeedUp::Update(void)
{
	if (m_Vertex.use) {
		if (m_Vertex.frame >= m_Xnum * m_Ynum)
		{
			m_Vertex.frame = 0;
			if (m_numTime >= 2) {
				m_numTime = 0;
				m_Vertex.use = false;
			}
			else {
				m_numTime++;
			}			
		}		
		else {
			m_Vertex.frame++;
		}

		m_Vertex.u = m_Vertex.frame % m_Xnum * m_Width;
		m_Vertex.v = m_Vertex.frame / m_Ynum * m_Height;
	}
}

void E_SpeedUp::Draw(void)
{
	SetBlendState(BLEND_MODE_ADD);

	if (m_Vertex.use) {
		DrawSpriteColor(m_TexIndex, m_Vertex.pos.x, m_Vertex.pos.y,
			m_Vertex.size.x, m_Vertex.size.y,
			m_Vertex.u, m_Vertex.v,
			m_Width, m_Height,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Vertex.alpha));
	}

	SetBlendState(BLEND_MODE_ALPHABLEND);
}
