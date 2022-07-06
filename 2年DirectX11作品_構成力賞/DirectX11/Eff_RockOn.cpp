//=============================================================================
//
// エネミーへロックオンするエフェクト [Eff_RockOn.cpp]
// Author : Yanagisawa Yuta
//
//=============================================================================
#include "Eff_RockOn.h"

static ID3D11Buffer* g_VertexBuffer = NULL;	// 頂点バッファ

void Eff_RockOn::Init()
{
	m_TexIndex = LoadTexture((char*)"data/TEXTURE/rockOn1.png");
	
	float width = 400.0f;
	float height = 400.0f;

	
	m_Obj.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Obj.scl = D3DXVECTOR3(width, height, 0.0f);
	m_Obj.use = false;
	
	
	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	g_VertexBuffer = NULL;

	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);

	// 頂点バッファに値をセットする
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;



		// 頂点座標の設定
		vertex[0].Position = D3DXVECTOR3(-width / 2.0f, 0.0f, 0.0f);
		vertex[1].Position = D3DXVECTOR3(-width / 2.0f, height, 0.0f);
		vertex[2].Position = D3DXVECTOR3(width / 2.0f, 0.0f, 0.0f);
		vertex[3].Position = D3DXVECTOR3(width / 2.0f, height, 0.0f);

		// 頂点カラーの設定
		vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		vertex[2].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	}

	// マテリアル初期化
	ZeroMemory(&m_Material, sizeof(m_Material));
	m_Material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

}

void Eff_RockOn::Uninit()
{
	if (g_VertexBuffer != NULL)
	{// 頂点バッファの解放
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

void Eff_RockOn::Update()
{

}

void Eff_RockOn::Draw()
{
	// αテストを有効に
	SetAlphaTestEnable(true);

	// ライティングを無効
	SetLightEnable(false);

	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	{
		if (m_Obj.use == false)return;

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_Obj.mtxWorld);

		CAMERA* cam = GetCamera();

		// ポリゴンを正面に向ける
#if 0
			// ビューマトリックスの逆行列を取得
		g_Bullet[i].mtxWorld = cam->mtxInvView;
		g_Bullet[i].mtxWorld._41 = 0.0f;
		g_Bullet[i].mtxWorld._42 = 0.0f;
		g_Bullet[i].mtxWorld._43 = 0.0f;
#else
			// ビューマトリックスを取得
		D3DXMATRIX mtxView = cam->mtxView;

		m_Obj.mtxWorld._11 = mtxView._11;
		m_Obj.mtxWorld._12 = mtxView._21;
		m_Obj.mtxWorld._13 = mtxView._31;
		m_Obj.mtxWorld._21 = mtxView._12;
		m_Obj.mtxWorld._22 = mtxView._22;
		m_Obj.mtxWorld._23 = mtxView._32;
		m_Obj.mtxWorld._31 = mtxView._13;
		m_Obj.mtxWorld._32 = mtxView._23;
		m_Obj.mtxWorld._33 = mtxView._33;
#endif


		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, m_Obj.pos.x,
			m_Obj.pos.y,
			m_Obj.pos.z);
		D3DXMatrixMultiply(&m_Obj.mtxWorld, &m_Obj.mtxWorld, &mtxTranslate);


		// ワールドマトリックスの設定
		SetWorldMatrix(&m_Obj.mtxWorld);

		// マテリアル設定
		SetMaterial(m_Material);

		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_TexIndex));

		// ポリゴンの描画
		GetDeviceContext()->Draw(4, 0);
	}
}

void Eff_RockOn::SetEffect()
{
	m_Obj.use = true;
	
}

void Eff_RockOn::SetEffect(D3DXVECTOR3 pos)
{
	m_Obj.use = true;
	m_Obj.pos = pos;	
}

void Eff_RockOn::SetEffect(bool IsStart)
{

}
