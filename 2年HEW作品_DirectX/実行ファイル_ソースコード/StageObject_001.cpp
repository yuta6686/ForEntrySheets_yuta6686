#include "StageObject_001.h"


HRESULT StageObject_001::Init(void)
{
    m_TextureIndex = LoadTexture(m_TextureName);

    m_Vertex.pos = D3DXVECTOR2(SCREEN_WIDTH/5, SCREEN_HEIGHT / 2 + 50.0f);
    m_Vertex.size = D3DXVECTOR2(SCREEN_WIDTH / 4, SCREEN_HEIGHT/3*2);
    m_Vertex.alpha = 1.0f;
    m_Vertex.use = true;

	m_light.Init();

    return E_NOTIMPL;
}

void StageObject_001::Uninit(void)
{
}

void StageObject_001::Update(void)
{
    m_MousePos.x = GetMousePosX();
    m_MousePos.y = GetMousePosY();
}

void StageObject_001::Draw(void)
{
    DrawSpriteColor(m_TextureIndex, m_Vertex.pos.x, m_Vertex.pos.y,
        m_Vertex.size.x, m_Vertex.size.y, 1.0f, 1.0f, 1.0f, 1.0f,
        D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Vertex.alpha));

	m_light.Draw();
}

bool StageObject_001::IsClick(void)
{
	D3DXVECTOR2 min1, max1;

	min1.x = m_Vertex.pos.x - m_Vertex.size.x / 2;
	min1.y = m_Vertex.pos.y - m_Vertex.size.y / 2;
	max1.x = m_Vertex.pos.x + m_Vertex.size.x / 2;
	max1.y = m_Vertex.pos.y + m_Vertex.size.y / 2;


	//X軸の判定
	if (min1.x < m_MousePos.x && max1.x > m_MousePos.x)
	{
		//Y軸の判定
		if (min1.y < m_MousePos.y && max1.y > m_MousePos.y)
		{

			if (IsMouseLeftTriggered()) {
				//全ての条件がTRUEならヒット判定
				return true;
			}
		}
	}
	return false;
}

void StageObject_001::ClickUpdate(void)
{
	if (!IsClick())return;

	SetStageNum(ReturnStageNum());

	//	ステージ1へ
	if (GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_GAME);
	}
}

bool StageObject_001::IsMouseOver(void)
{
	D3DXVECTOR2 min1, max1;

	min1.x = m_Vertex.pos.x - m_Vertex.size.x / 2;
	min1.y = m_Vertex.pos.y - m_Vertex.size.y / 2;
	max1.x = m_Vertex.pos.x + m_Vertex.size.x / 2;
	max1.y = m_Vertex.pos.y + m_Vertex.size.y / 2;


	//X軸の判定
	if (min1.x < m_MousePos.x && max1.x > m_MousePos.x)
	{
		//Y軸の判定
		if (min1.y < m_MousePos.y && max1.y > m_MousePos.y)
		{
			//全ての条件がTRUEならヒット判定
			return true;
		}
	}
	return false;
}

void StageObject_001::MouseOverUpdate(void)
{
	if (IsMouseOver()) {
		m_light.SetIlluminate(true,m_Vertex.pos,m_Vertex.size);
	}
	else {
		m_light.SetIlluminate(false, m_Vertex.pos, m_Vertex.size);
	}
}




