#include "GO_SS_Manager.h"
#include "GO_SS_Player.h"
#include "GO_SS_Wall.h"
#include "GO_SS_BackGround.h"
#include "GO_SS_Movement.h"
#include "GO_SS_Target.h"
#include "GO_SS_ShotString.h"
#include "GO_SS_Collision.h"
#include "GO_SS_FileLoad.h"
#include "GO_SS_Map.h"
#include "GO_SS_Effect_Wind.h"
#include "GO_SS_Scramble.h"
#include "GO_SS_Timer.h"
#include "GO_SS_Goal.h"
#include "GO_SS_TimeDelay.h"
#include "GO_SS_Fan.h"
#include "GO_SS_KitchenTimer.h"

/*---------------------------------------------
				?R???X?g???N?^
---------------------------------------------*/
GO_SS_Manager::GO_SS_Manager()
{
	for (int i = 0; i < GAMESCENE_GAME_TEST; i++) {
		m_ssGameObject[i] = nullptr;
	}

	Create();
}

/*---------------------------------------------
				?N???G?C?g
-----------------------------------------------
	?|?C???^???????A?????A???W?X?^?[
---------------------------------------------*/
void GO_SS_Manager::Create()
{
	//null
	{
		mp_ssBackGround = nullptr;
		mp_ssPlayer		= nullptr;
		mp_ssWall		= nullptr;
		mp_ssMovement= nullptr;
		mp_ssTarget = nullptr;
		mp_ssShotString = nullptr;
		mp_ssFileLoad = nullptr;
		mp_ssMap = nullptr;
		mp_ssEffWind = nullptr;
		mp_ssScramble = nullptr;
		mp_ssTimer = nullptr;
		mp_ssGoal = nullptr;
		mp_ssTimeDelay = nullptr;
		mp_ssFan = nullptr;
		mp_ssKitchenTimer = nullptr;
		mp_ssNegi = nullptr;
		mp_ssKarashi = nullptr;
	}

	//new
	{
		mp_ssBackGround = new GO_SS_BackGround;
		mp_ssPlayer = new GO_SS_Player;
		mp_ssWall = new GO_SS_Wall;
		mp_ssMovement = new GO_SS_Movement;

		mp_ssTarget = new GO_SS_Target;
		mp_ssShotString = new GO_SS_ShotString;
		mp_ssFileLoad = new GO_SS_FileLoad;
		mp_ssMap = new GO_SS_Map;
		mp_ssEffWind = new GO_SS_Effect_Wind;
		mp_ssScramble = new GO_SS_Scramble;
		mp_ssTimer = new GO_SS_Timer;
		mp_ssGoal = new GO_SS_Goal;
		mp_ssTimeDelay = new GO_SS_TimeDelay;
		mp_ssFan = new GO_SS_Fan;
		mp_ssKitchenTimer = new GO_SS_KitchenTimer;
		mp_ssNegi = new GO_SS_Negi;
		mp_ssKarashi = new GO_SS_Karashi;
	}

	//Register
	{
		Register(mp_ssBackGround);
		
		Register(mp_ssScramble);
		Register(mp_ssGoal);
		Register(mp_ssPlayer);
		
		Register(mp_ssWall);
		Register(mp_ssMovement);
		Register(mp_ssTarget);
		Register(mp_ssFan);
		Register(mp_ssShotString);
		Register(mp_ssFileLoad);
		Register(mp_ssMap);
		Register(mp_ssEffWind);
		Register(mp_ssTimeDelay);
		Register(mp_ssKitchenTimer);
		Register(mp_ssNegi);
		Register(mp_ssKarashi);

		Register(mp_ssTimer);
	
	}
}

