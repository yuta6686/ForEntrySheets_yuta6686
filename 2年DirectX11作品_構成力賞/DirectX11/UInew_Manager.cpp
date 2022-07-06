//=============================================================================
//
// UIマネージャー [UInew_Manager.cpp]
// Author : Yanagisawa Yuta
//
// 説明：UIのインスタンスをListで管理
//		スキルのテクスチャを表示しておくやつ
//=============================================================================
#include "UInew_Manager.h"
#include "scene.h"
#include <algorithm>

UInew_Manager::UInew_Manager()
{
	m_pUIs.clear();

}

UInew_Manager::~UInew_Manager()
{

	for (auto x : m_pUIs) {
		delete x;
	}
}

void UInew_Manager::Init()
{

	for (auto x : m_pUIs) {
		x->Init();
	}
}

void UInew_Manager::Uninit()
{

	for (auto x : m_pUIs) {
		x->Uninit();
		delete x;
	}

	m_pUIs.clear();
}

void UInew_Manager::Update()
{
	for (auto x : m_pUIs) {
		x->Update();
	}
}

void UInew_Manager::Draw()
{
	for (auto x : m_pUIs) {
		x->Draw();
	}
}

void UInew_Manager::Add(UserInterface_new* p)
{
	m_pUIs.push_back(p);
}


