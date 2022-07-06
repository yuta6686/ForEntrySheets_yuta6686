#include "GO_SS_Movement.h"
#include "GO_SS_BackGround.h"
#include "GO_SS_ShotString.h"
#include "GO_SS_Player.h"
#include "GO_SS_Target.h"
#include "GO_SS_Wall.h"
#include "GO_SS_Map.h"
#include "GO_SS_Effect_Wind.h"
#include "GO_SS_Goal.h"
#include "GO_SS_KitchenTimer.h"

#include <cmath>

void GO_SS_Movement::Initialize(void)
{
	m_ssCollision.CollisionInit();
}

void GO_SS_Movement::Update(void)
{
	//時間停止処理
	SetTimeDelay();

	Update_PlayerMoveSwitch();


	//当たり判定の更新処理
	m_ssCollision.CollisionUpdate();

	//移動処理
	MovementManager();

	//奈落からの復活
	FromAbyss();
}


void GO_SS_Movement::SetTimeDelay(void)
{
	if (IsMouseRightPressed() && !m_pShotString->IsClickTarget) 
	{
		m_pTimeDelay->SetTimeDelay(true);
	}
	else {
		m_pTimeDelay->SetTimeDelay(false);
	}

	if (m_pTimeDelay->GetTimeDelayFlag()) {
		m_TimeDelay = TIME_DELAY_VALUE;
	}
	else {
		m_TimeDelay = 1.0f;
	}

	m_pShotString->m_TimeDelay = m_TimeDelay;
	m_pTarget->m_TimeDelay = m_TimeDelay;
	m_pPlayer->m_TimeDelay = m_TimeDelay;
}



//-----------------------------------------------------------------------------------------
//	JumpMove_Liner()
//-----------------------------------------------------------------------------------------
//	直線的な動き
//	ターゲットまで直で向かう
//-----------------------------------------------------------------------------------------
void GO_SS_Movement::JumpMove_Liner()
{
	//糸を出したら
	if (!m_pShotString->IsClickTarget || m_pShotString->m_LinerEnd)return;
	//if (!m_pShotString->IsCollTarget)return;

	m_pShotString->SetPos(m_pTarget->GetTarget()[0].pos);

	

	//プレイヤーと糸の角度取得
	m_Angle = m_pShotString->GetAngle();

	if (m_pShotString->GetAngle() < PI / 8.0f) {
		m_pPlayer->IsJump = true;
		m_pShotString->m_LinerEnd = true;
		IsLiner = false;
		return;
	}
	
	
	//重力リセット
	m_pPlayer->SetGravityDefault();

	//プレイヤーのY軸　動き　
	m_pPlayer->AddYPos(-sinf(m_Angle) * 25.0f);

	//背景スクロール処理
	m_pBackGround->SubU(-0.01f);
	m_pMap->MoveMapObject(-10.0f);

	m_pGoal->AddX(-10.0f);

	m_pKitchenTimer->AddX(-10.0f);
	m_pNegi->AddX(-10.0f);
	m_pKarashi->AddX(-10.0f);

	//m_pEffectWind->SetEffTrue();
}

//-----------------------------------------------------------------------------------------
//	JumpMove_Pendulum()
//-----------------------------------------------------------------------------------------
//	振り子のような動き
//	下に動いてから、上に上がる
//-----------------------------------------------------------------------------------------
void GO_SS_Movement::JumpMove_Pendulum()
{
	

	//糸を出したら
	if (!m_pShotString->IsClickTarget)return;

	//重力リセット
	m_pPlayer->SetGravityDefault();


	//プレイヤーの動き
	PlayerMove_Pendulum();

	//背景、ギミックスクロール処理
	BackGroundMovement_Pendulum();

}

