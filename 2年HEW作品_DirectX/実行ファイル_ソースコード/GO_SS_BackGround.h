#pragma once
#include "GameObject.h"
class GO_SS_BackGround :
    public GameObject
{
public:
    // GameObject を介して継承されました
    virtual void Initialize(void) override;

    virtual void Finalize(void) override;

    virtual void Update(void) override;

    virtual void Draw(void) override;

    virtual int GetGameScene(void) override {  return GAME_SCENE;  }

    void AddU(FLOAT add) { 
        BackGround_Vertex.u += add * 2.0f / 3.0f; 
        m_uBack             += add / 10.0f;
        m_xNoneLoop         -= add * 500.0f;
        m_uBG               += add / 2.0f;
    }
    void SubU(FLOAT sub) { 
        BackGround_Vertex.u -= sub * 2.0f / 3.0f;
        m_uBack             -= sub / 10.0f;
        m_xNoneLoop         += sub * 500.0f;
        m_uBG               -= sub / 2.0f;
    }

private:
    //テクスチャ用変数

//  TexName
    //  朝
    char* MORNING_BG =          "data/TEXTURE/morning003.png";
    char* MORNING_NONELOOP =    "data/TEXTURE/morning002.png";
    char* MORNING_BUILDING =    "data/TEXTURE/morning001.png";

    //  昼
    char* NOON_BG =         "data/TEXTURE/noon003.png";
    char* NOON_NONELOOP =   "data/TEXTURE/noon002.png";
    char* NOON_BUILDING =   "data/TEXTURE/noon001.png";

    //  夜
    char* NIGHT_BG =                "data/TEXTURE/night004.png";
    char* NIGHT_NONELOOP =          "data/TEXTURE/night003.png";
    char* NIGHT_BUILDING_FRONT =    "data/TEXTURE/night001.png";
    char* NIGHT_BUILDING_BACK =     "data/TEXTURE/night002.png";

//  インデックス
    //  朝
    int m_morning_BG;               //  -> 003
    int m_morning_NoneLoop;         //  -> 002
    int m_morning_Building_Front;   //  -> 001

    //  昼
    int m_noon_BG;              //  -> 003
    int m_noon_NoneLoop;        //  -> 002
    int m_noon_Building_Front;  //  -> 001

    //  夜
    int m_night_BG;             //  -> 004
    int m_night_NoneLoop;       //  -> 003
    int m_night_Building_Front; //  -> 002
    int m_night_Building_Back;  //  -> 001

//  使用するテクスチャの入れ替え

    //  背景
    int m_nowTex_BG;
    
    //  ループ無しのやつ
    int m_nowTex_NoneLoop;

    //  前の建物
    int m_nowTex_Building_Front;

    //  後ろの建物
    int m_nowTex_Building_Back;

    int CmpTexture;
    char CMP_TEX_NAME[128] = "data/TEXTURE/cmp1.png";

    //ゲームシーン用変数
    const int GAME_SCENE = GAMESCENE_BUNGEE_JUMP;

    //頂点座標
    VERTEX_BACKGROUND BackGround_Vertex;

    //  UVのU情報

    /*FrontはBackGround_Vertex.uを使用*/
    FLOAT m_uBG;    
    FLOAT m_uBack;
    FLOAT m_xNoneLoop;

    const FLOAT UV_SCROLL = 0.001f;
};

