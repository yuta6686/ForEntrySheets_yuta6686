//=============================================================================
//
// アイテムを一括管理 [ItemManager.cpp]
// Author : Yanagisawa Yuta
//
// 反省　汎用性的にはよかったけど、使わなかったら意味がない。
//=============================================================================
#include "ItemManager.h"

void ItemManager::Create(void)
{

}


ItemManager::ItemManager()
{
	for (int i = 0; i < ITEM_MAX; i++) {
		m_pItems[i] = nullptr;
	}
}

ItemManager::~ItemManager()
{
	for (int i = 0; i < ITEM_MAX; i++) {
		delete m_pItems[i];
	}
}

void ItemManager::Init()
{
	for (int i = 0; i < ITEM_MAX; i++) {
		if (!m_pItems[i])continue;
		m_pItems[i]->Init();
	}
}

void ItemManager::Uninit()
{
	for (int i = 0; i < ITEM_MAX; i++) {
		if (!m_pItems[i])continue;
		m_pItems[i]->Uninit();
	}
}

void ItemManager::Update()
{
	for (int i = 0; i < ITEM_MAX; i++) {
		if (!m_pItems[i])continue;
		m_pItems[i]->Update();
	}
}

void ItemManager::Draw()
{
	for (int i = 0; i < ITEM_MAX; i++) {
		if (!m_pItems[i])continue;
		m_pItems[i]->Draw();
	}
}

bool ItemManager::mRegister(GO_Item* pItem)
{
	for (int i = 0; i < ITEM_MAX; i++) {
		if (m_pItems[i])continue;
		m_pItems[i] = pItem;
		return true;
	}
	return false;
}

