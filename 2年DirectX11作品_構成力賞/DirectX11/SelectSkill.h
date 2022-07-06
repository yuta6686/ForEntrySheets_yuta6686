//=============================================================================
//
// スキル選択 [SelectSkill.h]
// Author : Yanagisawa Yuta
//
// 説明：経験値を一定数獲得すると、スキル選択状態へ遷移する。
//		その状態のときに、2つのスキルを抽選し、プレイヤーに選択させる
//		抽選では同じスキルが被らないように施されている
//=============================================================================
#pragma once
#include "main.h"

#include "SkillManager.h"
#include "SkillFactory.h"

struct PosSize2 {
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
};

class SelectSkill
{
private:
	static const int WIDTH_NUM = 5;

	const float UI_FIRST_POS_X = 50.0f;

	const float UI_FIRST_POS_Y = 800.0f;

	const float UI_MARGIN_X = 75.0f;
	const float UI_MARGIN_Y = 75.0f;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	SkillFactory m_SkillFactory;
private:
//	メンバ変数
	bool m_once = true;

	int m_RandIndex1 = 0;
	int m_RandIndex2 = 0;

	int m_TexIndex1;
	int m_TexIndex2;

	PosSize2 m_PosSize1;
	PosSize2 m_PosSize2;	

	D3DXVECTOR2 mPos;

	SkillManager* m_SkillManager;

//	メンバ関数
	int LotteryIndex(void) { return rand() % SKILL_MAX; }

	int Click();

	bool IsClick(PosSize2 posize);
};


