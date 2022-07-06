//=============================================================================
//
// ステージクリア時のエフェクト [Eff_Clear.cpp]
// Author : Yanagisawa Yuta
//
// 説明：クリアしたんだな。って感じのエフェクトです
//		経験値完全取得後、発動。
//		スキル選択後、発動
//=============================================================================
#include "Eff_Clear.h"
#include "sprite.h"

void Eff_Clear::Init()
{
	m_TexIndex = LoadTexture(m_TexName);
	m_TexIndex2 = LoadTexture(m_TexName2);

	m_NowTex = m_TexIndex;

	m_Obj.pos = { SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f };
	m_Obj.size = { SCREEN_WIDTH,SCREEN_WIDTH,0.0f };
	m_Obj.use = false;
	m_Obj.counter = 0;

	m_u = 0.0f;
	m_v = 0.0f;
}

void Eff_Clear::Uninit()
{
}

void Eff_Clear::Update()
{
	if (m_Obj.use) {
		if (m_delay >= 1) {
			m_delay = 0;
		}
		else {
			m_delay++;

			if (m_Obj.counter >= CLEAR_MAX) {
				m_Obj.counter = 0;
				m_Obj.use = false;
			}
			else {
				m_Obj.counter++;

				if (m_Obj.counter == 1) {
					//  この間にエフェクトいれたり、BGM変えたりする
					GetSEManager()->PlaySE(SE_MAJIKARU, 0.5f);
				}
				else if (m_Obj.counter == 40) {
					GetSEManager()->PlaySE(SE_KIRAKIRA, 0.5f);
				}
			}
		}

		

		m_u = m_Obj.counter % CLEAR_X_NUM * CLEAR_WIDTH;
		m_v = m_Obj.counter / CLEAR_Y_NUM * CLEAR_HEIGHT;
	}
}

void Eff_Clear::Draw()
{
	SetBlendState(BLEND_MODE_ADD);

	if (m_Obj.use) {
		DrawSprite(m_NowTex,
			m_Obj.pos.x, m_Obj.pos.y,
			m_Obj.size.x, m_Obj.size.y,
			m_u, m_v, CLEAR_WIDTH, CLEAR_HEIGHT);
	}

	SetBlendState(BLEND_MODE_ALPHABLEND);
}

void Eff_Clear::SetEffect()
{
	if (!m_Obj.use) {
		m_Obj.counter = 0;		
		m_Obj.use = true;
		m_NowTex = m_TexIndex;
	}
}

void Eff_Clear::SetEffect(D3DXVECTOR3 pos)
{
}

void Eff_Clear::SetEffect(bool IsStart)
{
	if (!m_Obj.use ) {
		m_Obj.counter = 0;		
		m_Obj.use = true;

		if (IsStart) {
			m_NowTex = m_TexIndex2;
		}
		else {
			m_NowTex = m_TexIndex;
		}
	}
}
