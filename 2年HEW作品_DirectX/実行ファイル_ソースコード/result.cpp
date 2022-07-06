//=============================================================================
//
// リザルト画面処理 [result.cpp]
// Author : 
//
//=============================================================================

#include "main.h"
#include "result.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include <cmath>
#include "sound.h"
#include "E_Prizum.h"
#include "GO_SS_Timer.h"



//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define SCREEN_WIDTH	(1920 )				// ウインドウの幅
#define SCREEN_HEIGHT	(1080 )				// ウインドウの高さ

#define SCEREN_WIDTH_HURF SCREEN_WIDTH / 2
#define SCEREN_HEIGHT_HURF SCREEN_HEIGHT / 2

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//	サウンド用のインデックス
static int g_SoundIndex = 0;

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int	g_TextureNo;	// テクスチャ情報
static int Number_Texture;	// 番号
static int g_cursor;		//カーソル
static int g_UI[3];			//UI

static float g_AlphaRot = 0.0f;


struct VERTEX_NOMAL Result_Ui;

D3DXVECTOR2 Mouse_pos(0.0f, 0.0f);

float Result_Uipos1;
float Result_Uipos3;

E_Prizum g_Prizum;
GO_SS_Timer g_Timer;

bool g_TimerOnce;

int g_Time;

void SetTime(int time) { g_Time = time; }

