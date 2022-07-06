//---------------------------------------------
//	タイマー計測	[GO_Timer.cpp]	Author: Yanagisawa
//---------------------------------------------
// 1桁目～小数点第二位までの表示
//  
//---------------------------------------------
#include "GO_Timer.h"

void GO_Timer::Initialize(void)
{
	//テクスチャロード----------------
	Number_Texture = LoadTexture(TEX_NAME);

	//-------------初期化-------------
	//１桁目
	{
		Timer_Vertex.alpha = 1.0f;
		Timer_Vertex.counter = 0;
		Timer_Vertex.pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		Timer_Vertex.size = D3DXVECTOR2(75, 75);
		Timer_Vertex.u = 0.0f;
		Timer_Vertex.v = 0.0f;
		Timer_Vertex.use = true;
	}

	//小数点第1位
	{
		Timer_Second.pos = D3DXVECTOR2((SCREEN_WIDTH / 2) + 100.0f, SCREEN_HEIGHT / 2);
		Timer_Second.size = D3DXVECTOR2(75, 75);
		Timer_Second.u = 0.0f;
		Timer_Second.v = 0.0f;
	}

	//小数点第2位
	{
		Timer_Third.pos = D3DXVECTOR2((SCREEN_WIDTH / 2) + 200.0f, SCREEN_HEIGHT / 2);
		Timer_Third.size = D3DXVECTOR2(75, 75);
		Timer_Third.u = 0.0f;
		Timer_Third.v = 0.0f;
	}
}

void GO_Timer::Finalize(void)
{
}

void GO_Timer::Update(void)
{
	//１桁目
	FirstNum();

	//小数点第1位
	SecondNum();

	//小数点第2位
	ThirdNum();
}

void GO_Timer::Draw(void)
{
	if (Timer_Vertex.use == false)return;

	//１桁目
	DrawSpriteColor(Number_Texture, Timer_Vertex.pos.x, Timer_Vertex.pos.y,
		Timer_Vertex.size.x, Timer_Vertex.size.y,
		Timer_Vertex.u, Timer_Vertex.v, NUMBER_WIDTH, NUMBER_HEIGHT,
		D3DXCOLOR(1.0f,1.0f,1.0f, Timer_Vertex.alpha));

	//小数点第1位
	DrawSpriteColor(Number_Texture, Timer_Second.pos.x, Timer_Second.pos.y,
		Timer_Second.size.x, Timer_Second.size.y,
		Timer_Second.u, Timer_Second.v, NUMBER_WIDTH, NUMBER_HEIGHT,
		D3DXCOLOR(1.0f,1.0f,1.0f, Timer_Vertex.alpha));

	//小数点第2位
	DrawSpriteColor(Number_Texture, Timer_Third.pos.x, Timer_Third.pos.y,
		Timer_Third.size.x, Timer_Third.size.y,
		Timer_Third.u, Timer_Third.v, NUMBER_WIDTH, NUMBER_HEIGHT,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, Timer_Vertex.alpha));
}

void GO_Timer::FirstNum(void)
{
	if (Timer_Vertex.use == false)return;

	//１秒たったら
	if (Timer_Vertex.counter >= 600) {

		//納豆まぜまぜ終了
		Timer_Vertex.counter = 0;
		Timer_Vertex.use = false;
	}
	else {
		Timer_Vertex.counter++;
	}

//---------------------------------------------
//	uv値の設定
//	1 秒 = 60 フレーム　ー＞　10秒 = 600フレーム
//---------------------------------------------

	int cnt = ((600 - Timer_Vertex.counter) / 60);

	//数値変わる瞬間点滅
	Timer_Vertex.alpha = ((600 - Timer_Vertex.counter) % 60) / 10;

	//いつものアニメーションUV設定
	Timer_Vertex.u = NUMBER_WIDTH * (cnt % NUMBER_X);
	Timer_Vertex.v = NUMBER_HEIGHT * (cnt / NUMBER_Y);
}

void GO_Timer::SecondNum(void)
{
//---------------------------------------------
// 	   cnt	について
//---------------------------------------------
//	0.1秒	=	よくわからない。
//	なら、1秒の処理を10倍の速さでやればよくね
//---------------------------------------------
	int cnt = ((600 - Timer_Vertex.counter) / 6) % 10;


	Timer_Second.u = NUMBER_WIDTH * (cnt % NUMBER_X);
	Timer_Second.v = NUMBER_HEIGHT * (cnt / NUMBER_Y);
}

void GO_Timer::ThirdNum(void)
{
//---------------------------------------------
// 	   cnt	について
//---------------------------------------------
//	0.01秒	=	よくわからない。
//	なら、0.1秒の処理を10倍の速さでやればよくね
//---------------------------------------------
	int cnt = (int)((600 - Timer_Vertex.counter) / (6.0f /10.0f) ) % 10;

	Timer_Third.u = NUMBER_WIDTH * (cnt % NUMBER_X);
	Timer_Third.v = NUMBER_HEIGHT * (cnt / NUMBER_Y);
}
