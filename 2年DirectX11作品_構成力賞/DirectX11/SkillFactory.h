//=============================================================================
//
// ÉXÉLÉãçHèÍ [SkillFactory.h]
// Author : Yanagisawa Yuta
//
//=============================================================================
#pragma once

#include "Skill_Range.h"
#include "Skill_CoolTime.h"
#include "Skill_Attack.h"
#include "Skill_NewBullets.h"

class SkillFactory
{
public:
	Skill_Range* CreateRange() { return new Skill_Range(); }
	Skill_CoolTime* CreateCoolTime() { return new Skill_CoolTime(); }
	Skill_Attack* CreateAttack() { return new Skill_Attack(); }
	Skill_NewBullets* CreateNewBullets() { return new Skill_NewBullets(); }
};

