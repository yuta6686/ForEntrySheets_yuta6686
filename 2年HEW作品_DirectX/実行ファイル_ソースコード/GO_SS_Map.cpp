#include "GO_SS_Map.h"
#include "GO_SS_FileLoad.h"
#include "GO_SS_Wall.h"
#include "GO_SS_Target.h"
#include "GO_SS_Fan.h"
#include "GO_SS_Goal.h"
#include "GO_SS_KitchenTimer.h"
#include "GO_SS_Negi.h"
#include "GO_SS_Player.h"
#include <cstdlib>

//#include "GO_SS_ZipLine.h"

//#define SEEK_ZIP_MAX  5

void GO_SS_Map::Initialize(void)
{
	m_pFileLoad->MapFileLoad(MapData);
	once = true;
}

void GO_SS_Map::Finalize(void)
{
}

void GO_SS_Map::Update(void)
{
	if (once == false)return;
	once = false;

	for (int y = 0; y < STAGE_WALL_NUM_Y; y++)
	{
		for (int x = 0; x < STAGE_WALL_NUM_X; x++)
		{
			switch (MapData[y][x])
			{
			case WALL_NUM:
				m_pWall->SetWall(D3DXVECTOR2(WALL_WIDTH * x, WALL_HEIGHT * y), D3DXVECTOR2(WALL_WIDTH, WALL_HEIGHT));
				break;

			case TARGET_NUM:
				m_pTarget->SetTarget(D3DXVECTOR2(WALL_WIDTH * x, WALL_HEIGHT * y));
				break;

			case FAN_A_NUM:
				//換気扇吸い込み口が来たら吐き出し口を探しに行く
				//ない場合描画しない
				if (SeekFanB(x, y)) 
				{
					m_pFan->SetFan(D3DXVECTOR2(WALL_WIDTH * x, WALL_HEIGHT * y));
				}
				break;

			case FAN_B_UP_NUM:
				break;

			case FAN_B_LEFT_NUM:
				break;

			case GOAL_NUM:
				m_pGoal->SetGoalPos(D3DXVECTOR2(WALL_WIDTH * x, WALL_HEIGHT * y));
				break;
				
			case KITCHEN_TIMER_NUM:
				m_pKTimer->SetKTimer(D3DXVECTOR2(WALL_WIDTH * x, WALL_HEIGHT * y));
				break;

			case NEGI_NUM:
				m_pNegi->SetNegi(D3DXVECTOR2(WALL_WIDTH * x, WALL_HEIGHT * y));
				break;

			case KARASHI_NUM:
				m_pKarashi->SetKarashi(D3DXVECTOR2(WALL_WIDTH * x, WALL_HEIGHT * y));
				break;

			//case ZIPLINE_A_NUM:
			//	//ZIPLINE_A_NUMが来たらBを探しに行く
			//	if (SeekZipLineB(x, y))
			//	{
			//		m_pZipLine->SetZipLine(D3DXVECTOR2(WALL_WIDTH * x, WALL_HEIGHT * y));
			//	}
			//	break;
			}
		}
	}
}

void GO_SS_Map::Draw(void)
{
	
}
//マップオブジェクトの移動
void GO_SS_Map::MoveMapObject(FLOAT x)
{
	if (x > 0)
	{
		if (m_pPlayer->IsCollSide != 1)
		{
			m_pWall->AddX(x);
			m_pTarget->AddPosX(x);
			m_pFan->AddX(x);
		}
	}
	if (x < 0)
	{
		if (m_pPlayer->IsCollSide != 2)
		{
			m_pWall->AddX(x);
			m_pTarget->AddPosX(x);
			m_pFan->AddX(x);
		}
	}
}

void GO_SS_Map::ResetOnce(void)
{
	m_pTarget->ResetOnce();
	m_pWall->ResetOnce();
	m_pFan->ResetOnce();
	once = true;
}

bool GO_SS_Map::SeekFanB(int CurrentNumX, int CurrentNumY)
{
	int nearX = STAGE_WALL_NUM_X, nearY = STAGE_WALL_NUM_Y;
	int absX, absY;
	int total;
	bool disc = false;
	int x, y;

	for (y = 0; y < STAGE_WALL_NUM_Y; y++)
	{
		for (x = 0; x < STAGE_WALL_NUM_X; x++)
		{
			if (MapData[y][x] == FAN_B_UP_NUM || MapData[y][x] == FAN_B_LEFT_NUM)
			{
				absX = abs(CurrentNumX - x);
				absY = abs(CurrentNumY - y);

				total = absX + absY;

				if (total < abs(CurrentNumX -nearX) + abs(CurrentNumY - nearY))
				{
					nearX = x;
					nearY = y;
					disc = true;
				}
			}
		}
	}	
	if (disc)
	{
		if (MapData[nearY][nearX] == FAN_B_UP_NUM)
			m_pFan->LinkFanB(D3DXVECTOR2(WALL_WIDTH * nearX, WALL_HEIGHT * nearY), false);
		if (MapData[nearY][nearX] == FAN_B_LEFT_NUM)
			m_pFan->LinkFanB(D3DXVECTOR2(WALL_WIDTH * nearX, WALL_HEIGHT * nearY), true);

		return true;
	}
	
	return false;
}



//
////ziplineのBを探しに行く関数
//bool GO_SS_Map::SeekZipLineB(int CurrentNumX, int CurrentNumY)
//{
//	int y = CurrentNumY - SEEK_ZIP_MAX;
//	if (y <= 0)	y = 0;
//
//	for (y = CurrentNumY - SEEK_ZIP_MAX; y < CurrentNumY + SEEK_ZIP_MAX; y++)
//	{
//		for (int x = CurrentNumX + 1; x < CurrentNumX + SEEK_ZIP_MAX; x++)
//		{
//			if (MapData[y][x] == ZIPLINE_B_NUM)
//			{
//				m_pZipLine->LinkZipLineB(D3DXVECTOR2(WALL_WIDTH * x, WALL_HEIGHT * y), x - CurrentNumX);
//				return true;
//			}
//		}
//	}
//	return false;
//}