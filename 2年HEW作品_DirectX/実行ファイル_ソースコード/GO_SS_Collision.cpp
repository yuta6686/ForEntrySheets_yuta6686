#include "GO_SS_Collision.h"
#include "GO_SS_BackGround.h"
#include "GO_SS_ShotString.h"
#include "GO_SS_Player.h"
#include "GO_SS_Target.h"
#include "GO_SS_Wall.h"
#include "GO_SS_Goal.h"
#include "GO_SS_Fan.h"
#include "game.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "GO_SS_KitchenTimer.h"
#include "GO_SS_Timer.h"
#include "result.h"
#include "sound.h"

static int g_SoundIndex = 0;

void GO_SS_Collision::CollisionInit(void)
{
	jumpOnce = false;
}

void GO_SS_Collision::CollisionUpdate(void)
{
	playerPos = m_pPlayer->GetPos();
	playerSize = m_pPlayer->GetSize();

	m_FanInfo = m_pFan->GetFan();


	Goal_Vertex = m_pGoal->GetGoal();

	//プレイヤーと壁の衝突処理
	if (collTemp = CJ_PlayerWall() >= 0)
	{
		m_pPlayer->IsColl = true;
		if (!jumpOnce) {
			m_pPlayer->IsJump = true;
			jumpOnce = true;
			upCollOnce = true;
		}
	}
	else m_pPlayer->IsColl = false;

	//横判定 
	m_pPlayer->IsCollSide = CJ_PWSide();
	m_pPlayer->IsCollUp = CJ_PlayerUpper();

	CJ_PlayerFan();

	CJ_GoalPlayer();

	PlayerYCorrection(collTemp);

	//	キッチンタイマーの当たり判定処理
	CJ_KitchenTimerPlayer();

	//	ネギとプレイヤーの当たり判定処理
	CJ_NegiAndPlayer();

	//	からしとプレイヤーの当たり判定処理
	CJ_KarashiAndPlayer();

	//	エフェクトをプレイヤーのポジションに追尾させる
	m_pKarashi->SetEffectPos(m_pPlayer->GetPos());

	//DebugOut();

	DebugOut();
}

// ----------------------------------------------------------------
//						プレイヤーと壁
// ----------------------------------------------------------------
//	戻値：	あたっていたら、その壁のインデックスを。
//			あたっていなかったら、-1を返す
// ----------------------------------------------------------------
int GO_SS_Collision::CJ_PlayerWall(void)
{
	for (int i = 0; i < m_pWall->GetWallNumMax(); i++) {
		VERTEX_WALL vwall = m_pWall->GetvWall(i);
		if (!vwall.use)continue;
		if (BBCollision_LeftTop2(m_pPlayer->GetPos(), D3DXVECTOR2(playerSize.x*0.99f,playerSize.y), vwall.pos, vwall.size)) {
			return i;
		}
	}
	return -1;
}

bool GO_SS_Collision::CJ_PlayerUpper(void)
{
	for (int i = 0; i < m_pWall->GetWallNumMax(); i++) {
		VERTEX_WALL vwall = m_pWall->GetvWall(i);
		if (!vwall.use)continue;
		if (BBCollision_LeftTop2(D3DXVECTOR2(playerPos.x,playerPos.y- playerSize.y * 0.5f + 50.0f),
			D3DXVECTOR2(playerSize.x * 0.99f, 60.0f), vwall.pos, vwall.size)) {
			return true;
		}
	}
	return false;
}

//プレイヤーの横と壁
//戻り値 -1:当たってない　1:左 2:右
int GO_SS_Collision::CJ_PWSide(void)
{
	for (int i = 0; i < m_pWall->GetWallNumMax(); i++) 
	{
		VERTEX_WALL vwall = m_pWall->GetvWall(i);
		if (!vwall.use)continue;
		//左
		if (BBCollision_LeftTop2(D3DXVECTOR2(playerPos.x - playerSize.x * 0.5f + 30.0f, playerPos.y),
			D3DXVECTOR2(60.0f, playerSize.y * 0.5f), vwall.pos, vwall.size))
		{
			m_pPlayer->SetPosX(vwall.pos.x + vwall.size.x + playerSize.x * 0.5f - 1);
			return 1;
		}
		//右
		if (BBCollision_LeftTop2(D3DXVECTOR2(playerPos.x + playerSize.x * 0.5f - 30.0f, playerPos.y),
			D3DXVECTOR2(60.0f, playerSize.y * 0.5f), vwall.pos, vwall.size))
		{
			m_pPlayer->SetPosX(vwall.pos.x - playerSize.x * 0.5f + 1);
			return 2;
		}
	}
	return false;
}

