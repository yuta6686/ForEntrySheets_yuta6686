//=============================================================================
//
// スキル管理 [SkillManager.cpp]
// Author : Yanagisawa Yuta
//
// 説明：スキルを登録して一括管理する
//		選択されたスキルを新しく追加することはない。
//=============================================================================
#include "SkillManager.h"

SkillManager::SkillManager()
{
	for (int i = 0; i < SKILL_NUM_MAX; i++) 
	{
		m_pSkills[i] = nullptr;
	}

	Create();
}

void SkillManager::Create()
{
	Register(m_SkillFactory.CreateRange());
	Register(m_SkillFactory.CreateCoolTime());
	Register(m_SkillFactory.CreateAttack());
	Register(m_SkillFactory.CreateNewBullets());
}

SkillManager::~SkillManager()
{
	for (int i = 0; i < SKILL_NUM_MAX; i++) {
		delete m_pSkills[i];
	}
}




bool SkillManager::Register(Skill* pSkill)
{
	for (int i = 0; i < SKILL_NUM_MAX; i++) 
	{
		if (m_pSkills[i])continue;
		m_pSkills[i] = pSkill;
		return true;
	}
	return false;
}


void SkillManager::Init()
{
	for (int i = 0; i < SKILL_NUM_MAX; i++) {
		if (m_pSkills[i] == nullptr)continue;
		m_pSkills[i]->Init();
	}
}

void SkillManager::Uninit()
{
	for (int i = 0; i < SKILL_NUM_MAX; i++) {
		if (m_pSkills[i] == nullptr)continue;
		m_pSkills[i]->Uninit();
		m_pSkills[i]->ResetSelectNum();
	}
}

void SkillManager::Update()
{
	for (int i = 0; i < SKILL_NUM_MAX; i++) {
		if (m_pSkills[i] == nullptr)continue;
		m_pSkills[i]->Update();
	}
}

void SkillManager::Draw()
{
	for (int i = 0; i < SKILL_NUM_MAX; i++) {
		if (m_pSkills[i] == nullptr)continue;
		m_pSkills[i]->Draw();
	}
}


bool SkillManager::Remove(int index)
{
	if (m_pSkills[index] == nullptr)return false;

	m_pSkills[index] = nullptr;
	delete m_pSkills[index];

	return true;
}

void SkillManager::SetPlayerPos(D3DXVECTOR3 pos)
{
	for (int i = 0; i < SKILL_NUM_MAX; i++) {
		if (m_pSkills[i] == nullptr)continue;
		m_pSkills[i]->SetPos(pos);
	}
}



