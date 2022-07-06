//=============================================================================
//
// ステージ選択画面処理 [SelectStage.h]
// Author :	yuta yanagisawa 
//
//=============================================================================
#pragma once

#include "StageObectFactory.h"
#include "EffectFactory.h"
#include "StageObjectArrowKey.h"
#include "Spotlight.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************




//*****************************************************************************
// クラス
//*****************************************************************************

class StageObject;
class Effect;


class SelectStage {
public:
	SelectStage();
	~SelectStage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Create(void);

	void Click(void);
	void MouseOver(void);

private:
	static const int STAGE_OBJECT_MAX = 5;

	StageObject* m_pStageObjects[STAGE_OBJECT_MAX];

	static const int EFFECT_MAX = 3;

	Effect* m_effect[EFFECT_MAX];


	StageObectFactory	m_SO_Factory;
	EffectFactory		m_EF;
	StageObjectArrowKey m_SO_ArrowKey;
	Spotlight			m_Spotlight;

	void IlluminateUpdate(void);
	void ToSelectStage(void);

	int m_TexIndex_bg;
	char* m_pTexName = "data/TEXTURE/haikei2.png";

	float m_BackGround_u;
};