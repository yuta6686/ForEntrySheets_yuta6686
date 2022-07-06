#include "GO_SS_TimeDelay.h"

void GO_SS_TimeDelay::Initialize(void)
{
	m_eTimeDelay.pos = D3DXVECTOR2(-SCREEN_WIDTH/2,0.0f);
	m_eTimeDelay.size = D3DXVECTOR2(SCREEN_WIDTH*2.0f, SCREEN_HEIGHT);
	m_eTimeDelay.alpha = 0.0f;
	m_eTimeDelay.frame = 0;
	m_eTimeDelay.u = 0.0f;
	m_eTimeDelay.v = 0.0f;
	m_eTimeDelay.use = true;

	m_PointOfExtinction = 0.0f;
	
	ConcentrationLineTexture = LoadTexture(TEX_NAME);
}

void GO_SS_TimeDelay::Finalize(void)
{
}

void GO_SS_TimeDelay::Update(void)
{
	if (m_TimeDelayFlag) {
		if (m_PointOfExtinction >= D3DX_PI) {
			m_PointOfExtinction = 0.0f;
		}
		else {
			m_PointOfExtinction += 0.03f;
		}		


		m_eTimeDelay.alpha = fabsf(sinf(m_PointOfExtinction));
	}
	else {
		if (m_eTimeDelay.alpha <= 0.0f) {
			m_eTimeDelay.alpha = 0.0f;
		}
		else {
			m_eTimeDelay.alpha -= 0.04f;
		}
	}

}

void GO_SS_TimeDelay::Draw(void)
{
	SetBlendState(BLEND_MODE_SUBTRACT);

	DrawSpriteLeftTopColor(ConcentrationLineTexture,m_eTimeDelay.pos.x, m_eTimeDelay.pos.y,
		m_eTimeDelay.size.x, m_eTimeDelay.size.y, 1.0f,1.0f,1.0f,1.0f,
		D3DXCOLOR(0.7f, 1.0f, 1.0f, m_eTimeDelay.alpha));

	SetBlendState(BLEND_MODE_ALPHABLEND);
}
