#pragma once
#include "GameObject.h"


class GO_Scramble :
    public GameObject
{
public:
    // GameObject ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Initialize(void) override;

    virtual void Finalize(void) override;

    virtual void Update(void) override;

    virtual void Draw(void) override;

    virtual int GetGameScene(void) override { return m_GameScene; }


    void SetScrambleAngle(float angle) { Vortex_Vertex.angle = angle; }

    D3DXVECTOR2 GetScramblePos(){return Vortex_Vertex.pos;}

private:
    char TEX_NAME[128] = "data/TEXTURE/Vortex.png";

    int Scramble_texture;

    const int m_GameScene = GAMESCENE_SCRAMBLE;

    VERTEX_A Vortex_Vertex;
};

