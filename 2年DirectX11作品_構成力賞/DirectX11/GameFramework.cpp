//=============================================================================
//
// ÉQÅ[ÉÄëÂògä«óù [GameFramework.cpp]
// Author : Yanagisawa Yuta
//
//=============================================================================
#include "GameFramework.h"


void GameFramework::Create(void)
{
	//null
	{
		m_pPlayer				= nullptr;
		m_pStage				= nullptr;
		m_pDeployEnemy			= nullptr;

		for (int i = 0; i < DEPLOY_ENEMY_MAX; i++) {
			m_pCollPlayerAndEnemy[i] = nullptr;
			m_pCollStageAndEnemy[i] = nullptr;
		}

		m_pCollPlayerAndStage = nullptr;
		
	}

	//new
	{
		m_pPlayer				= new GO_Player();
		m_pStage				= new GO_SwitchStage();
		m_pDeployEnemy			= new DeployEnemy();
		
		for (int i = 0; i < DEPLOY_ENEMY_MAX; i++) {
			m_pCollPlayerAndEnemy[i] = new PlayerAndEnemyCollision();
			m_pCollStageAndEnemy[i] = new StageAndEnemyCollision();
		}

		m_pCollPlayerAndStage = new PlayerAndStageCollision();
		
	}
	

	//Register
	{
		mRegister(m_pPlayer);	
		mRegister(m_pStage);
		mRegister(m_pDeployEnemy);

		for (int i = 0; i < DEPLOY_ENEMY_MAX; i++) {
			if (m_pCollPlayerAndEnemy[i]) {
				mRegister(m_pCollPlayerAndEnemy[i]);
				mRegister(m_pCollStageAndEnemy[i]);
			}
		}
		mRegister(m_pCollPlayerAndStage);
		
	}

}

void GameFramework::SetObject(void)
{
	for (int i = 0; i < DEPLOY_ENEMY_MAX; i++) {
		if (m_pCollPlayerAndEnemy[i]) {

			m_pCollPlayerAndEnemy[i]->SetEnemy(m_pDeployEnemy->GetEnemy(i));
			m_pCollStageAndEnemy[i]->SetEnemy(m_pDeployEnemy->GetEnemy(i));

			m_pCollPlayerAndEnemy[i]->SetPlayer(m_pPlayer);
			m_pCollStageAndEnemy[i]->SetStage(m_pStage->GetStage());
		}
	}
	m_pCollPlayerAndStage->SetPlayer(m_pPlayer);
	m_pCollPlayerAndStage->SetStage(m_pStage->GetStage());

	
}

GameFramework::GameFramework()
{
	for (int i = 0; i<GAME_OBJECT_MAX; i++) {
		GameObjects[i] = nullptr;
	}

	Create();
}
GameFramework::~GameFramework()
{
	for (int i = 0; i < GAME_OBJECT_MAX; i++) {
		delete GameObjects[i];
	}
}
void GameFramework::Init()
{
	SetObject();

	for (int i = 0; i < GAME_OBJECT_MAX; i++) {
		if (!GameObjects[i])continue;
		GameObjects[i]->Init();;
	}

	
}
void GameFramework::Uninit()
{
	for (int i = 0; i < GAME_OBJECT_MAX; i++) {
		if (!GameObjects[i])continue;
		GameObjects[i]->Uninit();;
	}
}
void GameFramework::Update()
{
	for (int i = 0; i < GAME_OBJECT_MAX; i++) {
		if (!GameObjects[i])continue;
		GameObjects[i]->Update();
	}

	if (GetSelectSkillState()) {
		for (int i = 0; i < DEPLOY_ENEMY_MAX; i++) {
			if (m_pDeployEnemy->GetEnemy(i)) {
				m_pDeployEnemy->HPLottery();
			}
		}
	}
		
}
void GameFramework::Draw()
{
	for (int i = 0; i < GAME_OBJECT_MAX; i++) {
		if (!GameObjects[i])continue;
		GameObjects[i]->Draw();
	}
}
void GameFramework::mRegister(GameObject* go)
{
	for (int i = 0; i < GAME_OBJECT_MAX; i++) {
		if (GameObjects[i])continue;
		GameObjects[i] = go;
		break;
	}
}


