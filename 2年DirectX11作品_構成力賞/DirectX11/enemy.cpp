//=============================================================================
//
// ポリゴン表示処理 [enemy.cpp]
// Author : Yanagisawa Yuta
// 
// サンプルとして残している
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "enemy.h"
#include "texture.h"
#include "model.h"
#include "light.h"
#include "player.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_MOVE		(5.0f)						// 移動量
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// 回転量


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static DX11_MODEL	g_Model;			// モデル読み込み
static ENEMY		g_Enemy[ENEMY_NUM];	// エネミー情報		
static float        g_Rot;				// キャラクターの向き

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(void)
{
	// 位置・回転・スケールの初期設定
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		g_Enemy[i].pos = D3DXVECTOR3(frand()*1000 - 500.0f, 35.0f, frand() * 1000 - 500.0f);
		g_Enemy[i].rot = D3DXVECTOR3(frand()*D3DX_PI, 0.0f, frand()*D3DX_PI);
		g_Enemy[i].scl = D3DXVECTOR3(3.0f, 3.0f, 3.0f);
		g_Enemy[i].dir = D3DXVECTOR3(frand() - 0.5f, 0.0f, frand() - 0.5f);
		g_Enemy[i].spd = 1.0f;
		g_Enemy[i].use = true;

		g_Enemy[i].size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

		//単位ベクトル化する
		D3DXVec3Normalize(&g_Enemy[i].dir, &g_Enemy[i].dir);

		D3DXVECTOR3 sPos = g_Enemy[i].pos;
		sPos.y = 0.0f;
		g_Enemy[i].idxShadow = CreateShadow(sPos, 100.0f, 100.0f);
	}

	//objモデルの読み込み
	LoadModel((char*)"data/MODEL/torus.obj", &g_Model);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	//objモデルの解放
	UnloadModel(&g_Model);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		//useフラグがオフの場合はスキップする
		if (g_Enemy[i].use == false)
			continue;

		//座標の更新
		g_Enemy[i].pos += g_Enemy[i].dir * g_Enemy[i].spd;

		//回転の更新
		g_Enemy[i].rot.x += 0.05f;
		g_Enemy[i].rot.y += 0.05f;

		if (g_Enemy[i].pos.x > 500.0f)
			g_Enemy[i].dir.x *= -1;

		if (g_Enemy[i].pos.x < -500.0f)
			g_Enemy[i].dir.x *= -1;

		if (g_Enemy[i].pos.z > 500.0f)
			g_Enemy[i].dir.z *= -1;

		if (g_Enemy[i].pos.z < -500.0f)
			g_Enemy[i].dir.z *= -1;

		//影の位置の更新
		D3DXVECTOR3 sPos = g_Enemy[i].pos;
		sPos.y = 0.0f;
		SetPositionShadow(g_Enemy[i].idxShadow, sPos);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		//useフラグがオフの場合はスキップする
		if (g_Enemy[i].use == false)
			continue;

		// ワールドマトリックスの初期化（単位行列を作る関数）
		D3DXMatrixIdentity(&g_Enemy[i].mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, g_Enemy[i].scl.x, g_Enemy[i].scl.y, g_Enemy[i].scl.z);
		D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxScl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[i].rot.y, g_Enemy[i].rot.x, g_Enemy[i].rot.z);
		D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, g_Enemy[i].pos.x, g_Enemy[i].pos.y, g_Enemy[i].pos.z);
		D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		SetWorldMatrix(&g_Enemy[i].mtxWorld);

		//objモデルの描画
		DrawModel(&g_Model);
	}
}


//=============================================================================
// エネミー情報を取得
//=============================================================================
ENEMY *GetEnemy(void)
{
	return g_Enemy;
}

