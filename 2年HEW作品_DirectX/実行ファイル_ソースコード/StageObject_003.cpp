#include "StageObject_003.h"

HRESULT StageObject_003::Init(void)
{
    m_TextureIndex = LoadTexture(m_TextureName);

    m_Vertex.pos = D3DXVECTOR2(SCREEN_WIDTH / 5.0f * 4.0f, SCREEN_HEIGHT / 2.0f+50.0f);
    m_Vertex.size = D3DXVECTOR2(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 3.0f * 2.0f);
    m_Vertex.alpha = 1.0f;
    m_Vertex.use = true;

    m_light.Init();

    return E_NOTIMPL;
}

void StageObject_003::Draw(void)
{
    DrawSpriteColor(m_TextureIndex, m_Vertex.pos.x, m_Vertex.pos.y,
        m_Vertex.size.x, m_Vertex.size.y, 1.0f, 1.0f, 1.0f, 1.0f,
        D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Vertex.alpha));

    m_light.Draw();
}

void StageObject_003::ClickUpdate(void)
{
    if (!IsClick())return;

    SetStageNum(ReturnStageNum());

    //  ステージ3へ
    if (GetFadeState() == FADE_NONE)
    {
        SceneTransition(SCENE_GAME);
    }
}
