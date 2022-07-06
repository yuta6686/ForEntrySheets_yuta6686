//=============================================================================
//
// エネミー配置 [DeployEnemy.h]
// Author : Yanagisawa Yuta
//
// 説明：エネミーを一定時間経過したら出現させる
//		ダイヤモンドとスクエアの比率ー＞D:S = 1:3
//=============================================================================
#pragma once
#include "Enemy_Square.h"
#include "Enemy_Diamond.h"
#include <vector>
#include <memory>

//	この定義とエネミーの種類数は一致させる必要がある
#define DEPLOY_ENEMY_MAX 2

class DeployEnemy :public GameObject
{
public:
	DeployEnemy();
	~DeployEnemy();

private:
	static const int DEPLOY_CYCLE_TIME = 7;	//時間
	static const int DEPLOY_CYCLE = DEPLOY_CYCLE_TIME * 60;	//時間をフレームにしただけ。
public:
	virtual void Init()override;
	virtual void Uninit()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual bool Register(GO_Enemy* pEnemy);
	virtual void Create();
	
	virtual void HPLottery();

	//  動き
	virtual void Action();

	//  死んだときの処理
	virtual bool Death();
	

	virtual GO_Enemy* GetEnemy(int index) { 
		if (index > DEPLOY_ENEMY_MAX || index < 0)return nullptr;
		if (!m_pEnemys[index])return nullptr;
		return m_pEnemys[index]; 
	}
private:
	void DeployEnemyCycle(void);

	//	レベル
	int m_NowLevel;

	//	エネミーの最大数
	int m_MaxEnemyNum;

	// エネミー出現のカウンター
	int m_timeCounter = 0;
	
	GO_Enemy* m_pEnemys[DEPLOY_ENEMY_MAX];
};

