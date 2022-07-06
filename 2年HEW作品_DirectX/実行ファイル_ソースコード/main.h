/*==============================================================================

   テクスチャの描画 [main.h]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf のwarning防止
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#include "dinput.h"
#include "mmsystem.h"

#pragma warning(pop)

#include "VertexParameter.h"

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "d3dx11.lib")	
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME			"GameWindow"			// ウインドウのクラス名
#define WINDOW_CAPTION		"HEW プロトタイプ"		// ウインドウのキャプション名

#define SCREEN_WIDTH	(1920 )				// ウインドウの幅
#define SCREEN_HEIGHT	(1080 )				// ウインドウの高さ

#define SCEREN_WIDTH_HURF SCREEN_WIDTH / 2
#define SCEREN_HEIGHT_HURF SCREEN_HEIGHT / 2

#define PI 3.14159265358979323846264338327950L
#define RADIAN PI/180.0



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
long GetMousePosX(void);
long GetMousePosY(void);

HWND* GethWnd(void);
char* GetDebugStr(void);

float frand();
float frand_pn();

//*****************************************************************************
// 定数
//*****************************************************************************
const int WALL_NUM_X = 16;
const int WALL_NUM_Y = 9;

const int STAGE_WALL_NUM_X = 300;     //1ステージの横マス数
const int STAGE_WALL_NUM_Y = 9;     //1ステージの縦マス数

const float WALL_WIDTH = SCREEN_WIDTH / (float)WALL_NUM_X;
const float WALL_HEIGHT = SCREEN_HEIGHT / (float)WALL_NUM_Y;

/*

#ifdef _DEBUG	// デバッグ版の時だけAngleを表示する
	sprintf(&GetDebugStr()[strlen(GetDebugStr())], "〇〇：%.2f", m_);

	SetWindowText(GethWnd()[0], GetDebugStr());
#endif

*/