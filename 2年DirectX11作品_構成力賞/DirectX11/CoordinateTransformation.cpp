//=============================================================================
//
// 座標変換処理まとめ [CoordinateTransformation.cpp]
// Author : Yanagisawa Yuta
//
//=============================================================================
#include "CoordinateTransformation.h"

void CoordinateTransformation(GAME_OBJECT* go) {

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

// ワールドマトリックスの初期化（単位行列を作る関数）
	D3DXMatrixIdentity(&go->mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, go->scl.x, go->scl.y, go->scl.z);

	//第1引数 ＝          第2引数      ＊    第3引数
	D3DXMatrixMultiply(&go->mtxWorld, &go->mtxWorld, &mtxScl);

	//オフセット移動を行う
	D3DXMatrixTranslation(&mtxTranslate, go->offset.x, go->offset.y, go->offset.z);
	D3DXMatrixMultiply(&go->mtxWorld, &go->mtxWorld, &mtxTranslate);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, go->rot.y, go->rot.x, go->rot.z);
	D3DXMatrixMultiply(&go->mtxWorld, &go->mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, go->pos.x, go->pos.y, go->pos.z);
	D3DXMatrixMultiply(&go->mtxWorld, &go->mtxWorld, &mtxTranslate);

	//親の変換を反映させる
	//D3DXMatrixMultiply(&go->mtxWorld, &go->mtxWorld, &g_Player.mtxWorld);

	// ワールドマトリックスの設定
	SetWorldMatrix(&go->mtxWorld);
}