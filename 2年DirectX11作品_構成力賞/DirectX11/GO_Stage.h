//=============================================================================
//
// ステージのインタフェース [GO_Stage.h]
// Author : Yanagisawa Yuta
//
//=============================================================================
#pragma once
#include "GameObject.h"
#include "DeployEnemy.h"

#define STAGE_SIZE 200.0f
#define STAGE_X 14.52f
#define STAGE_Y 10.00f
#define STAGE_Z 10.00f


enum STAGE_NUM {
    STAGE_NUM_NONE = 0,
    STAGE_NUM_001,
    STAGE_NUM_002,
    STAGE_NUM_003,
    STAGE_NUM_MAX
};

class GO_Stage :
    public GameObject
{

public:
    virtual void Init() override=0;

    virtual void Uninit() override=0;

    virtual void Update() override=0;

    virtual void Draw() override=0;

    virtual int ReturnIndex()=0;

    GAME_OBJECT GetObjInfo() { return m_Obj; }



private:

    //  敵を倒した数
    int m_DefeatEnemyNum;

protected:
    DX11_MODEL m_Model;
    GAME_OBJECT m_Obj;

};