void GO_SS_Collision::CJ_PlayerFan(void)
{
	for (int i = 0; i < m_pFan->FANS_MAX; i++)
	{
		if (m_FanInfo[i].use) {
			if (m_FanInfo[i].isWork)
			{
				//上向き
				if (!m_FanInfo[i].isLeft)
				{
					if (BBCollision(playerPos, playerSize,
						D3DXVECTOR2(m_FanInfo[i].fanB_Pos.x + WALL_WIDTH / 2,
							m_FanInfo[i].fanB_Pos.y - WALL_HEIGHT + WALL_HEIGHT / 2), m_FanInfo[i].size))
					{
						/*上向き当たり判定処理*/
						m_pFan->SetCollisionNum(FAN_COLL_UP);
					}
					else
					{
						m_pFan->SetCollisionNum(FAN_COLL_NONE);
					}
				}
				//左むき
				else
				{
					if (BBCollision(playerPos, playerSize,
						D3DXVECTOR2(m_FanInfo[i].fanB_Pos.x - WALL_WIDTH + WALL_WIDTH / 2,
							m_FanInfo[i].fanB_Pos.y + WALL_HEIGHT / 2), m_FanInfo[i].size))
					{
						/*左向き当たり判定の処理*/
						m_pFan->SetCollisionNum(FAN_COLL_LEFT);

					}
					else {
						m_pFan->SetCollisionNum(FAN_COLL_NONE);
					}

				}
			}
			else {
				m_pFan->SetCollisionNum(FAN_COLL_NONE);
			}
		}
	}
}

bool GO_SS_Collision::BBCollision(D3DXVECTOR2 pos1, D3DXVECTOR2 size1, D3DXVECTOR2 pos2, D3DXVECTOR2 size2)
{
	D3DXVECTOR2 min1, max1;
	D3DXVECTOR2 min2, max2;

	min1.x = pos1.x - size1.x / 2;
	min1.y = pos1.y - size1.y / 2;
	max1.x = pos1.x + size1.x / 2;
	max1.y = pos1.y + size1.y / 2;

	min2.x = pos2.x - size2.x / 2;
	min2.y = pos2.y - size2.y / 2;
	max2.x = pos2.x + size2.x / 2;
	max2.y = pos2.y + size2.y / 2;

	//X軸の判定
	if (min1.x < max2.x && max1.x > min2.x)
	{
		//Y軸の判定
		if (min1.y < max2.y && max1.y > min2.y)
		{
			//全ての条件がTRUEならヒット判定
			return true;
		}
	}
	return false;
}

bool GO_SS_Collision::BBCollision_LeftTop2(D3DXVECTOR2 pos1, D3DXVECTOR2 size1, D3DXVECTOR2 pos2, D3DXVECTOR2 size2)
{
	D3DXVECTOR2 min1, max1;
	D3DXVECTOR2 min2, max2;

	min1.x = pos1.x - size1.x / 2;
	min1.y = pos1.y - size1.y / 2;
	max1.x = pos1.x + size1.x / 2;
	max1.y = pos1.y + size1.y / 2;

	min2.x = pos2.x;
	min2.y = pos2.y;
	max2.x = pos2.x + size2.x;
	max2.y = pos2.y + size2.y;

	//X軸の判定
	if (min1.x < max2.x && max1.x > min2.x)
	{
		//Y軸の判定
		if (min1.y < max2.y && max1.y > min2.y)
		{
			//全ての条件がTRUEならヒット判定
			return true;
		}
	}
	return false;
}

void GO_SS_Collision::DebugOut(void)
{
#ifdef _DEBUG	// デバッグ版の時だけAngleを表示する
	wsprintf(GetDebugStr(), WINDOW_CAPTION);
	//wsprintf(&GetDebugStr()[strlen(GetDebugStr())], " test:%d",);

	SetWindowText(GethWnd()[0], GetDebugStr());
#endif
}