void GO_SS_Movement::PlayerMove_Pendulum()
{
	//プレイヤーのY軸　動き　

	//フレームで管理

	//最後のフレームの処理
	if (Pendulum_Counter >= PENDULUM_COUNTER_MAX)
	{
		Pendulum_Counter = 0;

		//最後にジャンプ！
		m_pPlayer->SetGravity(-10.0f);

		IsPendulum = false;

		//元のフラグ解除
		m_pShotString->IsClickTarget = false;

		//糸描画しない
		m_pShotString->SetStringUse(false);

		//風エフェクト
		m_pEffectWind->SetWindEff();

		
	}
	//最初の1フレーム目の処理
	else if (Pendulum_Counter == 1)
	{
		Pendulum_Counter++;

		//	サイドにあたっていない	&&	壁にあたっている　ー＞　床にあたっている
		if (m_pPlayer->IsCollSide < 0 && m_pPlayer->IsColl) {
			//あたっていたらY軸方向に動かさない
		}
		//床にあたっていない
		else {
			FLOAT rot = (Pendulum_Counter * 3.6f);
			m_pPlayer->AddYPos(sinf(rot * RADIAN) * 10.0f);
		}

		//エフェクト
		m_pEffectWind->SetWindMoveEff();
		m_pTarget->SetEff(m_pShotString->IsInsideTarget);
	}
	//	いつもの動き
	else {
		Pendulum_Counter++;
		if (m_pPlayer->IsCollSide < 0 && m_pPlayer->IsColl) {

		}
		else {
			FLOAT rot = (Pendulum_Counter * 3.6f);
			m_pPlayer->AddYPos(sinf(rot * RADIAN) * 10.0f);
			//DebugOut(rot);
		}

		m_pShotString->SetStringUse(true);
	}

}

void GO_SS_Movement::BackGroundMovement_Pendulum()
{
	//プレイヤーと糸の角度取得
	FLOAT angle = m_pShotString->GetAngle();

	//背景スクロール処理
	m_pBackGround->SubU(-0.01f * m_TimeDelay);

	m_pMap->MoveMapObject(-10.0f * m_TimeDelay);

	m_pGoal->AddX(-10.0f * m_TimeDelay);

	m_pKitchenTimer->AddX(-10.0f * m_TimeDelay);

	m_pNegi->AddX(-10.0f * m_TimeDelay);
	m_pKarashi->AddX(-10.0f * m_TimeDelay);
}

void GO_SS_Movement::Update_PlayerMoveSwitch()
{
	/*	プライヤーの挙動	-> 切り替え(PlayerMove　index)
	PLAYERMOVE_LINEAR,
	PLAYERMOVE_PENDULUM,
*/
	
	//PlayerMoveSwitch(PLAYERMOVE_LINEAR);
	//PlayerMoveSwitch(PLAYERMOVE_PENDULUM);


	if (m_pTarget->GetTarget(m_pShotString->m_AimTarget)->pos.y < m_pPlayer->GetPos().y && 
		IsLiner == false && IsPendulum == false ) 
	{
		m_ChaMove = PLAYERMOVE_LINEAR;
	}
	else 
	{	
		m_ChaMove = PLAYERMOVE_PENDULUM;
	}

	/*if (IsLiner || IsPendulum) {
		m_pShotString->m_IsPlayerMove = true;
		
	}*/

	//	次の動き（m_ChaMove）と今までの動き（m_PreMove）を比較
	//	違っていたら、クールタイムが発動
	CheckNowMove();

	PlayerMoveSwitch((PlayerMove)m_NowMove);

	m_PreMove = m_NowMove;
}

void GO_SS_Movement::CheckNowMove()
{
	if (m_PreMove != m_ChaMove) {
		m_ChengeMove = true;
	}

	if (m_ChengeMove) {
		if (m_NowMove == PLAYERMOVE_PENDULUM) 
		{
			m_CoolMax = 120;
		}
		else {
			m_CoolMax = 60;
		}

		if (m_CoolTime >= m_CoolMax) {
			m_CoolTime = 0;
			m_ChengeMove = false;
			m_NowMove = m_ChaMove;
		}
		else {
			m_CoolTime++;
		}
	}
}

