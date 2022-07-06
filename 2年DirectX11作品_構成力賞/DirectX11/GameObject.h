//=============================================================================
//
// ゲームオブジェクトのインタフェース [GameObject.h]
// Author : Yanagisawa Yuta
//
//=============================================================================
#pragma once
#include "main.h"
#include "input.h"
#include "camera.h"
#include "texture.h"
#include "model.h"
#include "light.h"


struct GAME_OBJECT 
{
	D3DXVECTOR3		pos;		// 位置
	D3DXVECTOR3		rot;		// 向き(回転)
	D3DXVECTOR3		scl;		// 大きさ(スケール)
	D3DXVECTOR3		offset;		// オフセット座標

	D3DXCOLOR		col;

	float			spd;		// 移動スピード
	
	bool			use;		// 表示フラグ

	bool			free;		//	何かしらで使える

	int				idxShadow;	// 影の識別子
	int				counter;

	D3DXVECTOR3     size;		// 当たり判定用サイズ

	D3DXVECTOR3		vec;

	D3DXMATRIX		mtxWorld;	// ワールドマトリックス
};



class GameObject
{
public:
	GameObject() {}
	

	virtual void Init()=0;
	virtual void Uninit()=0;
	virtual void Update()=0;
	virtual void Draw()=0;


	
	
};

