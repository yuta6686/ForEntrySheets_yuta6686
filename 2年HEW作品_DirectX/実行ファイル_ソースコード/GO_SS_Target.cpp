#include "GO_SS_Target.h"
#include "renderer.h"
//’N‚©‚±‚±‚Åì‚Á‚Ä

void GO_SS_Target::Initialize(void)
{
	Target_Texture = LoadTexture(TEX_NAME);

    for (int i = 0; i < TARGET_NUM_MAX; i++) {
        Target_Vertex[i].pos = D3DXVECTOR2(-1000.0f, 00.0f);
        Target_Vertex[i].size = D3DXVECTOR2(TARGET_WIDTH, TARGET_HEIGHT);
        Target_Vertex[i].use = false;

        Target_eff[i].size = TARGET_WIDTH;
        Target_eff[i].alpha = 1.0f;
        Target_eff[i].use = false;
    }

    Target_Eff = LoadTexture(TE_TEX_NAME);

    once = true;
}

void GO_SS_Target::Finalize(void)
{

}

void GO_SS_Target::Update(void)
{
    SetTargetOnce();



    for (int i = 0; i < TARGET_NUM_MAX; i++) {
        if (Target_eff[i].use == false) continue;

        if (Target_eff[i].alpha <= 0.0f) {
            Target_eff[i].alpha = 0.0f;
            Target_eff[i].size = TARGET_WIDTH;
            Target_eff[i].use = false;
        }
        else {
            Target_eff[i].size += 1.5f;
            Target_eff[i].alpha -= 0.05f;
        }
        
    }
}

void GO_SS_Target::Draw(void)
{
    for (int i = 0; i < TARGET_NUM_MAX; i++) {

        if (Target_Vertex[i].use) {
            DrawSprite(Target_Texture, Target_Vertex[i].pos.x, Target_Vertex[i].pos.y,
                Target_Vertex[i].size.x, Target_Vertex[i].size.y, 1.0f, 1.0f, 1.0f, 1.0f);

            SetBlendState(BLEND_MODE_ADD);
            DrawSpriteColor(Target_Eff, Target_Vertex[i].pos.x, Target_Vertex[i].pos.y + 10.0f,
                Target_eff[i].size, Target_eff[i].size, 1.0f, 1.0f, 1.0f,1.0f,
                D3DXCOLOR(1.0f,1.0f,1.0f, Target_eff[i].alpha));
            SetBlendState(BLEND_MODE_ALPHABLEND);
        }


    }

}

void GO_SS_Target::SetTarget()
{
    for (int i = 0; i < TARGET_NUM_MAX; i++) {
        if (Target_Vertex[i].use) continue;
        Target_Vertex[i].use = true;
        break;
    }
    
}

void GO_SS_Target::SetTarget(D3DXVECTOR2 pos)
{
    for (int i = 0; i < TARGET_NUM_MAX; i++) {
        if (Target_Vertex[i].use) continue;
        Target_Vertex[i].pos = pos;
        Target_Vertex[i].use = true;
        break;
    }

}

void GO_SS_Target::SetTarget(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
    for (int i = 0; i < TARGET_NUM_MAX; i++) {
        if (Target_Vertex[i].use) continue;
        Target_Vertex[i].pos = pos;
        Target_Vertex[i].size = size;
        Target_Vertex[i].use = true;
        break;
    }
}

void GO_SS_Target::SetEff(int index)
{
    if (!Target_eff[index].use) {

        Target_eff[index].alpha = 5.0f;
        Target_eff[index].size = TARGET_WIDTH;
        Target_eff[index].use = true;
    }
}

void GO_SS_Target::SetTargetOnce()
{
    if (once) {
        once = false;
       /* SetTarget(D3DXVECTOR2(1000.0f, 300.0f));
        SetTarget(D3DXVECTOR2(2000.0f, 300.0f));*/
    }

}

void GO_SS_Target::AddPosX(FLOAT x)
{
    for (int i = 0; i < TARGET_NUM_MAX; i++) {
        if (!Target_Vertex[i].use)continue;
        Target_Vertex[i].pos.x += x;
    }
}


