/*==============================================================================

   シーン管理 [scene.cpp]
														 Author :Yanagisawa Yuta
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include <vector>

#include "SelectSkill.h"

#define A_STAGE_NUM_MAX 10

// 登録シーン一覧
enum SCENE
{
	SCENE_NONE,		//シーン処理なし
	SCENE_TITLE,	//タイトル
	SCENE_TUTORIAL,	//チュートリアル
	SCENE_GAME,		//ゲーム
	SCENE_RESULT,	//リザルト

	SCENE_MAX		//最後だとわかる奴をいれる
};

void InitScene(SCENE index);
void UninitScene(void);
void UpdateScene(void);
void DrawScene(void);

void SetScene(SCENE index);
void CheckScene(void);

bool GetOnceTutorial();
void SetOnceTutorial(bool flag);



SkillManager* GetSkillManager_Scene(void);

int* GetStageNum(void);
void AddStageNum(int value);