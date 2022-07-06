/*-----------------------------------------------------------------------
*	プレイヤーがバンジージャンプをする	[Bungee.cpp]
*										Author : Yangaisawa
-----------------------------------------------------------------------*/
#include "GO_Bungee.h"

void GO_Bungee::Initialize(void)
{
	Player_Texture = LoadTexture(TEX_NAME);

	Player_Vertex.pos = D3DXVECTOR2(SCREEN_WIDTH/4, -100.0f);
	Player_Vertex.size = D3DXVECTOR2(200.0f, 200.0f);

	m_Gravity = DEFAULT_GRAVITY;
}

void GO_Bungee::Finalize(void)
{
}

void GO_Bungee::Update(void)
{
	if (GetKeyboardTrigger(DIK_SPACE) && Player_Vertex.pos.y >= SCREEN_HEIGHT/4) {
		m_Gravity = DEFAULT_GRAVITY * m_Jump;
	}
	
	m_Gravity += GRAVITY_ACCELERATION;
	Player_Vertex.pos.y += m_Gravity;
}

void GO_Bungee::Draw(void)
{
	DrawSprite(Player_Texture,Player_Vertex.pos.x, Player_Vertex.pos.y,
		Player_Vertex.size.x, Player_Vertex.size.y, 1.0f, 1.0f, 1.0f, 1.0f);
}