void GO_SS_Movement::PlayerMoveSwitch(PlayerMove index)
{
	//プライヤーの動きー＞切り替え可能
	switch (index)
	{
	case PLAYERMOVE_NONE:
		break;
	case PLAYERMOVE_LINEAR:
		JumpMove_Liner();
		break;
	case PLAYERMOVE_PENDULUM:
		JumpMove_Pendulum();
		break;
	case PLAYERMOVE_MAX:
		break;
	default:
		break;
	}
}

void GO_SS_Movement::MovementManager(void)
{
	FLOAT speedUp = m_pPlayer->GetSpeedUp();

	//当たり判定
	//左入力
	if (GetKeyboardPress(DIK_A) && m_pPlayer->IsCollSide != 1)
	{
		m_pBackGround->SubU(BG_SCROLL_SPEED * m_TimeDelay * speedUp);
		m_pMap->MoveMapObject(MAP_OBJ_MOVING_SPEED * m_TimeDelay * speedUp);
		m_pGoal->AddX(GOAL_MOVING_SPEED * m_TimeDelay * speedUp);
		m_pKitchenTimer->AddX(KTIMER_MOVING_SPEED * m_TimeDelay * speedUp);
		m_pNegi->AddX(KTIMER_MOVING_SPEED * m_TimeDelay * speedUp);
		m_pKarashi->AddX(KTIMER_MOVING_SPEED * m_TimeDelay * speedUp);
	}
	//右入力
	if (GetKeyboardPress(DIK_D) && m_pPlayer->IsCollSide != 2)
	{
		m_pBackGround->AddU(BG_SCROLL_SPEED * m_TimeDelay * speedUp);
		m_pMap->MoveMapObject(-MAP_OBJ_MOVING_SPEED * m_TimeDelay * speedUp);
		m_pGoal->AddX(-GOAL_MOVING_SPEED * m_TimeDelay * speedUp);
		m_pKitchenTimer->AddX(-KTIMER_MOVING_SPEED * m_TimeDelay * speedUp);
		m_pNegi->AddX(-KTIMER_MOVING_SPEED * m_TimeDelay * speedUp);
		m_pKarashi->AddX(-KTIMER_MOVING_SPEED * m_TimeDelay * speedUp);
	}

	MovementManager_ForFan();
}

void GO_SS_Movement::MovementManager_ForFan()
{
	switch (m_pFan->GetCollisionNum())
	{
	case FAN_COLL_NONE:
		m_ForFan.SetOnceFlag(false);
		break;
	case FAN_COLL_UP:
		m_ForFan.SetOnceFlag(true);
		m_pPlayer->AddYPos(m_ForFan.GetWindSpeed() * -1.0f);

		break;
	case
	FAN_COLL_LEFT:
		m_ForFan.SetOnceFlag(true);

		//m_pBackGround->AddU(m_ForFan.GetWindSpeed() * m_TimeDelay);
		m_pMap->MoveMapObject(m_ForFan.GetWindSpeed() * m_TimeDelay);
		m_pGoal->AddX(m_ForFan.GetWindSpeed() * m_TimeDelay);
		break;
	default:
		m_ForFan.SetOnceFlag(false);
		break;
	}
}

void GO_SS_Movement::FromAbyss()
{
	if (m_pPlayer->GetPos().y >= SCREEN_HEIGHT) {
		m_pPlayer->SetPosY(0.0f);
		m_pMap->ResetOnce();
	}
}

void GO_SS_Movement::DebugOut(int i)
{
#ifdef _DEBUG	// デバッグ版の時だけAngleを表示する
	wsprintf(GetDebugStr(), WINDOW_CAPTION);
	wsprintf(&GetDebugStr()[strlen(GetDebugStr())], " rot:%d", i);

	SetWindowText(GethWnd()[0], GetDebugStr());
#endif
}





