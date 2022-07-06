//=============================================================================
//
// 攻撃スキル [Skill_Attack.h]
// Author : Yanagisawa Yuta
//
// テクスチャロードするだけだから、いらなかったかもしれん。
//=============================================================================#pragma once
#include "Skill.h"
class Skill_CoolTime :
    public Skill
{
private:
    char m_TexName[64] = "data/TEXTURE/CoolTime.png";

    static const int DECREASE_COOL_TIME = 5;
public:
    // Skill を介して継承されました
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;
    virtual int ReturnIndex(void) override { return SKILL_COOLTIME; }
    virtual FLOAT GetValue() override { 
        if (m_dCoolTime >= DECREASE_COOL_TIME) {
            m_dCoolTime = 0;
            return DECREASE_COOL_TIME;
        }
        else
            return 0;
    }
    virtual void ChangeValue(FLOAT value) override { m_dCoolTime = (int)value; };

    virtual void AddSelectedNum() 
    {
        m_dCoolTime = DECREASE_COOL_TIME;
    }

    int m_dCoolTime = 0;

    
};