/*---------------------------------------------
	SetGameObject()
-----------------------------------------------
	
---------------------------------------------*/
void GO_SS_Manager::SetGameObject()
{
	//mp_ssComunication
	{
		mp_ssMovement->SetBackGround(mp_ssBackGround);
		mp_ssMovement->SetPlayer(mp_ssPlayer);
		mp_ssMovement->SetShotString(mp_ssShotString);
		mp_ssMovement->SetGoal(mp_ssGoal);
		mp_ssMovement->SetWall(mp_ssWall);
		mp_ssMovement->SetTarget(mp_ssTarget);
		mp_ssMovement->SetMap(mp_ssMap);
		mp_ssMovement->SetEffWind(mp_ssEffWind);
		mp_ssMovement->SetTimeDelay(mp_ssTimeDelay);
		mp_ssMovement->SetFan(mp_ssFan);
		mp_ssMovement->SetKitchenTimer(mp_ssKitchenTimer);
		mp_ssMovement->SetTimer(mp_ssTimer);
		mp_ssMovement->SetNegi(mp_ssNegi);
		mp_ssMovement->SetKarashi(mp_ssKarashi);

		mp_ssShotString->SetPlayer(mp_ssPlayer);
		mp_ssShotString->SetTarget(mp_ssTarget);
		mp_ssShotString->SetScramble(mp_ssScramble);

		mp_ssMap->SetFileLoad(mp_ssFileLoad);
		mp_ssMap->SetWall(mp_ssWall);
		mp_ssMap->SetTarget(mp_ssTarget);
		mp_ssMap->SetFan(mp_ssFan);
		mp_ssMap->SetGoal(mp_ssGoal);
		mp_ssMap->SetKTimer(mp_ssKitchenTimer);
		mp_ssMap->SetNegi(mp_ssNegi);
		mp_ssMap->SetKarashi(mp_ssKarashi);
		mp_ssMap->SetPlayer(mp_ssPlayer);

		mp_ssFan->SetCircle(mp_ssShotString->GetCircle());
		//mp_ssMap->SetZipline(mp_ssZipLine);
	}
}
/*---------------------------------------------
*				?f?X?g???N?^
---------------------------------------------*/
GO_SS_Manager::~GO_SS_Manager()
{
	for (int i = 0; i < SS_GAMEOBJECT_MAX; i++) {
		// nullptr??delete???????v
		delete m_ssGameObject[i];
	}
}
/*---------------------------------------------
*				??????????
---------------------------------------------*/
void GO_SS_Manager::Initialize(void)
{
	for (int i = 0; i < SS_GAMEOBJECT_MAX; i++) {
		if (m_ssGameObject[i]) {
			m_ssGameObject[i]->Initialize();
		}
	}
	SetGameObject();
}
/*---------------------------------------------
*				?I??????
---------------------------------------------*/
void GO_SS_Manager::Finalize(void)
{
	for (int i = 0; i < SS_GAMEOBJECT_MAX; i++) {
		if (m_ssGameObject[i]) {
			m_ssGameObject[i]->Finalize();
		}
	}
}
/*---------------------------------------------
*				?X?V????
---------------------------------------------*/
void GO_SS_Manager::Update(void)
{
	for (int i = 0; i < SS_GAMEOBJECT_MAX; i++) {
		if (!m_ssGameObject[i])continue;

		m_ssGameObject[i]->Update();
	}

	LastUpdate();
}
void GO_SS_Manager::LastUpdate(void)
{
	mp_ssScramble->LastUpdate();
}
/*---------------------------------------------
*				?`????
---------------------------------------------*/
void GO_SS_Manager::Draw(void)
{
	for (int i = 0; i < SS_GAMEOBJECT_MAX; i++) {
		if (!m_ssGameObject[i])continue;
		m_ssGameObject[i]->Draw();

	}
}
/*---------------------------------------------
*				?o?^????
---------------------------------------------*/
void GO_SS_Manager::Register(GameObject* pSSObject)
{
	for (int i = 0; i < SS_GAMEOBJECT_MAX; i++) {
		if (!m_ssGameObject[i]) {
			m_ssGameObject[i] = pSSObject;
			break;
		}
	}
}





