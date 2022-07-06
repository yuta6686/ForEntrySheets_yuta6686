#pragma once
#include "GameObject.h"

//	柳澤追加----------------------------------->>>

//	プレイヤーが風に衝突した際の動き
//	movementで使用
class PlayerMoveForFan {
private:
	const float WIND_ACCELERATION = 0.5f;	//加速度
	const float WIND_DEFAULT_SPEED = 1.0f;	//速度
public:
	void SetOnceFlag(bool flag) 
	{
		if (once == true)return;
		windSpeed = WIND_DEFAULT_SPEED;
		once = flag; 
	}

	//スピードの速さ更新とフラグの処理
	void ChangeWindSpeed();	

	float GetWindSpeed() { 
		ChangeWindSpeed();
		return windSpeed; 
	}

private:
	float		windSpeed = WIND_DEFAULT_SPEED;

	bool		once = false;
};

//	m_CollisionNum用変数
//	使用用途：どの向きに衝突しているか判別する
enum FAN_COLLISION {
	FAN_COLL_NONE = -1,
	FAN_COLL_UP,
	FAN_COLL_LEFT,
};
//	柳澤追加-----------------------------------<<<

class GO_SS_Fan : public GameObject
{
public:		//	変更可能変数
	static const int FANS_MAX = 5;		//換気扇の最大数

private:	//	変更可能変数
	const int GAME_SCENE = GAMESCENE_GAME_TEST;
	const int WIND_TEX_MAX = 60;
	const int WIND_HEIGHT_SPLIT = 12;
	const int WIND_WIDTH_SPLIT = 5;
	const float WIND_ADD_V = 0.083f;
	const float WIND_ADD_U = 0.2f;

	const float LEFT_QUANTITY = 4.71238898038469f;


public:
	// GameObject を介して継承されました
	virtual void Initialize(void) override;
	virtual void Finalize(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;
	virtual int GetGameScene(void) { return GAME_SCENE; }

	//吐き出す側の設定　引数:位置
	void LinkFanB(D3DXVECTOR2 pos, bool isLeft);

	//換気扇のセット　引数:位置
	void SetFan(D3DXVECTOR2 pos);

	void SetCircle(VERTEX_CIRCLE* p) { m_pCircle = p; }

	FAN_VARTEX* GetFan(void) { return m_FanInfo; }

	void AddX(FLOAT x);

	inline void ResetOnce(void) {
		for (int i = 0; i < FANS_MAX; i++) {
			m_FanInfo[i].use = false;
		}
		once = true;
	}

//	柳澤追加----------------------------------->>>
//	m_CollisionNumセッターゲッター
	void SetCollisionNum(int num) { m_CollisionNum = num; }
	int GetCollisionNum(void) { return m_CollisionNum; }

//柳澤追加-----------------------------------<<<

private:

	bool FCCollision(D3DXVECTOR2 pos1, D3DXVECTOR2 size1, D3DXVECTOR2 pos2, float size2);
	void DebugOut(void);

	int m_FanATex;
	int m_FanBTex;
	int m_WindTex;

	FAN_VARTEX m_FanInfo[FANS_MAX];

	VERTEX_CIRCLE* m_pCircle;
	bool once;

//	柳澤追加----------------------------------->>>
		//	衝突: -1 ,上 0 ,左1
	int m_CollisionNum = -1;

//	柳澤追加-----------------------------------<<<
};