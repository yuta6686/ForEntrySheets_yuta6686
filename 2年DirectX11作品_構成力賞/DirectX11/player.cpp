//=============================================================================
//
// ポリゴン表示処理 [player.cpp]
// Author : YanagisawaYuta
// サンプルとして残す
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "player.h"
#include "texture.h"
#include "model.h"
#include "light.h"
#include "bullet.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************



struct KEYFRAME {
	D3DXVECTOR3 rot;
	int key;
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static DX11_MODEL	g_Model;	// モデル読み込み

static DX11_MODEL	g_Model_Miku_Body;
static DX11_MODEL	g_Model_Miku_ArmR;
static DX11_MODEL	g_Model_Miku_ArmL;

static PLAYER	g_Player;	// プレイヤー情報		
static PLAYER	g_MikuArmR;
static PLAYER	g_MikuArmL;

static float        g_Rot;		// キャラクターの向き
static float		g_Rot_x;
static float		g_ArmRot;
static float		g_PrePlayerPosY;

static int g_frame;

static KEYFRAME g_ArmAnimation[5] = {
	{{0.0f,0.0f,0.0f},0},
	{{1.0f,0.0f,0.0f},40},
	{{0.0f,0.0f,0.0f},80},
	{{-1.0f,0.0f,0.0f},120},
	{{0.0f,0.0f,0.0f},160},
};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	// 位置・回転・スケールの初期設定
	g_Player.pos = D3DXVECTOR3(0.0f, 35.0f, 0.0f);
	g_Player.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.scl = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
	g_Player.use = true;

	// 位置・回転・スケールの初期設定
	g_MikuArmR.pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
	g_MikuArmR.offset = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	g_MikuArmR.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MikuArmR.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_MikuArmR.use = true;
	

