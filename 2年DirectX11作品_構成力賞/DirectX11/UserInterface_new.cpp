//=============================================================================
//
// UIの新しいやつ [UserInterface_new.cpp]
// Author : Yanagisawa Yuta
//
// 説明：テクスチャ出力Ver
//=============================================================================
#include "UserInterface_new.h"
#include "sprite.h"
void UserInterface_new::Init()
{
}
void UserInterface_new::Uninit()
{
}
void UserInterface_new::Update()
{
}
void UserInterface_new::Draw()
{
	DrawSprite(m_TexIndex, m_x, m_y, m_width, m_height, 1.0f, 1.0f, 1.0f, 1.0f);
}

void UserInterface_new::SetPos(FLOAT x, FLOAT y)
{
	m_x = x;
	m_y = y;
}

void UserInterface_new::SetSize(FLOAT x, FLOAT y)
{
	m_width = x;
	m_height = y;
}
