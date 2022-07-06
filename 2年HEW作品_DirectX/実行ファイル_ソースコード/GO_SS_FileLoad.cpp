#include "GO_SS_FileLoad.h"
#include "StageObject.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;


void GO_SS_FileLoad::Initialize(void)
{

}

void GO_SS_FileLoad::Finalize(void)
{

}

void GO_SS_FileLoad::Update(void)
{
}

void GO_SS_FileLoad::Draw(void)
{
}

void GO_SS_FileLoad::MapFileLoad(int MapData[][STAGE_WALL_NUM_X])
{
	ifstream ifs;	//ファイルストリーム
	switch (GetStageNum())
	{
	case STAGE_NUM_001:
		 ifs.open("data/MapData1.csv");	//ファイルストリーム
		break;
	case STAGE_NUM_002:
		 ifs.open("data/MapData2.csv");	//ファイルストリーム
		break;
	case STAGE_NUM_003:
		 ifs.open("data/MapData3.csv");	//ファイルストリーム
		break;
	}

	string str;					//分割する為のstring
	//int x = 0;					
	//int y = 0;

	//エラー
	if (!ifs)
	{
		cerr << "error" << endl;
	}

	//取り出し
	//while (getline(ifs, str))
	for (int y = 0; y < STAGE_WALL_NUM_Y, getline(ifs, str); y++)
	{
		//分解格納用
		string token;

		//入出力用変換
		istringstream iss(str);

		//while (getline(iss, token, ','))
		for (int x = 0; x < STAGE_WALL_NUM_X, getline(iss, token, ','); x++)
		{
			MapData[y][x] = stoi(token.c_str());
		}
	}
	ifs.close();
}