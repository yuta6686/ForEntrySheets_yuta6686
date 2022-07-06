//=============================================================================
//
// ÉQÅ[ÉÄèàóù [game.h]
// Author : Yanagiswa Yuta
//
//=============================================================================
#pragma once

#include "SelectSkill.h"
#include "Eff_Clear.h"
#include "UInew_Manager.h"


void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

void ChangeSelectSkillState(bool flag);
bool GetSelectSkillState(void);

Eff_Clear* GetClearEffect();

UInew_Manager* GetUIManager();