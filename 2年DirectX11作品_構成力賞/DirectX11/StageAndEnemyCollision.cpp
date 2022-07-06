//=============================================================================
//
// ステージとエネミーの衝突処理 [StageAndEnemyCollision.cpp]
// Author : Yanagisawa Yuta
//
// 説明：エネミーがステージに衝突
// ー＞エネミーのベクトルを反転
//=============================================================================
#include "StageAndEnemyCollision.h"


void StageAndEnemyCollision::Init()
{

}

void StageAndEnemyCollision::Uninit()
{
}

void StageAndEnemyCollision::Update()
{
    for (int i = 0; i < m_pEnemy->GetEnemyNumMax(); i++) {
        if (!m_pEnemy)continue;
        if (IsCollisions(i) >= 0) {
            CollisionUpdate(i);
        }
    }
}

void StageAndEnemyCollision::Draw()
{
}

int StageAndEnemyCollision::IsCollisions(int index)
{
    D3DXVECTOR3 e_pos = m_pEnemy->GetObjInfo(index).pos;
    D3DXVECTOR3 e_size = m_pEnemy->GetObjInfo(index).size;

    D3DXVECTOR3 s_pos = m_pStage->GetObjInfo().pos;
    D3DXVECTOR3 s_size = m_pStage->GetObjInfo().size;

    //  X軸方向の壁判定
    if (s_pos.x + s_size.x >= e_pos.x + e_size.x &&
        s_pos.x - s_size.x <= e_pos.x - e_size.x) {
    }
    else {
        m_pEnemy->SetEnemeyVecX(index);
        return index;
    }

    //  Y軸方向の壁判定
    if (s_pos.y + s_size.y >= e_pos.y + e_size.y &&
        s_pos.y - s_size.y <= e_pos.y - e_size.y) {
    }
    else{
        m_pEnemy->SetEnemeyVecY(index);
        return index;
    }

    //  Z軸方向の壁判定
    if (s_pos.z + s_size.z >= e_pos.z + e_size.z &&
        s_pos.z - s_size.z <= e_pos.z - e_size.z) {
    }else
    {
        m_pEnemy->SetEnemeyVecZ(index);
        return index;
    }

    //  あたってなかったら
    return -1;
}

void StageAndEnemyCollision::CollisionUpdate(int  index)
{
    if (index < 0) return ;
    else {
        //m_pEnemy->SetUseFalse(index);
    }



    return ;
}
