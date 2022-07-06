#pragma once
#include "GameObject.h"
class GO_SS_Wall :
    public GameObject
{
public:

    // GO_ShootString ??рц??p??????????
    virtual void Initialize(void) override;

    virtual void Finalize(void) override;

    virtual void Update(void) override;

    virtual void Draw(void) override;

    virtual int GetGameScene(void) override;

    static const int GetWallNumMax(void) { return WALL_NUM_MAX; }
    VERTEX_WALL GetvWall(int index) { return m_vWall[index]; }


    void SetWall(D3DXVECTOR2 pos, D3DXVECTOR2 size);

  

    void ResetOnce(void) { 
        for (int i = 0; i < WALL_NUM_MAX; i++) {
            m_vWall[i].use = false;
        }
        once = true; 
    }
    

    void AddX(FLOAT x);
private:
    //?e?N?X?`???p???
    int Wall_Texture;
    char TEX_NAME[128] = "data/TEXTURE/yuka2.png";

    //?Q?[???V?[??
    const int GAME_SCENE = GAMESCENE_GAME_TEST;
    
    //????`
    static const int WALL_NUM_MAX = 2200;

    //???_???
    VERTEX_WALL m_vWall[WALL_NUM_MAX];

    bool once;

    void SetWallOnce();

};

