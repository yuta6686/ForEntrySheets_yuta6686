//=============================================================================
//
// ÉAÉCÉeÉÄçHèÍ [ItemFactory.h]
// Author : Yanagisawa Yuta
//
//=============================================================================
#pragma once
#include "GO_Item.h"
#include "Item_Bullet.h"
#include "DItem_Exp_Point.h"
class ItemFactory
{
public:
	Item_Bullet* CreateBullet(void) { return new Item_Bullet(); }

	DItem_Exp_Point* CreateExpPoint(void) { return new DItem_Exp_Point(); }
};

