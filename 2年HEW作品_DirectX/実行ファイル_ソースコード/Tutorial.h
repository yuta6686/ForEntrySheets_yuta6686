#pragma once
//-------------------------------
//	[Tutorial.cpp]	
//-------------------------------
//	create -> 柳澤優太
//	change -> 中村
//	
//-------------------------------
#include "main.h"

struct TUTORIAL_INFO 
{
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;

	bool use;
};

//	ページ管理
enum TUTORIAL {
	TUTORIAL_NONE,
	TUTORIAL_001,
	TUTORIAL_002,
	TUTORIAL_003,
	TUTORIAL_004,
	TUTORIAL_MAX,
};

class Tutorial
{

private:	//	ヘッダー内で値を定義する変数はここに書く

	//ページ管理変数
	int m_nowPage = TUTORIAL_001;

	char* m_TexName_001 = "data/TEXTURE/Tutorial_001.png";
	char* m_TexName_002 = "data/TEXTURE/Tutorial_002.png";
	char* m_TexName_003 = "data/TEXTURE/Tutorial_003.png";
	char* m_TexName_004 = "data/TEXTURE/Tutorial_004.png";

	
	

	//	↓中村書いて







	//	↑中村書いて

private:
	//	↓中村書いて







	//	↑中村書いて
private:
	//	↓柳澤が書いた
//	メンバ変数	

	//	頂点データ
	TUTORIAL_INFO m_Obj[TUTORIAL_MAX];

	//	テクスチャーの保存用変数
	int m_TexIndex_001;
	//int m_TexIndex_001_hoge;
	int m_TexIndex_002;
	int m_TexIndex_003;
	int m_TexIndex_004;

//	メンバ関数

	//	テクスチャロード
	void TutorialTextureLoad();

//-------------------------------
//	Init
//-------------------------------
	void TutorialInit_001();
	void TutorialInit_002();
	void TutorialInit_003();
	void TutorialInit_004();

//-------------------------------
//	Update
//-------------------------------
	void TutorialUpdate_001();
	void TutorialUpdate_002();
	void TutorialUpdate_003();
	void TutorialUpdate_004();
	void TutorialUpdate_Max();

	void ObjUseManag();
//-------------------------------
//	Draw
//-------------------------------
	void TutorialDraw_001();
	void TutorialDraw_002();
	void TutorialDraw_003();
	void TutorialDraw_004();


//	パブリックは基本書かない！
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};


