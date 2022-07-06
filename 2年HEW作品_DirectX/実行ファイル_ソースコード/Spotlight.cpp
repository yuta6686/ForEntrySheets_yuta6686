#include "Spotlight.h"
#include "Texture.h"
#include "sprite.h"

void Spotlight::Init()
{
	m_TexIndex = LoadTexture(m_TexName);
}

void Spotlight::Draw()
{
	if (!m_Illuminate)return;

	SetBlendState(BLEND_MODE_ADD);

	DrawSpriteColor(m_TexIndex, m_pos.x, m_pos.y, m_size.x,m_size.y,
		1.0f, 1.0f, 1.0f, 1.0f, (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)));

	SetBlendState(BLEND_MODE_ALPHABLEND);
}
