//=============================================================================
//
//  UIを管理[UserInterface.h]
// Author : Yanagisawa Yuta
//
// 説明：UIに使用するものの処理をここで行う
// モデル出力Ver
// DrawSpriteなどの処理で２D描画する場合、最後に描画する必要があるため。
//=============================================================================
#pragma once
#include "GameObject.h"
#include "ExperiencePoint.h"



class UserInterface :public GameObject
{
public:
	// GameObject を介して継承されました
	virtual void Init() override;

	virtual void Uninit() override;

	virtual void Update() override;

	virtual void Draw() override;

	ExperiencePoint* GetEXP() { return &m_EXP; }
private:
	//  経験値
	ExperiencePoint m_EXP;



};

