#pragma once
#include "GameObject.h"
class GO_Effect :
    public GameObject
{
private:
    static const int EFFECT_NUM_MAX = 300;
public:

    // GameObject ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Init() override=0;
    virtual void Uninit() override=0;
    virtual void Update() override=0;
    virtual void Draw() override=0;

    virtual void SetEffect() = 0;
    virtual void SetEffect(bool IsStart) = 0;
    virtual void SetEffect(D3DXVECTOR3 pos) = 0;

    

    virtual int SetEffects()
    {
        for (int i = 0; i < EFFECT_NUM_MAX; i++) {
            if (m_Objs[i].use == true)continue;
            m_Objs[i].use = true;
            return i;
        }
        return -1;
    }

    virtual int SetEffects(D3DXVECTOR3 pos)
    {
        for (int i = 0; i < EFFECT_NUM_MAX; i++) {
            if (m_Objs[i].use == true)continue;
            m_Objs[i].use = true;
            m_Objs[i].pos = pos;
            m_Objs[i].scl = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
            m_Objs[i].col.a = 1.0f;
            m_Objs[i].counter = 0;
            
            return i;
        }
        return -1;
    }

    virtual int SetEffects(D3DXVECTOR3 pos,float xrot)
    {
        for (int i = 0; i < EFFECT_NUM_MAX; i++) {
            if (m_Objs[i].use == true)continue;
            m_Objs[i].use = true;
            m_Objs[i].pos = pos;
            m_Objs[i].scl = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
            m_Objs[i].col.a = 1.0f;
            m_Objs[i].counter = 0;
            m_Objs[i].rot.x = xrot;
            return i;
        }
        return -1;
    }

    void SetEffectsUse(int index, bool flag) { m_Objs[index].use = flag; }
    void SetEffectUse(bool flag) { m_Obj.use = flag; }

    int GetEffectNumMax() { return EFFECT_NUM_MAX; }

    GAME_OBJECT* GetObjs(int index) { return &m_Objs[index]; }
protected:
    GAME_OBJECT m_Objs[EFFECT_NUM_MAX];
    GAME_OBJECT m_Obj;
    int m_TexIndex;
};

