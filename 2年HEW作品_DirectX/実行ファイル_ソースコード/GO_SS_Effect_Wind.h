#pragma once
#include "GameObject.h"

#define WIND_X_NUM 5
#define WIND_Y_NUM 6

#define WIND_WIDTH  (1.0f/ WIND_X_NUM)
#define WIND_HEIGHT (1.0f/ WIND_Y_NUM)

class GO_SS_Effect_Wind :
    public GameObject
{
public:


    // GameObject を介して継承されました
    virtual void Initialize(void) override;

    virtual void Finalize(void) override;

    virtual void Update(void) override;

    virtual void Draw(void) override;

    virtual int GetGameScene(void) override { return GAME_SCENE; }

    void SetWindEff(void) { windEff.use = true; }

    void SetWindMoveEff(int num) {
        m_numTImeMax = num;
        windMoveEff.use = true;
    }
    void SetWindMoveEff(void) { windMoveEff.use = true; }


private:
    //ゲームシーン用
    const int GAME_SCENE = GAMESCENE_GAME_TEST;

    //テクスチャ用
    char TEX_NAME[64] = "data/TEXTURE/Wind_Effect_001.png";
    int Eff_Texture;

    char TEX_NAME_WINDMOVE[64] = "data/TEXTURE/wind_move.png";
    int Eff_WindMove_Texture;


    VERTEX_EFF_WIND windEff;
    VERTEX_EFF      windMoveEff;

    int m_numTime;
    int m_numTImeMax;

    bool appear = false;
};

