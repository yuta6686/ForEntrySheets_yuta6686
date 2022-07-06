#include "GO_SS_Goal.h"
#include "game.h"
#include "main.h"
#include "input.h"
#include "fade.h"

void GO_SS_Goal::Initialize(void)
{
	Goal_Texture = LoadTexture(GOAL_TEX_NAME);
	After_Goal_Tex = LoadTexture(AFTER_GOAL_TEX);

	Goal_Vertex.pos = D3DXVECTOR2(-500.0f, 0.0f);
	Goal_Vertex.size = D3DXVECTOR2(180.0f, 200.0f);
	Goal_Vertex.use = true;
}

void GO_SS_Goal::Finalize(void)
{

}

void GO_SS_Goal::Update(void)
{
		
}

void GO_SS_Goal::Draw(void)
{
	if (Goal_Vertex.use)
	{
		DrawSprite(Goal_Texture, Goal_Vertex.pos.x, Goal_Vertex.pos.y,
			Goal_Vertex.size.x, Goal_Vertex.size.y, 1.0f, 1.0f, 1.0f, 1.0f);
	}
	else
	{
		DrawSprite(After_Goal_Tex, Goal_Vertex.pos.x, Goal_Vertex.pos.y,
			Goal_Vertex.size.x, Goal_Vertex.size.y, 1.0f, 1.0f, 1.0f, 1.0f);
	}
}

void GO_SS_Goal::SetGoalPos(D3DXVECTOR2 pos)
{
	Goal_Vertex.pos = pos;
}

void GO_SS_Goal::AddX(FLOAT x)
{
	Goal_Vertex.pos.x += x;
}