//=============================================================================
//
// リザルト画面処理 [result.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"





//*****************************************************************************
// マクロ定義
//*****************************************************************************
static char TEX_NAME[128] = "data/TEXTURE/number2.png";

//static int Number_Texture;


//	GameScene用変数
//const int m_GameScene = GAMESCENE_GAME_TEST;

//	UV用の変数
const float NUMBER_X = 4.0f;
const float NUMBER_Y = 4.0f;
const float NUMBER_WIDTH = 1.0f / NUMBER_X;
const float NUMBER_HEIGHT = 1.0f / NUMBER_Y;







//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void FirstNum();
void SecondNum();
void ThirdNum();

void SetTime(int time);