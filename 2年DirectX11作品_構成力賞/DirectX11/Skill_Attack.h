//=============================================================================
//
// 攻撃スキル [Skill_Attack.h]
// Author : Yanagisawa Yuta
//
// テクスチャロードするだけだから、いらなかったかもしれん。
//=============================================================================
#pragma once
#include "Skill.h"
class Skill_Attack :
    public Skill
{
public:
    // Skill を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual int ReturnIndex(void) override {return SKILL_ATTACK;}

    virtual FLOAT GetValue() override { return static_cast<FLOAT>(m_SelectedNum + 1); }

    virtual void ChangeValue(FLOAT value) override {};

    char m_TexName[64] = "data/TEXTURE/Attack.png";
};

