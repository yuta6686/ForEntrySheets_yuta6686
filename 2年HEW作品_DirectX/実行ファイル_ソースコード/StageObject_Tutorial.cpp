#include "StageObject_Tutorial.h"

HRESULT StageObject_Tutorial::Init(void)
{
    m_TextureIndex = LoadTexture(m_TextureName);

    m_Vertex.pos = D3DXVECTOR2(SCREEN_WIDTH /3*2, 100.0f);
    m_Vertex.size = D3DXVECTOR2(SCREEN_WIDTH / 12, SCREEN_HEIGHT / 6);
    m_Vertex.alpha = 1.0f;
    m_Vertex.use = true;

    m_light.Init();

    return E_NOTIMPL;
}

void StageObject_Tutorial::Draw(void)
{
    DrawSpriteColor(m_TextureIndex, m_Vertex.pos.x, m_Vertex.pos.y,
        m_Vertex.size.x, m_Vertex.size.y, 1.0f, 1.0f, 1.0f, 1.0f,
        D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Vertex.alpha));

    m_light.Draw();
}

void StageObject_Tutorial::ClickUpdate(void)
{
    if (!IsClick())return;

    SetStageNum(ReturnStageNum());

    //ÉVÅ[ÉìëJà⁄
    if (GetFadeState() == FADE_NONE)
    {
        SceneTransition(SCENE_TUTORIAL);
    }
}
