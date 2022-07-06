/*==============================================================================

   新しいバレット追加スキル [scene.cpp]
                                                         Author :Yanagisawa Yuta
                                                         Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#include "Skill.h"
class Skill_NewBullets :
    public Skill
{
public:
    // Skill を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual int ReturnIndex(void) override { return SKILL_NEWBULLETS; }

    virtual FLOAT GetValue() override { return 1.0f + static_cast<FLOAT>(m_SelectedNum) * 3.0f; }

    virtual void ChangeValue(FLOAT value) override {};

private:
    char m_TexName[64] = "data/TEXTURE/NewBullets.png";


};

