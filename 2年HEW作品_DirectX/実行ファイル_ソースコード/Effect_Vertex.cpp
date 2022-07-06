#include "Effect_Vertex.h"

void Effect_Vertex::Initialize(void)
{
	ID3D11Device* pDevice = GetDevice();

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * NUM_VERTEX;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pDevice->CreateBuffer(&bd, NULL, &m_VertexBuffer);
}

void Effect_Vertex::Finalize(void)
{
	// 頂点バッファの解放
	if (m_VertexBuffer)
	{
		m_VertexBuffer->Release();
		m_VertexBuffer = NULL;
	}
}


