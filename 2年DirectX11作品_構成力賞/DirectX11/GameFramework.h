#pragma once
//---------------------------
//	[GameFramework.h]
//	Yuta Yanagisawa 
//---------------------------

	///インクルード///
#include "GameObject.h"
#include "GO_Player.h"
#include "GO_SwitchStage.h"
#include "PlayerAndEnemyCollision.h"
#include "StageAndEnemyCollision.h"
#include "PlayerAndStageCollision.h"
#include "DeployEnemy.h"


class GameFramework
{
private:
	GO_Player* m_pPlayer;
	GO_SwitchStage* m_pStage;
	DeployEnemy* m_pDeployEnemy;
	PlayerAndEnemyCollision* m_pCollPlayerAndEnemy[DEPLOY_ENEMY_MAX];
	StageAndEnemyCollision* m_pCollStageAndEnemy[DEPLOY_ENEMY_MAX];
	PlayerAndStageCollision* m_pCollPlayerAndStage;
	

public:
	GameFramework();
	~GameFramework();

	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	static const int	GAME_OBJECT_MAX = 50;
	GameObject*			GameObjects[GAME_OBJECT_MAX];



	void mRegister(GameObject* go);
	void Create(void);
	void SetObject(void);
};

