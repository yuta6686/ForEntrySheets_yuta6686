//---------------------------
//	プレイヤー　[GO_Player.cpp]
//	Yuta Yanagisawa 
//---------------------------
#include "GO_Player.h"



void GO_Player::Initialize(void)
{
	Player_Texture = LoadTexture(PLAYER_TEX_NAME);

	//初期化
	Player_Vertex.pos.x = SCREEN_WIDTH / 2;
	Player_Vertex.pos.y = 440;

	Player_Vertex.size.x = 50.0f;
	Player_Vertex.size.y = 50.0f;

	Player_Vertex.vel.x = 1.0f;
	Player_Vertex.vel.y = 1.0f;

	Player_Vertex.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

}

void GO_Player::Finalize(void)
{
}

void GO_Player::Update(void)
{
	if (GetKeyboardPress(DIK_UP))
		Player_Vertex.pos.y -= 1.0f;

	if (GetKeyboardPress(DIK_DOWN))
		Player_Vertex.pos.y += 1.0f;

	if (GetKeyboardPress(DIK_LEFT))
		Player_Vertex.pos.x -= 1.0f;

	if (GetKeyboardPress(DIK_RIGHT))
		Player_Vertex.pos.x += 1.0f;

	if (IsMouseLeftPressed()) {
		Player_Vertex.pos.x = GetMousePosX();
		Player_Vertex.pos.y = GetMousePosY();
	}
}

void GO_Player::Draw(void)
{
	DrawSprite(Player_Texture, Player_Vertex.pos.x, Player_Vertex.pos.y,
		Player_Vertex.size.x, Player_Vertex.size.y,
		0.0f, 0.0f, 0.5f, 0.5f);
}
