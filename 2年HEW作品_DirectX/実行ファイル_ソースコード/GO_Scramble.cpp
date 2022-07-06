//---------------------------
//Vortex　＝　うずまき
//---------------------------
//	[GameFramework.cpp]
//	Yuta Yanagisawa 
//---------------------------
//	納豆混ぜるシーン（主に描画）
//

#include "GO_Scramble.h"
#include "Texture.h"
#include "sprite.h"


void GO_Scramble::Initialize(void)
{
	Vortex_Vertex.pos = D3DXVECTOR2(SCEREN_WIDTH_HURF, SCEREN_HEIGHT_HURF);
	Vortex_Vertex.vel = D3DXVECTOR2(0.0f, 0.0f);
	Vortex_Vertex.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Vortex_Vertex.frame = 0;
	Vortex_Vertex.angle = 0.0f;
	Vortex_Vertex.size = D3DXVECTOR2(500.0f, 500.0f);

	Scramble_texture = LoadTexture(TEX_NAME);
}

void GO_Scramble::Finalize(void)
{
}

void GO_Scramble::Update(void)
{
	/*if (Vortex_Vertex.angle >= 360.0f) {
		Vortex_Vertex.angle = 0.0f;
	}
	else {
		Vortex_Vertex.angle += 1.0f;
	}*/
}

void GO_Scramble::Draw(void)
{
	DrawSpriteColorRotate(Scramble_texture, Vortex_Vertex.pos.x, Vortex_Vertex.pos.y, 
		Vortex_Vertex.size.x, Vortex_Vertex.size.y,
		0.0f, 0.0f, 1.0f, 1.0f, Vortex_Vertex.color, Vortex_Vertex.angle);
}
