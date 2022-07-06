//=============================================================================
//
// アイテムを一括管理 [ItemManager.h]
// Author : Yanagisawa Yuta
//
// 反省　汎用性的にはよかったけど、使わなかったら意味がない。
//=============================================================================
#pragma once
#include "GameObject.h"
#include "GO_Item.h"

class ItemManager:public GameObject
{
private:
	static const int ITEM_MAX = 20;
public:
	ItemManager();
	~ItemManager();

	// GameObject を介して継承されました
	virtual void Init() override;

	virtual void Uninit() override;

	virtual void Update() override;

	virtual void Draw() override;

	bool mRegister(GO_Item* pItem);

	GO_Item* GetItem(int index) { 
		if (index < 0 || ITEM_MAX <= index)return nullptr;
		if (!m_pItems[index])return nullptr;
		return m_pItems[index]; 
	}

private:
	GO_Item* m_pItems[ITEM_MAX];

	void Create(void);
};

