//---------------------------------------------
//	タイマー計測	[GO_Timer.h]	Author: Yanagisawa
//---------------------------------------------
// 1桁目～小数点第二位までの表示
//  
//---------------------------------------------
#pragma once

#include"GameObject.h"

class GO_Timer:
	public GameObject
{
public:
	// GameObject を介して継承されました
	virtual void Initialize(void) override;
	virtual void Finalize(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;
	virtual int GetGameScene(void) override { return GAME_SCENE;};


	//	GameScene用のやつ
	bool GetTimerUse(void) { return Timer_Vertex.use; }
	void SetTimerUse(bool flag) { Timer_Vertex.use = flag; }

private:
//--------------------------------------------------------
//	メンバ変数
//--------------------------------------------------------

	//	Texture用変数
	char TEX_NAME[128] = "data/TEXTURE/number2.png";
	int Number_Texture;

	//	GameScene用変数
	const int GAME_SCENE = GAMESCENE_GAME_TEST;

	//	UV用の変数
	const int NUMBER_X = 4;
	const int NUMBER_Y = 4;
	const float NUMBER_WIDTH = 1.0f / (float)NUMBER_X;
	const float NUMBER_HEIGHT = 1.0f / (float)NUMBER_Y;

	//頂点データ
	VERTEX_ALPHA_ANIMATION_USE Timer_Vertex;	//1桁目
	VERTEX_UV Timer_Second;						//小数点第一位
	VERTEX_UV Timer_Third;						//小数点第二位

//--------------------------------------------------------
//	メンバ関数
//--------------------------------------------------------
//	What --> 一桁目　～　小数点第二位までの更新処理
//	Why	 --> 整理のため
//--------------------------------------------------------
	void FirstNum(void);
	void SecondNum(void);
	void ThirdNum(void);
};

