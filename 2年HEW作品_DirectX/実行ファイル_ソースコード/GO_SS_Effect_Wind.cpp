#include "GO_SS_Effect_Wind.h"
#include "renderer.h"
#include "sound.h"

static int g_SoundIndex = 0;

void GO_SS_Effect_Wind::Initialize(void)
{
    g_SoundIndex = LoadSound("data/BGM/se_nattofly.wav");

    //  windEff初期化
    {
        Eff_Texture = LoadTexture(TEX_NAME);

        windEff.pos     = D3DXVECTOR2(100.0f, 100.0f);
        windEff.size    = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
        windEff.use     = false;
        windEff.alpha   = 1.0f;
        windEff.u       = 0.0f;
        windEff.v       = 0.0f;
        windEff.frame   = 0;
    }

    //  windMoveEff 初期化
    {
        Eff_WindMove_Texture = LoadTexture(TEX_NAME_WINDMOVE);

        windMoveEff.pos     = D3DXVECTOR2(0.0f, 0.0f);
        windMoveEff.size    = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
        windMoveEff.use     = false;
        windMoveEff.alpha   = 1.0f;
        windMoveEff.u       = 0.0f;
        windMoveEff.v       = 0.0f;
    }

    m_numTime = 0;
    m_numTImeMax = 1;
}

void GO_SS_Effect_Wind::Finalize(void)
{

}

void GO_SS_Effect_Wind::Update(void)
{   
    if (windEff.use) {
        if (windEff.frame >= WIND_X_NUM * WIND_Y_NUM)
        {

            windEff.frame = 0;
            windEff.use = false;

            

            //	第一引数ー＞グローバル変数、第二引数ー＞0～1までの数値
            //で音量が設定できます
            SetVolume(g_SoundIndex, 0.5f);

            PlaySound(g_SoundIndex, 0);
        }
        else {
            windEff.frame++;
        }
    }

    if (windMoveEff.use) 
    {
        if (windMoveEff.u >= 5.0f) 
        {
            windMoveEff.u = 0.0f;
            windMoveEff.alpha = 1.5f;

            if (m_numTime >= m_numTImeMax) 
            {
                m_numTime = 0;
                windMoveEff.use = false;
            }
            else {
                m_numTime++;
            }
            
        }

        windMoveEff.u += 0.05f;
        windMoveEff.alpha -= 0.01f;
    }
}

void GO_SS_Effect_Wind::Draw(void)
{
    SetBlendState(BLEND_MODE_ADD);

    if (windEff.use) {
        DrawSpriteLeftTopColor(Eff_Texture, windEff.pos.x, windEff.pos.y,
            windEff.size.x, windEff.size.y,
            windEff.frame % WIND_X_NUM * WIND_WIDTH,
            windEff.frame / WIND_X_NUM * WIND_HEIGHT,
            WIND_WIDTH, WIND_HEIGHT,
            D3DXCOLOR(1.0f, 1.0f, 1.0f, windEff.alpha));
    }

    if (windMoveEff.use) {
        DrawSpriteLeftTopColor(Eff_WindMove_Texture, windMoveEff.pos.x, windMoveEff.pos.y,
            windMoveEff.size.x, windMoveEff.size.y,
            windMoveEff.u, 1.0f, 0.5f, 1.2f,
            D3DXCOLOR(1.0f, 1.0f, 1.0f, windMoveEff.alpha));
    }
    SetBlendState(BLEND_MODE_ALPHABLEND);
}



