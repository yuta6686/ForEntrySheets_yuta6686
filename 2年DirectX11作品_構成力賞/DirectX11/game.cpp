/*==============================================================================

   ゲーム処理 [game.cpp]
														 Author :Yanagisawa Yuta
														 Date   :~~~~~~~~~~~~~~~
--------------------------------------------------------------------------------

==============================================================================*/

#include "game.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "meshfield.h"
#include "collision.h"
#include "sound.h"
#include "score.h"
#include "camera.h"
#include "light.h"
#include "shadow.h"
#include "GameFramework.h"



/*------------------------------------------------------------------------------
   グローバル変数の定義
------------------------------------------------------------------------------*/
static int g_BGMNo = 0;
static GameFramework g_GameFramework;

static SelectSkill g_SelectSkill;

static Eff_Clear g_ClearEffect;

static UInew_Manager g_UImanager;

UInew_Manager* GetUIManager() { return &g_UImanager; }

Eff_Clear* GetClearEffect() { return &g_ClearEffect; }

//	true  = スキル選択状態中
//	false = ゲーム中
bool g_SelectSkillState = false;

/*------------------------------------------------------------------------------
   関数宣言・定義
------------------------------------------------------------------------------*/

/*
//	true  = スキル選択状態中
//	false = ゲーム中
bool g_SelectSkillState;
*/
bool GetSelectSkillState(void) { return g_SelectSkillState; }
void ChangeSelectSkillState(bool flag) { g_SelectSkillState = flag; }

/*------------------------------------------------------------------------------
   初期化関数
------------------------------------------------------------------------------*/
void InitGame(void)
{
	// カメラの初期化
	InitCamera();

	// ライトの初期化
	InitLight();

	// 影の初期化
	InitShadow();

	g_GameFramework.Init();

	// 地面の初期化
	InitMeshField(D3DXVECTOR3(0.0f, -1001.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, 10, 100.0f, 100.0f);


	// 弾の初期化
	InitBullet();

	// スコアの初期化
	InitScore();

	//	ゲームクリア時のエフェクト初期化
	g_ClearEffect.Init();

	SetLightEnable(true);

	//  スキル選択処理初期化
	g_SelectSkill.Init();

	//	UI管理初期化
	g_UImanager.Init();

	g_BGMNo = LoadSound((char*)"data/BGM/kanatanouchuu.wav");

	SetVolume(g_BGMNo, 0.25f);
	PlaySound(g_BGMNo, -1);
}

/*------------------------------------------------------------------------------
   終了処理をする関数
------------------------------------------------------------------------------*/
void UninitGame()
{
	//初期化とは逆順に終了処理を行う
	g_GameFramework.Uninit();

	//	スコア終了処理
	UninitScore();

	//	ゲームクリアエフェクト終了処理
	g_ClearEffect.Uninit();

	//	影終了処理
	UninitShadow();

	//	バレット終了処理
	UninitBullet();

	//	メッシュフィールド終了処理
	UninitMeshField();

	//	スキル選択終了処理
	g_SelectSkill.Uninit();

	//	UI終了処理
	g_UImanager.Uninit();

	//	ステージ番号リセット
	*GetStageNum() = 0;
}

/*------------------------------------------------------------------------------
   更新処理をする関数
------------------------------------------------------------------------------*/
void UpdateGame(void)
{
	
	// カメラ更新
	UpdateCamera();

	// 地面の更新処理
	UpdateMeshField();

	g_GameFramework.Update();

	// 影の更新処理
	UpdateShadow();

	// 弾の更新処理
	UpdateBullet();

	//	スキル選択
	if (g_SelectSkillState) {
		g_SelectSkill.Update();
	}

	// スコアの更新処理
	UpdateScore();

	//	クリアエフェクト更新処理
	g_ClearEffect.Update();

	//	UI更新処理
	g_UImanager.Update();

	// 当たり判定の更新処理
	UpdateCollision();
}

/*------------------------------------------------------------------------------
   描画処理をする関数
------------------------------------------------------------------------------*/
void DrawGame(void)
{
	// プレイヤー視点
	//D3DXVECTOR3 pos = GetPlayer()->pos;
	//pos.y = 0.0f;			// カメラ酔いを防ぐためにクリアしている
	//SetCameraAT(pos);
	//SetCamera();

	// 深度テスト有効
	SetDepthEnable(true);

	// ライティング有効
	SetLightEnable(true);

	// 地面の描画処理
	DrawMeshField();

	// 影の描画処理
	DrawShadow();

	g_GameFramework.Draw();

	// 弾の描画処理
	DrawBullet();

	// マトリクス設定
	SetWorldViewProjection2D();//座標の2D変換

	// 2D描画なので深度無効
	SetDepthEnable(false);

	// スコアの描画処理
	//DrawScore();

	//	クリアエフェクト描画処理
	g_ClearEffect.Draw();

	//	UI更新描画処理
	g_UImanager.Draw();

	//	スキル選択状態なら描画
	if (g_SelectSkillState) {
		g_SelectSkill.Draw();
	}
	
}