void GO_SS_Collision::CJ_GoalPlayer(void)
{
	//スペースキーが押されていて、フェード処理中ではないとき
	if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE) {
		SetTime(m_pTimer->GetTimerCounter());

		//RESULTへ移行する
		SceneTransition(SCENE_RESULT);
	}

	if (BBCollision_LeftTop2(m_pPlayer->GetPos(), m_pPlayer->GetSize(), Goal_Vertex.pos, Goal_Vertex.size))
	{
		g_SoundIndex = LoadSound("data/BGM/se_goal.wav");

		//	第一引数ー＞グローバル変数、第二引数ー＞0～1までの数値
		//で音量が設定できます
		SetVolume(g_SoundIndex, 0.5f);

		PlaySound(g_SoundIndex, 0);

		
		
		//if ()
		//{
			SetTime(m_pTimer->GetTimerCounter());
			m_pGoal->SetGoalUse(false);
			SceneTransition(SCENE_RESULT);
		//}
	}
}

void GO_SS_Collision::PlayerYCorrection(int index)
{
	for (int i = 0; i < m_pWall->GetWallNumMax(); i++) {

		VERTEX_WALL vwall = m_pWall->GetvWall(i);
		if (!vwall.use)continue;

		if (BBCollision_LeftTop2(D3DXVECTOR2(playerPos.x, playerPos.y + playerSize.y * 0.5f - 15.0f),
			D3DXVECTOR2(playerSize.x * 0.8f, 8), vwall.pos, vwall.size))
		{
			if (playerPos.y + playerSize.y * 0.5f >= vwall.pos.y)
				m_pPlayer->SetPosY(vwall.pos.y - playerSize.y * 0.5f);
		}
	}
}

void GO_SS_Collision::CJ_KitchenTimerPlayer(void)
{
	for (int i = 0; i < m_pKitchenTimer->GetKichenTimerMax(); i++) {
		if (m_pKitchenTimer->GetKitchenTimer(i)->use)
		{
			if (BBCollision_LeftTop2(m_pPlayer->GetPos(), m_pPlayer->GetSize(), m_pKitchenTimer->GetKitchenTimer(i)->pos, m_pKitchenTimer->GetKitchenTimer(i)->size))
			{
				m_pKitchenTimer->SetUse(i,false);

				m_pTimer->AddTimer(m_pKitchenTimer->GetAddTimer());
				//m_pTimer->SetTimerCounter(m_pTimer->GetTimerCounter() - m_pKitchenTimer->GetAddTimer());

				m_pTimer->SetEffect(m_pPlayer->GetPos());

				m_pShotString->SetNatto(NRN_TIMER);
			}
		}
	}
	
}

void GO_SS_Collision::CJ_NegiAndPlayer(void)
{
	for (int i = 0; i < m_pNegi->GetNegiMax(); i++) {
		if (m_pNegi->GetNegi(i)->use)
		{
			if (BBCollision_LeftTop2(m_pPlayer->GetPos(), m_pPlayer->GetSize(), m_pNegi->GetNegi(i)->pos, m_pNegi->GetNegi(i)->size))
			{
				m_pNegi->SetUse(i, false);

				m_pNegi->SetEffect(D3DXVECTOR2(m_pNegi->GetNegi(i)->pos.x + m_pNegi->GetNegi(i)->size.x/2.0f,
					m_pNegi->GetNegi(i)->pos.y += m_pNegi->GetNegi(i)->size.y/2.0f));

				m_pShotString->SetIsNegi(true);

				m_pShotString->SetNatto(NRN_NEGI);

			}
		}
	}
}

void GO_SS_Collision::CJ_KarashiAndPlayer(void)
{
	for (int i = 0; i < m_pKarashi->GetNegiMax(); i++) {
		if (m_pKarashi->GetKarashi(i)->use)
		{
			if (BBCollision_LeftTop2(m_pPlayer->GetPos(), m_pPlayer->GetSize(), m_pKarashi->GetKarashi(i)->pos, m_pKarashi->GetKarashi(i)->size))
			{
				m_pKarashi->SetUse(i, false);

				m_pKarashi->SetEffect(m_pPlayer->GetPos());

				m_pPlayer->SetSpeedUp(true);

				m_pShotString->SetNatto(NRN_KARASHI);

			}
		}
	}
}

