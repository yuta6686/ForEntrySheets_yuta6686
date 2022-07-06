#include "E_Prizum.h"

void E_Prizum::Initialize(void)
{
	m_TexIndex = LoadTexture(m_TexName);

	m_Vertex.pos = D3DXVECTOR2(0.0f, 0.0f);
	m_Vertex.size = D3DXVECTOR2(100.0f, 100.0f);
	m_Vertex.use = false;
	m_Vertex.alpha = 1.0f;
	m_Vertex.frame = 0;
	m_Vertex.u = m_Vertex.v = 0.0f;
	
	IsMousePlace = false;
}

void E_Prizum::Finalize(void)
{
}

void E_Prizum::Update(void)
{
	if (m_Vertex.use) {
		if (m_Vertex.frame >= m_Xnum * m_Ynum)
		{
			m_Vertex.size.x = 100.0f;
			m_Vertex.size.y = 100.0f;

			m_Vertex.frame = 0;
			m_Vertex.use = false;
		}
		else if (m_Vertex.frame == 1) {

			m_Vertex.frame++;

			if (IsMousePlace) {
				m_Vertex.pos.x = GetMousePosX();
				m_Vertex.pos.y = GetMousePosY();
			}

			
		}
		else {
			m_Vertex.frame++;

			m_Vertex.size.x *= 1.05f;
			m_Vertex.size.y *= 1.05f;
		}

		m_Vertex.u = m_Vertex.frame % m_Xnum * m_Width;
		m_Vertex.v = m_Vertex.frame / m_Ynum * m_Height;
	}
	
}

void E_Prizum::Draw(void)
{
	if (m_Vertex.use) {
		DrawSpriteColor(m_TexIndex,m_Vertex.pos.x, m_Vertex.pos.y,
			m_Vertex.size.x, m_Vertex.size.y,
			m_Vertex.u, m_Vertex.v,
			m_Width, m_Height,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Vertex.alpha));
	}
}
