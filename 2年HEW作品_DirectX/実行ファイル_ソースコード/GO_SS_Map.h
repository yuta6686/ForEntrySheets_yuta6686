#pragma once
#include "GameObject.h"
#include <iostream>
#include <vector>

#include "GO_SS_Negi.h"
#include "GO_SS_Karashi.h"

class GO_SS_FileLoad;
class GO_SS_Wall;
class GO_SS_Target;
class GO_SS_Fan;
class GO_SS_Goal;
class GO_SS_KitchenTimer;
class GO_SS_Negi;
class GO_SS_Player;
//class GO_SS_ZipLine;

//マップチップの列挙型
typedef enum {
	WALL_NUM = 1,
	TARGET_NUM,
	FAN_A_NUM,
	FAN_B_UP_NUM,
	FAN_B_LEFT_NUM,
	GOAL_NUM,
	KITCHEN_TIMER_NUM,
	NEGI_NUM,
	KARASHI_NUM,
	ZIPLINE_A_NUM,
	ZIPLINE_B_NUM,
}MAP_CHIP_NO;

class GO_SS_Map :public GameObject
{
public:
	// GameObject を介して継承されました
	virtual void Initialize(void) override;
	virtual void Finalize(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

	void SetFileLoad(GO_SS_FileLoad* p) { m_pFileLoad = p; }
	void SetWall(GO_SS_Wall* p) { m_pWall = p; }
	void SetTarget(GO_SS_Target* p) { m_pTarget = p; }
	void SetFan(GO_SS_Fan* p) { m_pFan = p; }
	void SetGoal(GO_SS_Goal* p) { m_pGoal = p; }
	//void SetZipline(GO_SS_ZipLine* p) { m_pZipLine = p; }
	void SetKTimer(GO_SS_KitchenTimer* p) { m_pKTimer = p; }
	void SetNegi(GO_SS_Negi* pNegi) { m_pNegi = pNegi; }
	void SetKarashi(GO_SS_Karashi* pKarashi) { m_pKarashi = pKarashi; }
	void SetPlayer(GO_SS_Player* pPlayer) { m_pPlayer = pPlayer; }
	//マップオブジェクトの移動
	void MoveMapObject(FLOAT x);

	virtual int GetGameScene(void) override { return GAME_SCENE; }

	void ResetOnce(void);

private:
	//bool SeekZipLineB(int CurrentNum, int CurrentNumY);
	bool SeekFanB(int CurrentNumX, int CurrentNumY);

	int GAME_SCENE = GAMESCENE_GAME_TEST;
	int MapData[STAGE_WALL_NUM_Y][STAGE_WALL_NUM_X];//まっぷでーた
	static const int SEEK_ZIP_MAX = 5;	//Bを探すときの最大距離

	GO_SS_FileLoad* m_pFileLoad;	//FileLoadポインタ
	GO_SS_Wall* m_pWall;			//Wallポインタ
	GO_SS_Target* m_pTarget;		//targetポインタ
	GO_SS_Fan* m_pFan;
	GO_SS_Goal* m_pGoal;	
	//GO_SS_ZipLine* m_pZipLine;		//ZipLineポインタ

	GO_SS_KitchenTimer* m_pKTimer;
	GO_SS_Negi* m_pNegi;
	GO_SS_Karashi* m_pKarashi;
	GO_SS_Player* m_pPlayer;

	MAP_CHIP_NO mapChipNo;

	bool once;
};