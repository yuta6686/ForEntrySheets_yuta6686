//=============================================================================
//
// ステージ切り替え [GO_SwitchStage.cpp]
// Author : Yanagisawa Yuta
//
// 説明：ステージを切り替えます。
// 使わなかった。
//=============================================================================
#include "GO_SwitchStage.h"

GO_SwitchStage::GO_SwitchStage()
{
	for (int i = 0; i < STAGE_MAX; i++) {
		m_pStage[i] = nullptr;
	}

	Create();
}

void GO_SwitchStage::Create()
{
	Register(m_StageFactory.Create_001());
	Register(m_StageFactory.Create_BG());
}

GO_SwitchStage::~GO_SwitchStage()
{
	for (int i = 0; i < STAGE_MAX; i++) {
		delete m_pStage[i];
	}
}

void GO_SwitchStage::Init()
{
	for (int i = 0; i < STAGE_MAX; i++) {
		if (m_pStage[i] == nullptr)continue;
		if (m_pStage[i]->ReturnIndex() == m_nowStageIndex) {
			m_pStage[i]->Init();
		}
	}
}

void GO_SwitchStage::Uninit()
{
	for (int i = 0; i < STAGE_MAX; i++) {
		if (m_pStage[i] == nullptr)continue;
		if (m_pStage[i]->ReturnIndex() == m_nowStageIndex) {
			m_pStage[i]->Uninit();
		}
	}
}

void GO_SwitchStage::Update()
{
	for (int i = 0; i < STAGE_MAX; i++) {
		if (m_pStage[i] == nullptr)continue;
		if (m_pStage[i]->ReturnIndex() == m_nowStageIndex) {
			m_pStage[i]->Update();
		}
	}
}

void GO_SwitchStage::Draw()
{
	for (int i = 0; i < STAGE_MAX; i++) {
		if (m_pStage[i] == nullptr)continue;
		if (m_pStage[i]->ReturnIndex() == m_nowStageIndex) {
			m_pStage[i]->Draw();
		}
	}
}

void GO_SwitchStage::Register(GO_Stage* pStage)
{
	for (int i = 0; i < STAGE_MAX; i++) {
		if (m_pStage[i])continue;
		m_pStage[i] = pStage;
		break;
	}
}


