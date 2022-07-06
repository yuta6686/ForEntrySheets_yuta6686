//=============================================================================
//
// 当たり判定処理 [collision.cpp]
// Author : Yanagisawa Yuta
//
// サンプルとして残している
//=============================================================================
#include "main.h"
#include "collision.h"
#include "player.h"
#include "enemy.h"
#include "score.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// 構造体定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool CollisionBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2);
bool CollisionBS(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);


//*****************************************************************************
// グローバル変数
//*****************************************************************************


//=============================================================================
// 当たり判定処理
//=============================================================================
void UpdateCollision(void)
{
//	PLAYER *player = GetPlayer();	// プレイヤーのポインターを初期化
//	ENEMY  *enemy = GetEnemy();		// エネミーのポインターを初期化
//
//	// 敵と操作キャラ(BB)
//	if (player[0].use == true)
//	{
//		for (int i = 0; i < ENEMY_NUM; i++)
//		{
//			if (enemy[i].use == false)
//				continue;
//
////			if (CollisionBB(player->pos, enemy[i].pos, player->size, enemy[i].size))
//			if (CollisionBS(player->pos, enemy[i].pos, player->size.x / 2, enemy[i].size.x / 2))
//			{
//				// 敵キャラクターを消す
//				enemy[i].use = false;
//				// 影も消さなくてはならい
//				ReleaseShadow(enemy[i].idxShadow);
//
//				// スコアを追加
//				AddScore(39);
//			}
//		}
//	}
}

//=============================================================================
// 境界箱BBによる当たり判定処理
// 回転は考慮しない
// 戻り値：当たってたらtrue
//=============================================================================
bool CollisionBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2)
{
	float Axmax = pos1.x + (size1.x / 2);
	float Axmin = pos1.x - (size1.x / 2);
	float Aymax = pos1.y + (size1.y / 2);
	float Aymin = pos1.y - (size1.y / 2);
	float Azmax = pos1.z + (size1.z / 2);
	float Azmin = pos1.z - (size1.z / 2);

	float Bxmax = pos2.x + (size2.x / 2);
	float Bxmin = pos2.x - (size2.x / 2);
	float Bymax = pos2.y + (size2.y / 2);
	float Bymin = pos2.y - (size2.y / 2);
	float Bzmax = pos2.z + (size2.z / 2);
	float Bzmin = pos2.z - (size2.z / 2);

	if ((Axmax > Bxmin) && (Axmin < Bxmax))
	{
		if ((Aymin < Bymax) && (Aymax > Bymin))
		{
			if ((Azmax > Bzmin) && (Azmin < Bzmax))
			{
				return true;
			}
		}
	}

	return false;
}

//=============================================================================
// 境界球BSによる当たり判定処理
// サイズは半径
// 戻り値：当たってたらtrue
//=============================================================================
bool CollisionBS(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{
	//pos1とpos2をつなぐベクトルを作る
	D3DXVECTOR3 dist = pos2 - pos1;

	//作ったベクトルの大きさを計算する
//	float length = D3DXVec3Length(&dist);

	//Sqがついている関数は平方根の計算をしないバージョン
	float length = D3DXVec3LengthSq(&dist);

	//1と2の半径を足す
	float size = size1 + size2;

	//判定する相手の方を二乗する
	size = size * size;

	//半径の方が大きいとき、二つの円は重なっている
	if (length < size)
		return true;

	return false;
}