	// 位置・回転・スケールの初期設定
	g_MikuArmL.pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);
	g_MikuArmL.offset = D3DXVECTOR3(0.0f,-1.0f, 0.0f);
	g_MikuArmL.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MikuArmL.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_MikuArmL.use = true;



	//当たり判定用サイズの初期設定
	g_Player.size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

	//objモデルの読み込み
	LoadModel((char*)"data/MODEL/miku_01.obj", &g_Model);

	LoadModel((char*)"data/MODEL/miku_body.obj", &g_Model_Miku_Body);
	LoadModel((char*)"data/MODEL/miku_arm_r.obj", &g_Model_Miku_ArmR);
	LoadModel((char*)"data/MODEL/miku_arm_l.obj", &g_Model_Miku_ArmL);


	g_ArmRot = 0.1f;
	g_PrePlayerPosY = 0.0f;

	//影の設定
	D3DXVECTOR3 sPos = g_Player.pos;
	sPos.y = 0.0f;
	g_Player.idxShadow = CreateShadow(sPos, 100.0f, 100.0f);

	// 並行光源の設定（世界を照らす光）
	//LIGHT *pLight = NULL;
	//pLight = GetLightData(0);
	//pLight->Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);// 光の向き
	//pLight->Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);	// 光の色
	//pLight->Type = LIGHT_TYPE_DIRECTIONAL;					// 並行光源
	//pLight->Enable = false;									// このライトをON
	//SetLightData(0, pLight);									// これで設定している

	//// 点光源の設定
	//pLight = GetLightData(1);
	//pLight->Position = D3DXVECTOR4(0.0f,500.0f, 0.0f, 0.0f);
	//pLight->Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);// 光の向き
	//pLight->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 光の色
	//pLight->Attenuation = 1000.0f;							// 減衰距離
	//pLight->Type = LIGHT_TYPE_POINT;						// 並行光源
	//pLight->Enable = true;									// このライトをON
	//SetLightData(1, pLight);								// これで設定している

	

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	//objモデルの解放
	UnloadModel(&g_Model);
	UnloadModel(&g_Model_Miku_Body);
	UnloadModel(&g_Model_Miku_ArmL);
	UnloadModel(&g_Model_Miku_ArmR);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	CAMERA *cam = GetCamera();

	//移動速度の減衰処理
	g_Player.spd *= 0.9f;

	

	if (GetKeyboardPress(DIK_A) ||
		GetKeyboardPress(DIK_S) ||
		GetKeyboardPress(DIK_D) ||
		GetKeyboardPress(DIK_W)) {

		if (g_frame >= 160) {
			g_frame = 0;
		}
		else {
			g_frame++;
			
			for (int i = 0; i < 4; i++) {
				if (g_frame >= g_ArmAnimation[i].key &&
					g_frame <= g_ArmAnimation[i + 1].key) {
					D3DXVec3Lerp(&g_MikuArmL.rot, &g_ArmAnimation[0].rot,
						&g_ArmAnimation[4].rot, g_frame/160);
					
				}
			}
		}

		//D3DXVECTOR3 kekka, saisho, saigo;
		//媒介変数 t(0.0 ～ 1.0)
		//D3DXVec3Lerp(&kekka, &saisho, &saigo, t);

		

		/*if (g_MikuArmL.rot.x >= D3DX_PI / 2.0f) {
			g_ArmRot *= -1.0f;
		}
		if (g_MikuArmL.rot.x <= -D3DX_PI / 2.0f) {
			g_ArmRot *= -1.0f;
		}

		g_MikuArmL.rot.x += g_ArmRot;
		g_MikuArmR.rot.x -= g_ArmRot;*/


	}
	else {
		g_MikuArmL.rot.x *= 0.9f;
		g_MikuArmR.rot.x *= 0.9f;
	}

	if (GetKeyboardPress(DIK_A))
	{
		g_Player.spd = VALUE_MOVE;
		g_Rot = -D3DX_PI / 2;
	}
	if (GetKeyboardPress(DIK_D))
	{
		g_Player.spd = VALUE_MOVE;
		g_Rot = D3DX_PI / 2;
	}

	if (GetKeyboardPress(DIK_W))
	{
		g_Player.spd = VALUE_MOVE;
		g_Rot = 0.0f;
	}
	if (GetKeyboardPress(DIK_S))
	{
		g_Player.spd = VALUE_MOVE;
		g_Rot = D3DX_PI;
	}

	{	// 押した方向にプレイヤーを移動させる
		// 押した方向にプレイヤーを向かせている所
		g_Player.rot.y = g_Rot + cam->rot.y;

		g_Player.pos.x += sinf(g_Player.rot.y) * g_Player.spd;
		g_Player.pos.z += cosf(g_Player.rot.y) * g_Player.spd;

		
		g_Player.rot.x = g_Rot_x + cam->rot.x;

		g_Player.pos.y -= sinf(g_Player.rot.x) * g_Player.spd;
		
	}

	// カメラの注視点をプレイヤーの座標にしてみる
	cam->at = g_Player.pos;

	// カメラの視点をカメラのY軸回転に対応させている
	cam->pos.x = cam->at.x - sinf(cam->rot.y) * cam->len;
	cam->pos.z = cam->at.z - cosf(cam->rot.y) * cam->len;

	cam->pos.y = cam->at.y + sinf(cam->rot.x) * cam->len + g_PrePlayerPosY * 1.5f;
	//cam->pos.y = cam->at.y + cam->len;

	// 弾を撃つ
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		SetBullet(g_Player.pos);
	}

	//影の位置の更新
	D3DXVECTOR3 sPos = g_Player.pos;
	sPos.y = 0.0f;
	SetPositionShadow(g_Player.idxShadow, sPos);

