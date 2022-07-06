#include "EV_GetItem.h"

void EV_GetItem::Initialize(void)
{
	Effect_Vertex::Initialize();

	for (int i = 0; i < GetVERTEXNUMMAX(); i++) {
		//m_Vertexes[i].pos = D3DXVECTOR2()
	}
}

void EV_GetItem::Finalize(void)
{
	Effect_Vertex::Finalize();
}

void EV_GetItem::Update(void)
{
}

void EV_GetItem::Draw(void)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	m_pVertex = (VERTEX_3D*)msr.pData;


}
