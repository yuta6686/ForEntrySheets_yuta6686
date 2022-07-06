#include "StageObjectArrowKey.h"



void StageObjectArrowKey::Update(void)
{
	ArrowKeyUpdate();

	EnterUpdate();
}

void StageObjectArrowKey::Draw(void)
{

}


int StageObjectArrowKey::IsArrowKeyTriggerd(void){
	if (GetKeyboardTrigger(DIK_RIGHTARROW)) {
		return ARROW_KEY_RIGHT;
	}
	else if (GetKeyboardTrigger(DIK_LEFTARROW)) {
		return ARROW_KEY_LEFT;
	}
	else {
		return ARROW_KEY_NONE;
	}

	return ARROW_KEY_NONE;
}

void StageObjectArrowKey::ArrowKeyUpdate()
{
	switch (IsArrowKeyTriggerd())
		{
		case ARROW_KEY_NONE:
			break;
		case ARROW_KEY_RIGHT:
			if (m_StageNumSelect == STAGE_NUM_MAX) {
				SetStageNumSelect(STAGE_GOBACK);
			}
			else {
				StageNumAdd();
			}
			break;
		case ARROW_KEY_LEFT:
			if (m_StageNumSelect == STAGE_NUM_NONE) {
				SetStageNumSelect(STAGE_NUM_001);
			}
			else {
				StageNumSub();
			}
			break;
		case ARROW_KEY_MAX:
			break;
		default:
			break;
	}
	
}

bool StageObjectArrowKey::IsEnterTriggerd(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) &&
		m_StageNumSelect != STAGE_NUM_NONE &&
		m_StageNumSelect != STAGE_NUM_MAX) {
		return true;
		
	}
	return false;
}

void StageObjectArrowKey::EnterUpdate(void)
{
	if (IsEnterTriggerd()) {
		
		SetStageNum(m_StageNumSelect);
		
			               
		if (GetFadeState() == FADE_NONE)
		{
			SceneTransition(SCENE_GAME);
		}
		
	}
}

STAGE_NUM StageObjectArrowKey::ReturnStageNum(void)
{
    return (STAGE_NUM)GetStageNumSelect();
}
