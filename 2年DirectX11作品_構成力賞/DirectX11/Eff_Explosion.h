//=============================================================================
//
// ”š”­ƒGƒtƒFƒNƒg [Eff_Explosion.h]
// Author : Yanagisawa Yuta
//
// à–¾Fc‰¡‚Ì‰~Œ`aŒ‚‚ªŠg‘å‚³‚ê‚Ä‚¢‚­
//=============================================================================
#pragma once
#include "GO_Effect.h"
class Eff_Explosion :
    public GO_Effect
{
private:
    //char m_TexName[64] = "data/TEXTURE/";
    static const int EXPLOSION_TIME = 120;
public:
    // GO_Effect ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void SetEffect() override;

    virtual void SetEffect(D3DXVECTOR3 pos) override;

private:
    DX11_MODEL  m_ModelCircle;
    char        m_TexNameCircle[64] = "data/MODEL/circle.obj";
    int         m_TexIndexCircle;

    // GO_Effect ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void SetEffect(bool IsStart) override;
};

