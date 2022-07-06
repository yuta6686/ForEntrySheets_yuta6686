//=============================================================================
//
// 射程上昇スキル [Skill_Range.h]
// Author : Yanagisawa Yuta
//
// 説明：射程をリングで表示
//=============================================================================
#pragma once
#include "Skill.h"
class Skill_Range :
    public Skill
{
private:
    const float RANGE_FACTOR = 0.5f;
    const float RANGE_DEFAULT = 500.0f;
public:
    // Skill を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;


    // Skill を介して継承されました
    virtual int ReturnIndex(void) override
    {
        return SKILL_RANGE;
    }

    virtual FLOAT GetValue() override
    {
        return m_range;
    }
    
    virtual void ChangeValue(FLOAT value) override 
    {
        m_range = value;
    }

private:
    FLOAT m_range;

    char m_pModelName[64] = "data/MODEL/range.obj";
    
    char m_TexName[64] = "data/TEXTURE/RangeUp2.png";

    

};

