//=============================================================================
//
// 経験値処理 [ExperiencePoint.cpp]
// Author : Yanagisawa Yuta
//
// 説明：経験値のゲージ処理
// 
//=============================================================================
#include "ExperiencePoint.h"
#include "CoordinateTransformation.h"
#include "fade.h"
#include "result.h"
#include "game.h"

void ExperiencePoint::NextStage()
{

	
	if (m_EXP >= m_exp_max) 
	{
		m_EXP = 0;

		if (*GetStageNum() >= A_STAGE_NUM_MAX) {
			SetIsClear(true);
			SceneTransition(SCENE_RESULT);
			*GetStageNum() = 0;
		}
		else 
		{
			AddStageNum(1);
			ChangeSelectSkillState(true);
			m_Obj.size.x = 0.0f;
		}
		
	}

}

void ExperiencePoint::Init()
{
	m_exp_max = EXP_MAX_DEFAULT;

	//	ゲージの方
	{
		m_Obj.pos = D3DXVECTOR3(0.0f, 35.0f, 0.0f);
		m_Obj.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Obj.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Obj.vec = D3DXVECTOR3(10.0f, 0.0f, 0.0f);

		float scale = 2.5f;
		m_Obj.scl = D3DXVECTOR3(scale, scale, scale);
		m_Obj.size = D3DXVECTOR3(m_Exp_Gauge, 10.0f, 50.0f);
		m_Obj.idxShadow = 0;
		m_Obj.use = true;
	}

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &m_VertexBuffer);

	// 頂点バッファに値をセットする
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		vertex = (VERTEX_3D*)msr.pData;

		float width = m_Obj.size.x;
		float height = m_Obj.size.y;

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

		GetDeviceContext()->Unmap(m_VertexBuffer, 0);
	}

	//	MAXの方
	{
		m_Obj_EXPMAX.pos = D3DXVECTOR3(0.0f, 35.0f, 0.0f);
		m_Obj_EXPMAX.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Obj_EXPMAX.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Obj_EXPMAX.vec = D3DXVECTOR3(10.0f, 0.0f, 0.0f);

		float scale = 2.5f;
		m_Obj_EXPMAX.scl = D3DXVECTOR3(scale, scale, scale);
		m_Obj_EXPMAX.size = D3DXVECTOR3(EXP_GAUGE_XMAX, 10.0f, 50.0f);
		m_Obj_EXPMAX.idxShadow = 0;
		m_Obj_EXPMAX.use = true;
	}

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd2;
	ZeroMemory(&bd2, sizeof(bd2));
	bd2.Usage = D3D11_USAGE_DYNAMIC;
	bd2.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd2.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd2.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd2, NULL, &m_VertexBuffer_max);
	
	// 頂点バッファに値をセットする
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(m_VertexBuffer_max, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		vertex_max = (VERTEX_3D*)msr.pData;

		float width = m_Obj_EXPMAX.size.x;
		float height = m_Obj_EXPMAX.size.y;

		// 頂点座標の設定
		vertex_max[0].Position = D3DXVECTOR3(-width / 2.0f, 0.0f, 0.0f);
		vertex_max[1].Position = D3DXVECTOR3(-width / 2.0f, height, 0.0f);
		vertex_max[2].Position = D3DXVECTOR3(width / 2.0f, 0.0f, 0.0f);
		vertex_max[3].Position = D3DXVECTOR3(width / 2.0f, height, 0.0f);

		// 頂点カラーの設定
		vertex_max[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		vertex_max[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		vertex_max[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		vertex_max[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);


		// テクスチャ座標の設定
		vertex_max[0].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
		vertex_max[1].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		vertex_max[2].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		vertex_max[3].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		GetDeviceContext()->Unmap(m_VertexBuffer_max, 0);
	}

	m_texIndex = LoadTexture(m_pTexName);

	// マテリアル初期化
	ZeroMemory(&m_Material, sizeof(m_Material));
	m_Material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Alpha);

	// マテリアル初期化
	ZeroMemory(&m_Material2, sizeof(m_Material2));
	m_Material2.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Alpha);
}

void ExperiencePoint::Uninit()
{
	UnloadModel(&m_Model);

	if (m_VertexBuffer != NULL)
	{// 頂点バッファの解放
		m_VertexBuffer->Release();
		m_VertexBuffer = NULL;
	}

	
}

