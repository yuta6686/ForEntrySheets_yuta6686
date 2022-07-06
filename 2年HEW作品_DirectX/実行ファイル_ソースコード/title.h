//=============================================================================
//
// タイトル画面処理 [title.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define PLAYER_X_NUM 5
#define PLAYER_Y_NUM 4

#define PLAYER_WIDTH  (1.0f/ PLAYER_X_NUM)
#define PLAYER_HEIGHT (1.0f/ PLAYER_Y_NUM)

#define SALARRYMAN_H 93.75
#define SALARRYMAN_W 93.8
#define GRAVITY_NUM 9.8


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
void Action(int ActionScene);


