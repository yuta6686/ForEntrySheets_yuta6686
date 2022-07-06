//=============================================================================
//
// 地面処理 [enemy.h]
// Author : Yanagisawa Yuta
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "GameObject.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMY_NUM 10

struct ENEMY
{
	D3DXVECTOR3		pos;		// 位置
	D3DXVECTOR3		rot;		// 向き(回転)
	D3DXVECTOR3		scl;		// 大きさ(スケール)
	D3DXVECTOR3		dir;		// 移動方向
	float			spd;		// 移動スピード
	bool			use;		// 表示フラグ

	int				idxShadow;	// 影の識別子

	D3DXVECTOR3     size;		// 当たり判定用サイズ

	D3DXMATRIX		mtxWorld;	// ワールドマトリックス
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

ENEMY *GetEnemy(void);

