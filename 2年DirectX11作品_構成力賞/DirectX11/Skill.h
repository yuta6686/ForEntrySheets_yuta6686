//=============================================================================
//
// スキルのインタフェース [Skill.h]
// Author : Yanagisawa Yuta
//
//=============================================================================
#pragma once
#include "GameObject.h"

enum SKILL {
    SKILL_NONE = -1,
    SKILL_RANGE,
    SKILL_COOLTIME,
    SKILL_ATTACK,
    SKILL_NEWBULLETS,
    SKILL_MAX,
};

class Skill :public GameObject
{
public:

    Skill() {
        m_Obj.pos = { 0.0f,0.0f,0.0f };
        m_Obj.size = { 0.0f,0.0f,0.0f };
        m_Obj.vec = { 0.0f,0.0f,0.0f };
        m_Obj.offset = { 0.0f,0.0f,0.0f };
        m_Obj.rot = { 0.0f,0.0f,0.0f };

        m_Obj.use = false;
        m_Obj.free = false;
        
        m_Obj.col = { 1.0f,1.0f,1.0f,1.0f };
        
        m_Obj.idxShadow = -1;
        m_Obj.counter = 0;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m_Obj.mtxWorld.m[j][i] = 0;
            }
        }
    }
   

    virtual void Init() override=0;

    virtual void Uninit() override=0;

    virtual void Update() override=0;

    virtual void Draw() override=0;

    virtual int ReturnIndex(void) = 0;

    virtual int GetTexIndex(void) {
        return m_TexIndex;
    }

    virtual void SetPos(D3DXVECTOR3 pos) { m_Obj.pos = pos; }

    virtual FLOAT GetValue() = 0;
    virtual void ChangeValue(FLOAT value) = 0;

    virtual void AddSelectedNum() { m_SelectedNum++; }
    virtual void ResetSelectNum() { m_SelectedNum = 0; }
protected:
    DX11_MODEL m_Model;
    GAME_OBJECT m_Obj;
    
    int m_TexIndex = -1;

    //  選ばれた数
    int m_SelectedNum = 0;
};

