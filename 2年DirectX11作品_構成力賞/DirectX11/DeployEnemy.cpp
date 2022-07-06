//=============================================================================
//
// エネミー配置 [DeployEnemy.cpp]
// Author : Yanagisawa Yuta
//
// 説明：エネミーを一定時間経過したら出現させる
//		ダイヤモンドとスクエアの比率ー＞D:S = 1:3
//=============================================================================
#include "DeployEnemy.h"
#include "game.h"
#include "scene.h"

void DeployEnemy::Create()
{
	Register(new Enemy_Square());
	Register(new Enemy_Diamond());
}



DeployEnemy::DeployEnemy() : m_NowLevel(0), m_MaxEnemyNum(0)
{
	for (int i = 0; i < DEPLOY_ENEMY_MAX; i++) {
		m_pEnemys[i] = nullptr;
	}
	Create();

	
}

DeployEnemy::~DeployEnemy()
{
	for (int i = 0; i < DEPLOY_ENEMY_MAX; i++) {
		delete m_pEnemys[i];
	}
}

void DeployEnemy::Init()
{
	for (int i = 0; i < DEPLOY_ENEMY_MAX; i++) {
		if (!m_pEnemys[i])continue;
		m_pEnemys[i]->Init();
	}

	for (int i = 0; i < DEPLOY_ENEMY_MAX; i++) {
		if (!m_pEnemys[i])continue;
		m_pEnemys[i]->HPLottery();
	}
}

void DeployEnemy::Uninit()
{
	for (int i = 0; i < DEPLOY_ENEMY_MAX; i++) {
		if (!m_pEnemys[i])continue;
		m_pEnemys[i]->Uninit();
	}

}

void DeployEnemy::Update()
{
	if (GetSelectSkillState())return;

	DeployEnemyCycle();

	Action();

	for (int i = 0; i < DEPLOY_ENEMY_MAX; i++) {
		if (!m_pEnemys[i])continue;
		m_pEnemys[i]->Update();
	}
}

void DeployEnemy::Draw()
{
	for (int i = 0; i < DEPLOY_ENEMY_MAX; i++) {
		if (!m_pEnemys[i])continue;
		m_pEnemys[i]->Draw();
	}
}

void DeployEnemy::HPLottery()
{
	for (int i = 0; i < DEPLOY_ENEMY_MAX; i++) {
		if (!m_pEnemys[i])continue;
		m_pEnemys[i]->HPLottery();
	}
}

bool DeployEnemy::Register(GO_Enemy* pEnemy)
{
	for (int i = 0; i < DEPLOY_ENEMY_MAX; i++) {
		if (m_pEnemys[i])continue;
		m_pEnemys[i] = pEnemy;
		return true;
	}
	return false;
}



void DeployEnemy::Action()
{
	for (int i = 0; i < DEPLOY_ENEMY_MAX; i++) {
		if (!m_pEnemys[i])continue;
		m_pEnemys[i]->Action();
	}
}

bool DeployEnemy::Death()
{
	for (int i = 0; i < DEPLOY_ENEMY_MAX; i++) {
		if (!m_pEnemys[i])continue;
		m_pEnemys[i]->Death();
		return i;
	}
	return -1;
}

void DeployEnemy::DeployEnemyCycle(void)
{
	

	if (m_timeCounter >= DEPLOY_CYCLE) {
		m_timeCounter = 0;

		for (int i = 0; i < DEPLOY_ENEMY_MAX; i++) {

		
			m_pEnemys[i]->SetNumOfEnemiesThatAppear((*GetStageNum()+1) * 5);

			for (int i = 0; i < m_pEnemys[0]->GetNumOfEnemiesThatAppear()/ENEMY_MAX/2; i++)
			{
				m_pEnemys[ENEMY_SQUARE]->SetEnemy();
				m_pEnemys[ENEMY_SQUARE]->SetEnemy();
				m_pEnemys[ENEMY_SQUARE]->SetEnemy();
				m_pEnemys[ENEMY_DIAMOND]->SetEnemy();
			}
		}
	}
	else {
		m_timeCounter++;
	}

#ifdef _DEBUG	
	if (GetKeyboardPress(DIK_R)) {
		m_pEnemys[ENEMY_SQUARE]->SetEnemy();
		m_pEnemys[ENEMY_DIAMOND]->SetEnemy();
	}
#endif

#ifdef _DEBUG	// デバッグ版の時だけAngleを表示する



	sprintf(&GetDebugStr()[strlen(GetDebugStr())], "カウンター：%d", m_timeCounter);

	SetWindowText(GethWnd()[0], GetDebugStr());
#endif
}

