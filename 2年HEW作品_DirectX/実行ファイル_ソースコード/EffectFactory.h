#pragma once
#include "E_Prizum.h"

class EffectFactory
{
public:
	E_Prizum* Create(void) {
		return new E_Prizum();
	}

};

