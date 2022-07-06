//=============================================================================
//
// スキル管理 [SkillManager.cpp]
// Author : Yanagisawa Yuta
//
// 説明：スキルを登録して一括管理する
//		選択されたスキルを新しく追加することはない。
//=============================================================================
#pragma once
#include "GameObject.h"
#include "Skill.h"
#include "SkillFactory.h"


class SkillManager :
    public GameObject
{
private:
    static const int SKILL_NUM_MAX = 24;
public:
    SkillManager();
    ~SkillManager();

    // GameObject を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    bool Register(Skill* pSkill);

    bool Remove(int index);

    void SetPlayerPos(D3DXVECTOR3 pos);

    Skill* GetSkill(int index) { 
        if (m_pSkills == nullptr)return nullptr;
        return m_pSkills[index]; 
    }
private:
    void Create();

    
    Skill* m_pSkills[SKILL_NUM_MAX];
    
    SkillFactory m_SkillFactory;
};

