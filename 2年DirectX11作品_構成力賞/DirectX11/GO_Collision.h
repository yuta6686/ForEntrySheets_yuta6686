//=============================================================================
//
// 当たり判定のインタフェース [GO_Collision.h]
// Author : Yanagisawa Yuta
//
//=============================================================================
#pragma once

#include "GameObject.h"

class GO_Collision :
    public GameObject
{
public:
    GO_Collision() {}

    virtual void Init() override=0;

    virtual void Uninit() override=0;

    void Update() override = 0;

    virtual void Draw() override=0;

    virtual bool IsCollision() = 0;
    virtual int IsCollisions(int index) = 0;

    virtual void CollisionUpdate(int index) = 0;

};

