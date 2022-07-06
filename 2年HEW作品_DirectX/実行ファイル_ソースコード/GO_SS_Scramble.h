#pragma once
#include "GameObject.h"

#include "GO_SS_Player.h"
#include "GO_SS_NattoRotate.h"

struct VERTEX_SCRAMBLE :VERTEX_NOMAL {
    bool use;

    FLOAT angle;

    D3DXCOLOR color;
};

class GO_SS_Scramble :
    public GameObject
{
private:
    const float DECREASE_PREVIOUS_DIFF = 10000.0f;
public:
    ~GO_SS_Scramble()override;

    // GameObject ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Initialize(void) override;

    virtual void Finalize(void) override;

    virtual void Update(void) override;

    void LastUpdate(void);

    virtual void Draw(void) override;

    virtual int GetGameScene(void) override { return m_GameScene; }

    void SetScrambleAngle(float angle) { Vortex_Vertex.angle = angle; }

    D3DXVECTOR2 GetScramblePos(){return Vortex_Vertex.pos;}

    void SetPos(D3DXVECTOR2 pos) { Vortex_Vertex.pos = pos; }

    FLOAT GetPreviousDiff(void);

    void SetNato(void) { m_Natto->SetNatto(); }
    void SetNato(int index) { m_Natto->SetNatto(index); }

private:
    char TEX_NAME[128] = "data/TEXTURE/natto.png";

    int Scramble_texture;

    const int m_GameScene = GAMESCENE_GAME_TEST;

    VERTEX_SCRAMBLE Vortex_Vertex;

    FLOAT m_Diff;

    D3DXVECTOR2 m_PrePos;
    D3DXVECTOR2 m_CurPos;

    GO_SS_NattoRotate* m_Natto;

    //  ÉÅÉìÉoä÷êî
    void NattoRotation();
};

