#pragma once
#include "GameObject.h"
class GO_SS_TimeDelay :
    public GameObject
{
private:
    const int TIME_DELAY_LIMIT = 60 * 5;
public:
    virtual void Initialize(void) override;

    virtual void Finalize(void) override;

    virtual void Update(void) override;

    virtual void Draw(void) override;

    virtual int GetGameScene(void) override { return GAMESCENE_GAME_TEST; }



    void SetTimeDelay(bool flag) { m_TimeDelayFlag = flag; }
    bool GetTimeDelayFlag(void) { return m_TimeDelayFlag; }

private:
    bool m_TimeDelayFlag = false;

    VERTEX_ALL_EFFECT m_eTimeDelay;

    float m_PointOfExtinction;

    int ConcentrationLineTexture;
    char TEX_NAME[64] = "data/TEXTURE/èWíÜê¸3.png";

};