void ExperiencePoint::Update()
{
#ifdef _DEBUG	// デバッグ版の時だけAngleを表示する

	sprintf(&GetDebugStr()[strlen(GetDebugStr())], "経験値：%d", m_EXP);

	SetWindowText(GethWnd()[0], GetDebugStr());
#endif

	SetExpMax();

	float width = m_Obj.size.x;
	float height = m_Obj.size.y;

	vertex[0].Position = D3DXVECTOR3(-width / 2.0f, 0.0f, 0.0f);
	vertex[1].Position = D3DXVECTOR3(-width / 2.0f, height, 0.0f);
	vertex[2].Position = D3DXVECTOR3(width / 2.0f, 0.0f, 0.0f);
	vertex[3].Position = D3DXVECTOR3(width / 2.0f, height, 0.0f);

	m_Obj_EXPMAX.pos = m_Obj.pos;
}

void ExperiencePoint::Draw()
{
	//	ビルボードで表示
	{
		//	アルファテストを有効に
		SetAlphaTestEnable(true);

		// ライティングを無効
		SetLightEnable(false);

		//SetBlendState(BLEND_MODE_ADD);
		SetBlendState(BLEND_MODE_ALPHABLEND);


		D3DXMATRIX mtxView, mtxScale, mtxTranslate;

		// 頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

		// プリミティブトポロジ設定
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		if (m_Obj.use) {
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&m_Obj.mtxWorld);

			CAMERA* cam = GetCamera();

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

			//// スケールを反映
			//D3DXMatrixScaling(&mtxScale, m_Obj.size.x,m_Obj.size.y,m_Obj.size.z);

			////第1引数 ＝          第2引数      ＊    第3引数
			//D3DXMatrixMultiply(&m_Obj.mtxWorld, &m_Obj.mtxWorld, &mtxScale);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, m_Obj.pos.x,m_Obj.pos.y,m_Obj.pos.z);

			D3DXMatrixMultiply(&m_Obj.mtxWorld, &m_Obj.mtxWorld, &mtxTranslate);

			SetWorldMatrix(&m_Obj.mtxWorld);

			SetMaterial(m_Material);

			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_texIndex));

			GetDeviceContext()->Draw(4, 0);
		}


		GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer_max, &stride, &offset);

		// プリミティブトポロジ設定
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		if (m_Obj_EXPMAX.use) {
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&m_Obj_EXPMAX.mtxWorld);

			CAMERA* cam = GetCamera();

			// ビューマトリックスを取得
			D3DXMATRIX mtxView = cam->mtxView;

			m_Obj_EXPMAX.mtxWorld._11 = mtxView._11;
			m_Obj_EXPMAX.mtxWorld._12 = mtxView._21;
			m_Obj_EXPMAX.mtxWorld._13 = mtxView._31;
			m_Obj_EXPMAX.mtxWorld._21 = mtxView._12;
			m_Obj_EXPMAX.mtxWorld._22 = mtxView._22;
			m_Obj_EXPMAX.mtxWorld._23 = mtxView._32;
			m_Obj_EXPMAX.mtxWorld._31 = mtxView._13;
			m_Obj_EXPMAX.mtxWorld._32 = mtxView._23;
			m_Obj_EXPMAX.mtxWorld._33 = mtxView._33;

			//// スケールを反映
			//D3DXMatrixScaling(&mtxScale, m_Obj.size.x,m_Obj.size.y,m_Obj.size.z);

			////第1引数 ＝          第2引数      ＊    第3引数
			//D3DXMatrixMultiply(&m_Obj.mtxWorld, &m_Obj.mtxWorld, &mtxScale);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, m_Obj_EXPMAX.pos.x, m_Obj_EXPMAX.pos.y, m_Obj_EXPMAX.pos.z);

			D3DXMatrixMultiply(&m_Obj_EXPMAX.mtxWorld, &m_Obj_EXPMAX.mtxWorld, &mtxTranslate);

			SetWorldMatrix(&m_Obj_EXPMAX.mtxWorld);

			SetMaterial(m_Material2);

			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_texIndex));

			GetDeviceContext()->Draw(4, 0);
		}
	}

	SetBlendState(BLEND_MODE_ALPHABLEND);

	// ライティングを有効に
	SetLightEnable(true);

	// αテストを無効に
	SetAlphaTestEnable(false);
}
