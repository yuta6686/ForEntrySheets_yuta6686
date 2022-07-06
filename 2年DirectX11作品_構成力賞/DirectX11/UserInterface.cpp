//=============================================================================
//
//  UIを管理[UserInterface.cpp]
// Author : Yanagisawa Yuta
//
// 説明：UIに使用するものの処理をここで行う
// モデル出力Ver
// DrawSpriteなどの処理で２D描画する場合、最後に描画する必要があるため。
//=============================================================================
#include "UserInterface.h"

void UserInterface::Init()
{
	m_EXP.Init();
}

void UserInterface::Uninit()
{
	m_EXP.Uninit();
}

void UserInterface::Update()
{
	m_EXP.Update();
}

void UserInterface::Draw()
{
	m_EXP.Draw();
}
