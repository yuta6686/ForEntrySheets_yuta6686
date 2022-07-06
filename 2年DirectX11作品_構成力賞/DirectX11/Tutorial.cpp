//-------------------------------
//	[Tutorial.cpp]	
//-------------------------------
//	create -> 柳澤優太
//	
//-------------------------------
#include "Tutorial.h"
#include "input.h"
#include "Texture.h"
#include "sprite.h"	
#include "fade.h"

void Tutorial::TutorialTextureLoad()
{
	m_TexIndex_001 = LoadTexture(m_TexName_001);
	m_TexIndex_002 = LoadTexture(m_TexName_002);
	m_TexIndex_003 = LoadTexture(m_TexName_003);
	m_TexIndex_004 = LoadTexture(m_TexName_004);
	m_TexIndex_005 = LoadTexture(m_TexName_005);

	//	↓中村書いて

	//	音源のロードもしてる
	m_Music = LoadSound(m_MusName);

	SetVolume(m_Music, 0.5f);

	PlaySound(m_Music, 256);



	//	↑中村書いて
}

void Tutorial::Uninit()
{
	//この中には処理を書かないでください
	//関数の中に書いてください

	//ここはいらないかも？

	StopSound(m_Music);

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

void Tutorial::TutorialInit_005()
{
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

void Tutorial::TutorialUpdate_005()
{
}



void Tutorial::TutorialUpdate_Max()
{
	//ここでゲームシーンへ遷移
	if (GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_GAME);

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

void Tutorial::TutorialDraw_005()
{
	if (m_Obj[TUTORIAL_005].use) {
		DrawSpriteLeftTop(m_TexIndex_005, m_Obj[TUTORIAL_005].pos.x, m_Obj[TUTORIAL_005].pos.y,
			m_Obj[TUTORIAL_005].size.x, m_Obj[TUTORIAL_005].size.y,
			0.0f, 0.0f, 1.0f, 1.0f);
	}
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
	TutorialInit_005();

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
	case TUTORIAL_005:
		TutorialUpdate_005();
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
		IsMouseLeftTriggered() &&
		GetFadeState() == FADE_NONE)
	{
		if (m_nowPage > TUTORIAL_MAX) {
			m_nowPage = TUTORIAL_MAX;
		}
		else {
			m_nowPage++;

			GetSEManager()->PlaySE(SE_PAGE, 2.0f);
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
	case TUTORIAL_005:
		TutorialDraw_005();
		break;
	default:
		break;
	}
}