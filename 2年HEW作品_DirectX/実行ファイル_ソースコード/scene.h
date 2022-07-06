#pragma once
//#include "StageObject.h"

// 登録シーン一覧
enum SCENE
{
	SCENE_NONE,			//シーン処理なし
	SCENE_TITLE,		//タイトル
	SCENE_CREDIT,		//クレジット
	SCENE_SELECT_STAGE,	//ステージ選択
	SCENE_TUTORIAL,		//チュートリアル
	SCENE_GAME,			//ゲーム
	SCENE_RESULT,		//リザルト
	SCENE_GAMEOVER,		//ゲームオーバー

	SCENE_MAX			//最後だとわかる奴をいれる
};

void InitScene(SCENE index);
void UninitScene(void);
void UpdateScene(void);
void DrawScene(void);

void SetScene(SCENE index);
void CheckScene(void);

void SetStageNum(int sn);
int GetStageNum(void);
void AddStageNum(void);