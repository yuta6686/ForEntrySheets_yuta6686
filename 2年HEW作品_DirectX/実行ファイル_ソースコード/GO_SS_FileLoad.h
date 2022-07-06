#pragma once
#include "GameObject.h"
#include <iostream>
#include <vector>

class GO_SS_FileLoad :public GameObject
{
public:
	virtual void Initialize(void) override;

	virtual void Finalize(void) override;

	virtual void Update(void) override;

	virtual void Draw(void) override;

	void GO_SS_FileLoad::MapFileLoad(int MapData[][STAGE_WALL_NUM_X]);

	virtual int GetGameScene(void) override { return GAME_SCENE; }
private:
	const int GAME_SCENE = GAMESCENE_GAME_TEST;
};