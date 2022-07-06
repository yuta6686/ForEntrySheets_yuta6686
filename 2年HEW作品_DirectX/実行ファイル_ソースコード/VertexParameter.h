//---------------------------
//	[VertexParameter.h]
// --------------------------
//	Author:Yuta Yanagisawa 
//---------------------------

//ここでパラメータ？の整理してください。。。

#pragma once
#include "main.h"

struct VERTEX_T {
	D3DXVECTOR2		pos;	//位置ベクトル
	D3DXVECTOR2		vel;	//速度ベクトル
	D3DXCOLOR		color;	//頂点カラー
	D3DXVECTOR2		size;

	bool use;
};

struct VERTEX_A :public VERTEX_T {
	INT frame;
	FLOAT angle;
};

//基本この下から選ぶ　無かったらNOMALを継承して作る
struct VERTEX_NOMAL {
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
};

struct VERTEX_ANIMATION_USE :public VERTEX_NOMAL {
	bool use;

	FLOAT u;
	FLOAT v;
	int counter;
};


//alpha & use & animation
struct VERTEX_ALPHA_ANIMATION_USE :public VERTEX_NOMAL {
	bool use;
	FLOAT alpha;

	FLOAT u;
	FLOAT v;
	int counter;
};

//uv
struct VERTEX_UV :public VERTEX_NOMAL {
	FLOAT u;
	FLOAT v;
};

struct VERTEX_PLAYER :public VERTEX_NOMAL {
	FLOAT delay;
	
	int frame;

	FLOAT u;
	FLOAT v;
	FLOAT width;
	FLOAT height;
};

struct VERTEX_BACKGROUND :public VERTEX_NOMAL {
	FLOAT u;
};

struct VERTEX_SHOOTSTIRNG :public VERTEX_NOMAL {
	float angle;
	bool use;
};


struct VERTEX_WALL :public VERTEX_NOMAL {
	bool use;
};

struct VERTEX_GOAL :public VERTEX_NOMAL {
	bool use;
};

struct VERTEX_KTIMER :public VERTEX_NOMAL {
	bool use;
};

struct VERTEX_EFF :public VERTEX_NOMAL {
	bool use;

	FLOAT alpha;

	FLOAT u;
	FLOAT v;
};

struct VERTEX_EFF_WIND :public VERTEX_EFF{
	int frame;
};

struct VERTEX_CIRCLE :public VERTEX_NOMAL {
	FLOAT alpha;
};

struct VERTEX_TARGET_EFF {
	FLOAT size;
	FLOAT alpha;

	bool use;
};

struct VERTEX_TITLE_PLAYER : public VERTEX_NOMAL {
	bool use;
	FLOAT angle;
	FLOAT u;
	FLOAT v;
	int frame;
};

struct VERTEX_ALL_EFFECT :public VERTEX_EFF {
	int frame;
};

struct VERTEX_SELECT_STAGE :public VERTEX_NOMAL {
	bool use;
	FLOAT alpha;
};

struct VERTEX_NATTO :public VERTEX_NOMAL {
	bool use;
	FLOAT alpha;
	FLOAT angle;
	FLOAT radius;
	FLOAT rot;

	D3DXVECTOR2 dpos;
};

struct FAN_VARTEX :public VERTEX_NOMAL
{
	bool use;
	bool isWork;
	bool isLeft;
	D3DXVECTOR2 fanB_Pos;
	bool isLink;
};