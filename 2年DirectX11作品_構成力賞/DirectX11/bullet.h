//=============================================================================
//
// 弾処理 [bullet.h]
// Author : Yanagisawa Yuta
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BULLET_MAX		(10)		// バレットのMax数
#define BULLET_SPEED	(10.0f)		// バレットの移動スピード


// バレット構造体
struct BULLET
{
	D3DXMATRIX				mtxWorld;
	bool					use;	// true:使っている  false:未使用
	D3DXVECTOR3				pos;	// バレットの座標
	D3DXVECTOR3				move;	// バレットの移動量
	float					frame;	// フレーム数
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

BULLET *GetBullet(void);
void SetBullet(D3DXVECTOR3 pos);

