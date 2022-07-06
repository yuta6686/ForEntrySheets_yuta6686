#pragma once
#include "GameObject.h"

struct VERTEX_TARGET : public VERTEX_NOMAL {
    //自由に追加して使って
    bool use;
};

class GO_SS_Target :
    public GameObject
{
public:
    // GameObject を介して継承されました
    virtual void Initialize(void) override;

    virtual void Finalize(void) override;

    virtual void Update(void) override;

    virtual void Draw(void) override;

    virtual int GetGameScene(void) override { return GAME_SCENE; }


    void SetTarget();
    void SetTarget(D3DXVECTOR2 pos);
    void SetTarget(D3DXVECTOR2 pos, D3DXVECTOR2 size);

    void SetEff(int index);

    void SetTargetOnce();

    void AddPosX(FLOAT x);

    VERTEX_TARGET* GetTarget(void) { return &Target_Vertex[0]; }
    VERTEX_TARGET* GetTarget(int index) { return &Target_Vertex[index]; }

    int GetTargetNumMax(void) { return TARGET_NUM_MAX; }

    void ResetOnce(void) { 
        for (int i = 0; i < TARGET_NUM_MAX; i++) {
            Target_Vertex[i].use = false;
        }
        once = true; 
    }

    FLOAT m_TimeDelay;

private:
    int Target_Texture;
    char TEX_NAME[128] = "data/TEXTURE/target1.png";

    int Target_Eff;
    char TE_TEX_NAME[128] = "data/TEXTURE/eff_target.png";

    //ゲームシーン
    const int GAME_SCENE = GAMESCENE_GAME_TEST;

    //テクスチャ用変数
    const int TARGET_NUM_X = 16;
    const int TARGET_NUM_Y = 9;

    const float TARGET_WIDTH = SCREEN_WIDTH / TARGET_NUM_X * 2.0f;
    const float TARGET_HEIGHT = SCREEN_HEIGHT / TARGET_NUM_Y * 2.0f;


    //
    static const int TARGET_NUM_MAX = 50;
    VERTEX_TARGET Target_Vertex[TARGET_NUM_MAX];
    VERTEX_TARGET_EFF Target_eff[TARGET_NUM_MAX];

    bool once;
};

