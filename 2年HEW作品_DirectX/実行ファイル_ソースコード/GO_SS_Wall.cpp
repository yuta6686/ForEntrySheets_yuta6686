#include "GO_SS_Wall.h"

void GO_SS_Wall::Initialize(void)
{
    Wall_Texture = LoadTexture(TEX_NAME);

    for (int i = 0; i < WALL_NUM_MAX; i++) {
        m_vWall[i].pos = D3DXVECTOR2(100.0f, 100.0f);
        m_vWall[i].size = D3DXVECTOR2(50.0f, 50.0f);
        m_vWall[i].use = false;
    }
    
    once = true;
}

void GO_SS_Wall::Finalize(void)
{
}

void GO_SS_Wall::Update(void)
{
    SetWallOnce();

}

void GO_SS_Wall::Draw(void)
{
    for (int i = 0; i < WALL_NUM_MAX; i++) {
        if (!m_vWall[i].use)continue;
        DrawSpriteLeftTop(Wall_Texture, m_vWall[i].pos.x, m_vWall[i].pos.y,
            m_vWall[i].size.x, m_vWall[i].size.y, 1.0f, 1.0f, 1.0f, 1.0f);
    }
}

int GO_SS_Wall::GetGameScene(void)
{
    return GAMESCENE_GAME_TEST;
}




void GO_SS_Wall::SetWall(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
    for (int i = 0; i < WALL_NUM_MAX; i++) {
        if (m_vWall[i].use) continue;
        m_vWall[i].pos = pos;
        m_vWall[i].size = size;
        m_vWall[i].use = true;
        break;
    }
}


void GO_SS_Wall::SetWallOnce()
{
    if (once) {
        once = false;
        
        //for (int i = 0; i < WALL_NUM_Y; i++) {
        //    for (int j = 0; j < WALL_NUM_X; j++) {
        //       // SetWall(D3DXVECTOR2( WALL_WIDTH * j,WALL_HEIGHT*i),D3DXVECTOR2(WALL_WIDTH, WALL_HEIGHT));

        //        SetWall(D3DXVECTOR2(WALL_WIDTH * j, WALL_HEIGHT * 15), D3DXVECTOR2(WALL_WIDTH, WALL_HEIGHT));
        //    }
        //   // SetWall(D3DXVECTOR2(WALL_WIDTH * 5, WALL_HEIGHT * i), D3DXVECTOR2(WALL_WIDTH, WALL_HEIGHT));
        //}
        /*for (int i = 0; i < WALL_NUM_X * 5; i++) {
            SetWall(D3DXVECTOR2(WALL_WIDTH * i, WALL_HEIGHT * 8), D3DXVECTOR2(WALL_WIDTH, WALL_HEIGHT));
        }

        for (int i = 0; i < WALL_NUM_Y; i++) {
            SetWall(D3DXVECTOR2(WALL_WIDTH, WALL_HEIGHT * i), D3DXVECTOR2(WALL_WIDTH, WALL_HEIGHT));
        }*/
    }
}

void GO_SS_Wall::AddX(FLOAT x)
{
    for (int i = 0; i < WALL_NUM_MAX; i++) {
        if (!m_vWall[i].use)continue;
        m_vWall[i].pos.x += x;
    }
}


