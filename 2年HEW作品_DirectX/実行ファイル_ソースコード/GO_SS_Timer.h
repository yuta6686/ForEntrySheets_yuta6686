#pragma once
#include "GameObject.h"
#include "E_Prizum.h"
#include "E_AddTime.h"
#include "E_Circle.h"

class GO_SS_Player;

class GO_SS_Timer :
    public GameObject
{
private:
	static const int TIMER_LIMIT = 6000;
public:
	// GameObject を介して継承されました
	virtual void Initialize(void) override;

	virtual void Finalize(void) override;

	virtual void Update(void) override;
	
	virtual void Draw(void) override;
	
	virtual int GetGameScene(void) override { return m_GameScene; };


	//	GameScene用のやつ
	bool GetTimerUse(void) { return Timer_Vertex.use; }
	void SetTimerUse(bool flag) { Timer_Vertex.use = flag; }

	int GetTimerCounter(void) { return Timer_Vertex.counter; }
	void SetTimerCounter(int count) { Timer_Vertex.counter = count; }


	void SetVertex(VERTEX_ALPHA_ANIMATION_USE info) { Timer_Vertex = info; }
  	void AddTimer(int value) { 
		if (Timer_Vertex.counter <= value * 60) {
			Timer_Vertex.counter = 0;
		}
		else {
			Timer_Vertex.counter -= value * 60;
		}
		
	}
	

	void SetEffect() { 
		m_Eff.SetEffectNoMouse( D3DXVECTOR2(Timer_TenDigits.pos.x + 200.0f, Timer_TenDigits.pos.y),300.0f);
		m_AddTime.SetEffectNoMouse(D3DXVECTOR2(Timer_TenDigits.pos.x, Timer_TenDigits.pos.y), 300.0f);	
	}

	void SetEffect(D3DXVECTOR2 pos) 
	{
		SetEffect();
		m_Circle.SetEffectNoMouse(pos,100.0f);
		m_Circle_001.SetEffectNoMouse(pos, 0.0f);
	}

	

	void SetPos(D3DXVECTOR2 pos) {
		Timer_Vertex.pos = pos;
		Timer_Second.pos = D3DXVECTOR2(Timer_Vertex.pos.x + Timer_Vertex.size.x + 25.0f, pos.y);
		Timer_Third.pos = D3DXVECTOR2(Timer_Second.pos.x + Timer_Vertex.size.x + 25.0f, pos.y);
		Timer_TenDigits.pos = D3DXVECTOR2(Timer_Vertex.pos.x - (Timer_Vertex.size.x + 25.0f), pos.y);

		Timer_Point.pos.x = Timer_Vertex.pos.x + (Timer_Vertex.size.x * 1 / 2);
		Timer_Point.pos.y = Timer_Vertex.pos.y + (Timer_Vertex.size.x * 1 / 3);
	}

	void SetSize(D3DXVECTOR2 size) 
	{
		Timer_Vertex.size = size;
		Timer_Second.size = size;
		Timer_Third.size = size;
		Timer_TenDigits.size = size;

		Timer_Point.size = D3DXVECTOR2(Timer_Vertex.size.x * 3 / 4, Timer_Vertex.size.y * 3 / 4);
		
	}
private:
//--------------------------------------------------------
//	メンバ変数
//--------------------------------------------------------

		//	Texture用変数
	char TEX_NAME[128] = "data/TEXTURE/number02.png";
	char* TEX_NAME_MINORITY = "data/TEXTURE/number02_mono.png";
	char* TEX_NAME_POINT = "data/TEXTURE/ten.png";

	int Number_Texture;
	int m_TexIndex_Minority;
	int m_TexIndex_Point;

	//	GameScene用変数
	const int m_GameScene = GAMESCENE_GAME_TEST;

	//	UV用の変数
	const int NUMBER_X = 4;
	const int NUMBER_Y = 4;
	const float NUMBER_WIDTH = 1.0f / (float)NUMBER_X;
	const float NUMBER_HEIGHT = 1.0f / (float)NUMBER_Y;

	//頂点データ
	VERTEX_ALPHA_ANIMATION_USE Timer_Vertex;	//1桁目
	VERTEX_UV Timer_Second;						//小数点第一位
	VERTEX_UV Timer_Third;						//小数点第二位
	VERTEX_UV Timer_TenDigits;					//10の位
	VERTEX_UV Timer_Point;						//小数点

	//	エフェクト
	E_Prizum m_Eff;
	E_AddTime m_AddTime;
	E_Circle m_Circle;
	E_Circle m_Circle_001;
	
//--------------------------------------------------------
//	メンバ関数
//--------------------------------------------------------
//	What --> 一桁目　～　小数点第二位までの更新処理
//	Why	 --> 整理のため
//--------------------------------------------------------
	void FirstNum(void);

	void SecondNum(void);
	
	void ThirdNum(void);

	void TenDigits(void);

	//タイマーが0になったらGameoverへ
	void SceneToGameOver(void);

	void CJ_KitchenTimerPlayer(void);
};

