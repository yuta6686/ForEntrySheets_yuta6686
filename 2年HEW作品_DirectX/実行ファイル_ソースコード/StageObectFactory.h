#pragma once
//=============================================================================
//
// ステージオブジェクト工場 [StageObjectFactory.h]
// Author :	yuta yanagisawa 
//
//=============================================================================
#include "StageObject_001.h"
#include "StageObject_002.h"
#include "StageObject_003.h"
#include "StageObject_Tutorial.h"
#include "StageObject_GoBack.h"

class StageObectFactory
{
public:
	StageObject_001* Create_001(void){
		return new StageObject_001();
	}

	StageObject_002* Create_002(void) {
		return new StageObject_002();
	}

	StageObject_003* Create_003(void) {
		return new StageObject_003();
	}

	StageObject_Tutorial* Create_Tutorial(void) {
		return new StageObject_Tutorial();
	}

	StageObject_GoBack* Create_GoBack(void) {
		return new StageObject_GoBack();
	}
};

