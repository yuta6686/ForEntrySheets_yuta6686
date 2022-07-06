//-------------------------------
//	[Tutorial.cpp]	
//-------------------------------
//	create -> 柳澤優太
//	change -> 中村
//	
//-------------------------------
#include "Tutorial.h"
#include "input.h"
#include "Texture.h"
#include "sprite.h"	
#include "fade.h"
#include "sound.h"

static int g_SoundIndex = 0;


void Tutorial::TutorialTextureLoad()
{
	StopSoundAll();

	m_TexIndex_001 = LoadTexture(m_TexName_001);
	m_TexIndex_002 = LoadTexture(m_TexName_002);
	m_TexIndex_003 = LoadTexture(m_TexName_003);
	m_TexIndex_004 = LoadTexture(m_TexName_004);
	
	g_SoundIndex = LoadSound("data/BGM/tutorial.wav");

	//	第一引数ー＞グローバル変数、第二引数ー＞0～1までの数値
	//で音量が設定できます
	SetVolume(g_SoundIndex, 0.5f);

	PlaySound(g_SoundIndex, 256);

	//	↓中村書いて







	//	↑中村書いて
}

//-------------------------------
//	Init
//-------------------------------
void Tutorial::TutorialInit_001()
{
	//	↓中村書いて







	//	↑中村書いて
}

void Tutorial::TutorialInit_002()
{
	//	↓中村書いて







	//	↑中村書いて
}

void Tutorial::TutorialInit_003()
{
	//	↓中村書いて







	//	↑中村書いて
}

void Tutorial::TutorialInit_004()
{
	//	↓中村書いて







	//	↑中村書いて
}


//-------------------------------
//	Update
//-------------------------------
void Tutorial::TutorialUpdate_001()
{
	//	↓中村書いて







	//	↑中村書いて
	
}

void Tutorial::TutorialUpdate_002()
{
	//	↓中村書いて







	//	↑中村書いて

}

void Tutorial::TutorialUpdate_003()
{
	//	↓中村書いて







	//	↑中村書いて
}

void Tutorial::TutorialUpdate_004()
{
	//	↓中村書いて







	//	↑中村書いて
}



void Tutorial::TutorialUpdate_Max()
{
	//ここでゲームシーンへ遷移
	if (GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_SELECT_STAGE);

	}

	//	↓中村書いて







	//	↑中村書いて


}





//-------------------------------
//	Draw
//-------------------------------
void Tutorial::TutorialDraw_001()
{
	if (m_Obj[TUTORIAL_001].use) {
		DrawSpriteLeftTop(m_TexIndex_001, m_Obj[TUTORIAL_001].pos.x, m_Obj[TUTORIAL_001].pos.y,
			m_Obj[TUTORIAL_001].size.x, m_Obj[TUTORIAL_001].size.y,
			0.0f, 0.0f, 1.0f, 1.0f);
	}

	//	↓中村書いて







	//	↑中村書いて
}

void Tutorial::TutorialDraw_002()
{
	if (m_Obj[TUTORIAL_002].use) {
		DrawSpriteLeftTop(m_TexIndex_002, m_Obj[TUTORIAL_002].pos.x, m_Obj[TUTORIAL_002].pos.y,
			m_Obj[TUTORIAL_002].size.x, m_Obj[TUTORIAL_002].size.y,
			0.0f, 0.0f, 1.0f, 1.0f);
	}

	//	↓中村書いて







	//	↑中村書いて
}

void Tutorial::TutorialDraw_003()
{
	if (m_Obj[TUTORIAL_003].use) {
		DrawSpriteLeftTop(m_TexIndex_003, m_Obj[TUTORIAL_003].pos.x, m_Obj[TUTORIAL_003].pos.y,
			m_Obj[TUTORIAL_003].size.x, m_Obj[TUTORIAL_003].size.y,
			0.0f, 0.0f, 1.0f, 1.0f);
	}

	//	↓中村書いて







	//	↑中村書いて
}

void Tutorial::TutorialDraw_004()
{
	if (m_Obj[TUTORIAL_004].use) {
		DrawSpriteLeftTop(m_TexIndex_004, m_Obj[TUTORIAL_004].pos.x, m_Obj[TUTORIAL_004].pos.y,
			m_Obj[TUTORIAL_004].size.x, m_Obj[TUTORIAL_004].size.y,
			0.0f, 0.0f, 1.0f, 1.0f);
	}

	//	↓中村書いて







	//	↑中村書いて
}


void Tutorial::Init()
{
	//オブジェクト情報初期化
	for (int i = 0; i < TUTORIAL_MAX; i++) {
		m_Obj[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		m_Obj[i].size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
		m_Obj[i].use = true;
	}

	//現在ページリセット
	m_nowPage = TUTORIAL_001;

	//テクスチャロード
	TutorialTextureLoad();

	//この中には処理を書かないでください
	//関数の中に書いてください
	TutorialInit_001();
	TutorialInit_002();
	TutorialInit_003();
	TutorialInit_004();


}

void Tutorial::Uninit()
{
	//この中には処理を書かないでください
	//関数の中に書いてください

	//ここはいらないかも？

}

void Tutorial::ObjUseManag()
{
	for (int i = 0; i < TUTORIAL_MAX; i++) {
		if (i == m_nowPage) {
			m_Obj[i].use = true;
		}
		else {
			m_Obj[i].use = false;
		}
	}
}

void Tutorial::Update()
{
	//この中には処理を書かないでください
	//関数の中に書いてください

	//	useフラグ管理
	ObjUseManag();

	switch (m_nowPage)
	{
	case TUTORIAL_001:
		TutorialUpdate_001();
		break;
	case TUTORIAL_002:
		TutorialUpdate_002();
		break;
	case TUTORIAL_003:
		TutorialUpdate_003();
		break;
	case TUTORIAL_004:
		TutorialUpdate_004();
		break;
	case TUTORIAL_MAX:
		TutorialUpdate_Max();
		break;
	default:
		break;
	}

	//	次のページへ
	if (GetKeyboardTrigger(DIK_RETURN) ||
		GetKeyboardTrigger(DIK_SPACE) ||
		IsMouseLeftTriggered())
	{
		if (m_nowPage >= TUTORIAL_MAX) {
			m_nowPage = TUTORIAL_MAX;
		}
		else {
			m_nowPage++;
		}
		
	}
}

void Tutorial::Draw()
{
	//この中には処理を書かないでください
	//関数の中に書いてください
	switch (m_nowPage)
	{
	case TUTORIAL_001:
		TutorialDraw_001();
		break;
	case TUTORIAL_002:
		TutorialDraw_002();
		break;
	case TUTORIAL_003:
		TutorialDraw_003();
		break;
	case TUTORIAL_004:
		TutorialDraw_004();
		break;
	default:
		break;
	}
}