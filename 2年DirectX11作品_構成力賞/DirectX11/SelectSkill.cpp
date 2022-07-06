//=============================================================================
//
// スキル選択 [SelectSkill.cpp]
// Author : Yanagisawa Yuta
//
// 説明：経験値を一定数獲得すると、スキル選択状態へ遷移する。
//		その状態のときに、2つのスキルを抽選し、プレイヤーに選択させる
//		抽選では同じスキルが被らないように施されている
//=============================================================================
#include "SelectSkill.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "sprite.h"




void SelectSkill::Init()
{
	m_SkillManager = GetSkillManager_Scene();

	m_once = true;

	m_PosSize1.pos = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 };
	m_PosSize1.size = { SCREEN_WIDTH / 3.0f, SCREEN_WIDTH / 3.0f };

	m_PosSize2.pos = { SCREEN_WIDTH / 4 * 3, SCREEN_HEIGHT / 2 };
	m_PosSize2.size = { SCREEN_WIDTH / 3.0f, SCREEN_WIDTH / 3.0f };
}

void SelectSkill::Uninit()
{
	
}

void SelectSkill::Update()
{
	//	最初に一回抽選する
	//	スキル2つを抽選
	if (m_once) {
		m_once = false;
		m_RandIndex1 = 0;
		m_RandIndex2 = 0;

		while (m_RandIndex1 == m_RandIndex2) {
	
			//	スキル抽選
			m_RandIndex1 = LotteryIndex();
			m_RandIndex2 = LotteryIndex();

			//	スキルのアイコンのテクスチャを設定
			m_TexIndex1 = m_SkillManager->GetSkill(m_RandIndex1)->GetTexIndex();
			m_TexIndex2 = m_SkillManager->GetSkill(m_RandIndex2)->GetTexIndex();

		}
	}

#ifdef _DEBUG	
	//	とりあえず残しとく
	if (GetKeyboardTrigger(DIK_RETURN)
		&& GetFadeState() == FADE_NONE) {
		m_once = true;
	}	
#endif
	

	//　クリックした方のm_RandIndexを返す
	int iscl = Click();

	//	クリックしていなかったら、｜｜　クリックしたけど、あたっていなかったら-1を返す
	if (iscl >= 0) {
		m_SkillManager->GetSkill(iscl)->AddSelectedNum();

		//	UIに追加

		FLOAT xpos = UI_FIRST_POS_X + ((GetUIManager()->GetListSize()) % WIDTH_NUM) * UI_MARGIN_X;
		FLOAT ypos = UI_FIRST_POS_Y + ((GetUIManager()->GetListSize()) / WIDTH_NUM) * UI_MARGIN_Y;

		GetUIManager()->Add(
			new UserInterface_new(m_SkillManager->GetSkill(iscl)->GetTexIndex(),
				xpos, ypos));

		ChangeSelectSkillState(false);

		GetClearEffect()->SetEffect(true);
		m_once = true;
	}


	
}

void SelectSkill::Draw()
{
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_TexIndex1));

	DrawSprite(m_TexIndex1, m_PosSize1.pos.x, m_PosSize1.pos.y, m_PosSize1.size.x, m_PosSize1.size.y,
		1.0f, 1.0f, 1.0f, 1.0f);

	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_TexIndex2));

	DrawSprite(m_TexIndex2, m_PosSize2.pos.x, m_PosSize2.pos.y, m_PosSize2.size.x, m_PosSize2.size.y,
		1.0f, 1.0f, 1.0f, 1.0f);
}

int SelectSkill::Click()
{
	

	if (IsMouseLeftTriggered()) 
	{

		mPos = { (FLOAT)GetMousePosX(),(FLOAT)GetMousePosY() };


		if (IsClick(m_PosSize1)) 
		{			
			return m_RandIndex1;
		}

		if (IsClick(m_PosSize2)) 
		{
			return m_RandIndex2;
		}
	}

	
	return -1;
}

bool SelectSkill::IsClick(PosSize2 posize)
{
	if (mPos.x > posize.pos.x - posize.size.x &&
		mPos.x < posize.pos.x + posize.size.x) 
	{
		if (mPos.y > posize.pos.y - posize.size.y &&
			mPos.y < posize.pos.y + posize.size.y) 
		{
			return true;
		}
	}

	return false;
}
