//=============================================================================
//
// ステージ工場 [StageFactory.h]
// Author : Yanagisawa Yuta
//
//=============================================================================
#pragma once

#include "GO_Stage_001.h"
#include "StageBackground.h"

class StageFactory
{
public:
	GO_Stage_001* Create_001() {
		return new GO_Stage_001();
	}

	StageBackground* Create_BG() {
		return new StageBackground();
	}
};

