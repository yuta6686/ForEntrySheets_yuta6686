#include "GO_SS_BackGround.h"
#include "scene.h"
#include "StageObject.h"

void GO_SS_BackGround::Initialize(void)
{
	//  朝
	m_morning_BG = LoadTexture(MORNING_BG);
	m_morning_NoneLoop = LoadTexture(MORNING_NONELOOP);
	m_morning_Building_Front = LoadTexture(MORNING_BUILDING);

	//  昼
	m_noon_BG = LoadTexture(NOON_BG);
	m_noon_NoneLoop = LoadTexture(NOON_NONELOOP);
	m_noon_Building_Front = LoadTexture(NOON_BUILDING);

	//  夜
	m_night_BG = LoadTexture(NIGHT_BG);
	m_night_NoneLoop = LoadTexture(NIGHT_NONELOOP);
	m_night_Building_Front = LoadTexture(NIGHT_BUILDING_FRONT);
	m_night_Building_Back = LoadTexture(NIGHT_BUILDING_BACK);


	//	m_nowTex初期化
	m_nowTex_BG = m_morning_BG;
	m_nowTex_NoneLoop = m_morning_NoneLoop;
	m_nowTex_Building_Back = -1;
	m_nowTex_Building_Front = m_morning_Building_Front;

	CmpTexture = LoadTexture(CMP_TEX_NAME);

	//	頂点情報初期化
	BackGround_Vertex.pos = D3DXVECTOR2(0.0f, 0.0f);
	BackGround_Vertex.size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	BackGround_Vertex.u = 0.5f;

	m_uBG = 0.0f;
	m_uBack = 0.0f;
	m_xNoneLoop = 0.0f;
}

void GO_SS_BackGround::Finalize(void)
{
}

void GO_SS_BackGround::Update(void)
{

	switch (GetStageNum())
	{
	case STAGE_NUM_NONE:
		break;
	case STAGE_NUM_001:
		m_nowTex_BG = m_morning_BG;
		m_nowTex_NoneLoop = m_morning_NoneLoop;
		m_nowTex_Building_Back = -1;
		m_nowTex_Building_Front = m_morning_Building_Front;
		
		break;
	case STAGE_NUM_002:
		m_nowTex_BG = m_noon_BG;

		m_nowTex_NoneLoop = m_noon_NoneLoop;
		m_nowTex_Building_Back = -1;
		m_nowTex_Building_Front = m_noon_Building_Front;
		break;
	case STAGE_NUM_003:
		m_nowTex_BG = m_night_BG;

		m_nowTex_NoneLoop = m_night_NoneLoop;
		m_nowTex_Building_Back = m_night_Building_Back;
		m_nowTex_Building_Front = m_night_Building_Front;
		break;
	case STAGE_NUM_MAX:
		break;
	default:
		break;
	}
}

void GO_SS_BackGround::Draw(void)
{
	//	一番うしろの背景
	DrawSpriteLeftTopColor(m_nowTex_BG, BackGround_Vertex.pos.x, BackGround_Vertex.pos.y,
		BackGround_Vertex.size.x, BackGround_Vertex.size.y,
		m_uBack, 1.0f, 0.5f, 1.0f,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

	//	ループ無し建物
	//if (m_xNoneLoop >= -8000.0f) {
		DrawSpriteLeftTopColor(m_nowTex_NoneLoop, m_xNoneLoop, BackGround_Vertex.pos.y,
			BackGround_Vertex.size.x * 2.0f, BackGround_Vertex.size.y,
			0.0f, 1.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//}

#ifdef _DEBUG	// デバッグ版の時だけAngleを表示する
	sprintf(&GetDebugStr()[strlen(GetDebugStr())], "ループなしのX：%.2f", m_xNoneLoop);

	SetWindowText(GethWnd()[0], GetDebugStr());
#endif

	//	後ろの建物
	//	夜以外は使ってないので	
	//	朝と昼のときはm_nowTex_Building_Backには-1が格納されている
	if (m_nowTex_Building_Back >= 0) {
		DrawSpriteLeftTopColor(m_nowTex_Building_Back, BackGround_Vertex.pos.x, BackGround_Vertex.pos.y,
			BackGround_Vertex.size.x, BackGround_Vertex.size.y,
			m_uBack, 1.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	
	//	前に建物
	DrawSpriteLeftTopColor(m_nowTex_Building_Front, BackGround_Vertex.pos.x, BackGround_Vertex.pos.y,
		BackGround_Vertex.size.x, BackGround_Vertex.size.y,
		BackGround_Vertex.u, 1.0f, 0.5f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

