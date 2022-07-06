#pragma once
//=============================================================================
//
// ステージ選択画面オブジェクト_003 [SelectStage.h]
// Author :	yuta yanagisawa 
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "fade.h"
#include "Texture.h"
#include "sprite.h"
#include "input.h"
#include "Spotlight.h"

enum STAGE_NUM {
	STAGE_NUM_NONE = 0,
	STAGE_NUM_001,
	STAGE_NUM_002,
	STAGE_NUM_003,
	STAGE_TUTORIAL,
	STAGE_GOBACK,
	STAGE_NUM_MAX,
};

enum ARROW_KEYS {
	ARROW_KEY_NONE,
	ARROW_KEY_RIGHT,
	ARROW_KEY_LEFT,
	ARROW_KEY_MAX,
};

class StageObject
{
public:
	StageObject() {};


	virtual ~StageObject() {}

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	//クリック処理
	virtual bool IsClick(void) = 0;
	virtual void ClickUpdate(void) = 0;

	//マウスオーバー処理
	virtual bool IsMouseOver(void) = 0;
	virtual void MouseOverUpdate(void) = 0;

	virtual STAGE_NUM ReturnStageNum(void) = 0;

	virtual D3DXVECTOR2 GetPos(void)	{ return m_Vertex.pos; }
	virtual D3DXVECTOR2 GetSize(void)	{ return m_Vertex.size; }

protected:

	VERTEX_SELECT_STAGE m_Vertex;

	Spotlight m_light;

	
};

