//=============================================================================
//
// UIマネージャー [UInew_Manager.cpp]
// Author : Yanagisawa Yuta
//
// 説明：UIのインスタンスをListで管理
//		スキルのテクスチャを表示しておくやつ
//=============================================================================
#pragma once
#include "UserInterface_new.h"
#include <list>

class UInew_Manager
{
public:
	UInew_Manager();
	~UInew_Manager();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Add(UserInterface_new* p);

	int GetListSize() { return m_pUIs.size(); }
private:

	std::list<UserInterface_new*> m_pUIs;
};