//#ifdef _DEBUG	// デバッグ情報を表示する
//	char* str = GetDebugStr();
//	sprintf(&str[strlen(str)], " rotX:%.2f rotY:%.2f", g_Player.rot.x, g_Player.rot.y);
//
//#endif

	g_PrePlayerPosY = g_Player.pos.y;
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化（単位行列を作る関数）
	D3DXMatrixIdentity(&g_Player.mtxWorld);	

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, g_Player.scl.x, g_Player.scl.y, g_Player.scl.z);

	                   //第1引数 ＝          第2引数      ＊    第3引数
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(&g_Player.mtxWorld);

	//カリングなし
	SetCullingMode(CULL_MODE_NONE);


	DrawModel(&g_Model_Miku_Body);



	SetCullingMode(CULL_MODE_BACK);

	///***	子	***///

	// ワールドマトリックスの初期化（単位行列を作る関数）
	D3DXMatrixIdentity(&g_MikuArmL.mtxWorld);
	
	// スケールを反映
	D3DXMatrixScaling(&mtxScl, g_MikuArmL.scl.x, g_MikuArmL.scl.y, g_MikuArmL.scl.z);

	//第1引数 ＝          第2引数      ＊    第3引数
	D3DXMatrixMultiply(&g_MikuArmL.mtxWorld, &g_MikuArmL.mtxWorld, &mtxScl);

	//オフセット移動を行う
	D3DXMatrixTranslation(&mtxTranslate, g_MikuArmL.offset.x,g_MikuArmL.offset.y, g_MikuArmL.offset.z);
	D3DXMatrixMultiply(&g_MikuArmL.mtxWorld, &g_MikuArmL.mtxWorld, &mtxTranslate);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MikuArmL.rot.y, g_MikuArmL.rot.x, g_MikuArmL.rot.z);
	D3DXMatrixMultiply(&g_MikuArmL.mtxWorld, &g_MikuArmL.mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, g_MikuArmL.pos.x, g_MikuArmL.pos.y, g_MikuArmL.pos.z);
	D3DXMatrixMultiply(&g_MikuArmL.mtxWorld, &g_MikuArmL.mtxWorld, &mtxTranslate);

	//親の変換を反映させる
	D3DXMatrixMultiply(&g_MikuArmL.mtxWorld, &g_MikuArmL.mtxWorld, &g_Player.mtxWorld);

	// ワールドマトリックスの設定
	SetWorldMatrix(&g_MikuArmL.mtxWorld);

	//カリングなし
	SetCullingMode(CULL_MODE_NONE);

	DrawModel(&g_Model_Miku_ArmL);

	SetCullingMode(CULL_MODE_BACK);

	///***	子	***///

	// ワールドマトリックスの初期化（単位行列を作る関数）
	D3DXMatrixIdentity(&g_MikuArmR.mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, g_MikuArmR.scl.x, g_MikuArmR.scl.y, g_MikuArmR.scl.z);

	//第1引数 ＝          第2引数      ＊    第3引数
	D3DXMatrixMultiply(&g_MikuArmR.mtxWorld, &g_MikuArmR.mtxWorld, &mtxScl);

	//オフセット移動を行う
	D3DXMatrixTranslation(&mtxTranslate, g_MikuArmR.offset.x, g_MikuArmR.offset.y, g_MikuArmR.offset.z);
	D3DXMatrixMultiply(&g_MikuArmR.mtxWorld, &g_MikuArmR.mtxWorld, &mtxTranslate);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MikuArmR.rot.y, g_MikuArmR.rot.x, g_MikuArmR.rot.z);
	D3DXMatrixMultiply(&g_MikuArmR.mtxWorld, &g_MikuArmR.mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, g_MikuArmR.pos.x, g_MikuArmR.pos.y, g_MikuArmR.pos.z);
	D3DXMatrixMultiply(&g_MikuArmR.mtxWorld, &g_MikuArmR.mtxWorld, &mtxTranslate);

	//親の変換を反映させる
	D3DXMatrixMultiply(&g_MikuArmR.mtxWorld, &g_MikuArmR.mtxWorld, &g_Player.mtxWorld);

	// ワールドマトリックスの設定
	SetWorldMatrix(&g_MikuArmR.mtxWorld);

	//カリングなし
	SetCullingMode(CULL_MODE_NONE);

	DrawModel(&g_Model_Miku_ArmR);

	SetCullingMode(CULL_MODE_BACK);
}


//=============================================================================
// プレイヤー情報を取得
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player;
}