static VERTEX_ALPHA_ANIMATION_USE r_Timer_Vertex;	//1桁目


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResult(void)
{
	StopSoundAll();

	ShowCursor(false);

	//テクスチャロード----------------
	//Number_Texture = LoadTexture("data/TEXTURE/number2.png");
	g_TextureNo = LoadTexture("data/TEXTURE/result_back.png");
	g_cursor = LoadTexture("data/TEXTURE/cursor.png");

	g_UI[0] = LoadTexture("data/TEXTURE/result_button_title.png");
	g_UI[1] = LoadTexture("data/TEXTURE/UI2.png");
	g_UI[2] = LoadTexture("data/TEXTURE/result_button_next.png");



	//-------------初期化-------------
	////////==数字==////////
	//１桁目
	{
		r_Timer_Vertex.alpha = 0.0f;
		r_Timer_Vertex.counter = 0;
		r_Timer_Vertex.pos = D3DXVECTOR2(SCREEN_WIDTH /2.0f - 75.0f, SCREEN_HEIGHT / 2.0f );
		r_Timer_Vertex.size = D3DXVECTOR2(200.0f, 200.0f);
		r_Timer_Vertex.u = 0.0f;
		r_Timer_Vertex.v = 0.0f;
		r_Timer_Vertex.use = true;
	}

	
	g_Timer.SetVertex(r_Timer_Vertex);


	////小数点第1位
	//{
	//	Timer_Second.pos = D3DXVECTOR2(Timer_Vertex.pos.x + 100.0f, SCREEN_HEIGHT / 10);
	//	Timer_Second.size = D3DXVECTOR2(75, 75);
	//	Timer_Second.u = 0.0f;
	//	Timer_Second.v = 0.0f;
	//}

	////小数点第2位
	//{
	//	Timer_Third.pos = D3DXVECTOR2(Timer_Vertex.pos.x + 200.0f, SCREEN_HEIGHT / 10);
	//	Timer_Third.size = D3DXVECTOR2(75, 75);
	//	Timer_Third.u = 0.0f;
	//	Timer_Third.v = 0.0f;
	//}

	////////==UI==////////
	Result_Ui.pos = D3DXVECTOR2(SCEREN_WIDTH_HURF, SCREEN_HEIGHT * 0.75);
	Result_Ui.size = D3DXVECTOR2(480.0f, 160.0f);

	Result_Uipos1 = Result_Ui.pos.x - 500.0f;
	Result_Uipos3 = Result_Ui.pos.x + 500.0f;

	g_AlphaRot = 0.0f;
	

	//BGM処理
	g_SoundIndex = LoadSound("data/BGM/result.wav");

	//	第一引数ー＞グローバル変数、第二引数ー＞0～1までの数値
	//で音量が設定できます
	SetVolume(g_SoundIndex, 0.5f);

	PlaySound(g_SoundIndex, 256);

	g_Prizum.Initialize();

	g_Timer.Initialize();
	g_Timer.SetSize(r_Timer_Vertex.size);
	g_Timer.SetPos(r_Timer_Vertex.pos);

	g_TimerOnce = false;

	return S_OK;

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{
	ShowCursor(true);

	StopSound(g_SoundIndex);

	g_Prizum.Finalize();

	g_Timer.Finalize();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResult(void)
{
	Mouse_pos.x = GetMousePosX();
	Mouse_pos.y = GetMousePosY();

	if (IsMouseLeftTriggered())
	{
		if (Mouse_pos.y >= Result_Ui.pos.y - Result_Ui.size.y / 2 &&
			Mouse_pos.y <= Result_Ui.pos.y + Result_Ui.size.y / 2)
		{
			if (Mouse_pos.x >= Result_Uipos1 - Result_Ui.size.x / 2 &&
				Mouse_pos.x <= Result_Uipos1 + Result_Ui.size.x / 2)
			{
				SceneTransition(SCENE_TITLE);
				g_Prizum.SetEffect(Mouse_pos);
			}

			if (Mouse_pos.x >= Result_Ui.pos.x - Result_Ui.size.x / 2 &&
				Mouse_pos.x <= Result_Ui.pos.x + Result_Ui.size.x / 2)
			{
				SceneTransition(SCENE_TITLE);
				g_Prizum.SetEffect(Mouse_pos);
			}

			if (Mouse_pos.x >= Result_Uipos3 - Result_Ui.size.x / 2 &&
				Mouse_pos.x <= Result_Uipos3 + Result_Ui.size.x / 2)
			{
				AddStageNum();
				SceneTransition(SCENE_GAME);
				g_Prizum.SetEffect(Mouse_pos);
			}

		}

	}

	if (g_AlphaRot >= D3DX_PI * 2.0f)
	{
		g_AlphaRot = 0.0f;
	}
	else 
	{
		g_AlphaRot += 0.05f;
	}

	g_Timer.SetSize(
		D3DXVECTOR2(r_Timer_Vertex.size.x + ((sinf(g_AlphaRot)+ 0.5f)*50.0f),
			r_Timer_Vertex.size.y + ((sinf(g_AlphaRot) + 0.5f) * 50.0f)));

	//if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE)
	//{
	//	SceneTransition(SCENE_TITLE);
	//}

	if (GetKeyboardTrigger(DIK_G)) 
	{
		g_Timer.AddTimer(10);
		g_Timer.Update();
	}

	//g_Prizum.Update();
	if (!g_TimerOnce) 
	{
		g_Timer.SetTimerCounter(g_Time);
		g_Timer.Update();
		g_TimerOnce = true;
	}
	

	
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResult(void)
{
	//１枚のポリゴンの頂点とテクスチャ座標を設定
	DrawSpriteLeftTop(g_TextureNo, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

	////////１桁目
	//DrawSprite(Number_Texture, Timer_Vertex.pos.x, Timer_Vertex.pos.y,
	//	Timer_Vertex.size.x, Timer_Vertex.size.y,
	//	Timer_Vertex.u, Timer_Vertex.v, NUMBER_WIDTH, NUMBER_HEIGHT);

	//////小数点第1位
	//DrawSprite(g_TextureNo, Timer_Second.pos.x, Timer_Second.pos.y,
	//	Timer_Second.size.x, Timer_Second.size.y,
	//	Timer_Second.u, Timer_Second.v, NUMBER_WIDTH, NUMBER_HEIGHT);

	//////小数点第2位
	//DrawSprite(g_TextureNo, Timer_Third.pos.x, Timer_Third.pos.y,
	//	Timer_Third.size.x, Timer_Third.size.y,
	//	Timer_Third.u, Timer_Third.v, NUMBER_WIDTH, NUMBER_HEIGHT);

	////UI
	DrawSpriteColor(g_UI[0], Result_Uipos1, Result_Ui.pos.y,
		Result_Ui.size.x, Result_Ui.size.y,
		0.0f, 0.0f, 1.0f, 1.0f,D3DXCOLOR(1.0f,1.0f,1.0f, sinf(g_AlphaRot) + 0.75f));


	//DrawSprite(g_UI[1], Result_Ui.pos.x, Result_Ui.pos.y,
	//	Result_Ui.size.x + 100.0f, Result_Ui.size.y,
	//	0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteColor(g_UI[2], Result_Uipos3, Result_Ui.pos.y,
		Result_Ui.size.x, Result_Ui.size.y,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, sinf(g_AlphaRot)+0.75f));

	//// マウスカーソル
	DrawSprite(g_cursor, Mouse_pos.x, Mouse_pos.y,
		75.0f, 75.0f,
		0.0f, 0.0f, 1.0f, 1.0f);

	g_Prizum.Draw();
	
	g_Timer.Draw();
}