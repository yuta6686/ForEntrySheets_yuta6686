#include "GO_SS_KitchenTimer.h"
#include "Texture.h"
#include "sprite.h"
#include "game.h"
#include "main.h"
#include "input.h"
#include "fade.h"


void GO_SS_KitchenTimer::Initialize(void)
{
	KitchenTimer_Texture = LoadTexture(KTIMER_TEX_NAME);


	for (int i = 0; i < KICHENTIMER_MAX; i++) 
	{
		KitchenTimer_Vertex[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		KitchenTimer_Vertex[i].size = D3DXVECTOR2(180.0f, 200.0f);
		KitchenTimer_Vertex[i].use = false;
	}
	
	//for (int i = 0; i < 50; i++) {
	//	SetKTimer(D3DXVECTOR2(800.0f*i, 300.0f));
	//}
	
}

void GO_SS_KitchenTimer::Finalize(void)
{

}

void GO_SS_KitchenTimer::Update(void)
{
	
}

void GO_SS_KitchenTimer::Draw(void)
{
	for (int i = 0; i < KICHENTIMER_MAX; i++) {
		if (KitchenTimer_Vertex[i].use)
		{
			DrawSprite(KitchenTimer_Texture, KitchenTimer_Vertex[i].pos.x, KitchenTimer_Vertex[i].pos.y,
				KitchenTimer_Vertex[i].size.x, KitchenTimer_Vertex[i].size.y, 1.0f, 1.0f, 1.0f, 1.0f);
		}
	}
	
}

void GO_SS_KitchenTimer::AddX(FLOAT x)
{
	for (int i = 0; i < KICHENTIMER_MAX; i++) {
		if (KitchenTimer_Vertex[i].use)
		{
			KitchenTimer_Vertex[i].pos.x += x;

		}
	}
}