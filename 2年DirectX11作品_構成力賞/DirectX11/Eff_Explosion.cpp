//=============================================================================
//
// 爆発エフェクト [Eff_Explosion.cpp]
// Author : Yanagisawa Yuta
//
// 説明：縦横の円形斬撃が拡大されていく
//=============================================================================
#include "Eff_Explosion.h"
#include "CoordinateTransformation.h"

void Eff_Explosion::Init()
{
	LoadModel(m_TexNameCircle, &m_ModelCircle);

	for (int i = 0; i < GetEffectNumMax(); i++) 
	{
		m_Objs[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Objs[i].scl = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
		m_Objs[i].counter = 0;
		m_Objs[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

void Eff_Explosion::Uninit()
{
	UnloadModel(&m_ModelCircle);
}

void Eff_Explosion::Update()
{
	for (int i = 0; i < GetEffectNumMax(); i++) {
		if (m_Objs[i].use) {
			if (m_Objs[i].counter >= EXPLOSION_TIME) 
			{
				m_Objs[i].counter = 0;
				m_Objs[i].use = false;
			}
			else {
				m_Objs[i].counter++;

				m_Objs[i].scl.x += 5.0f;
				m_Objs[i].scl.z += 5.0f;
			}
			
		}
	}
	
}

void Eff_Explosion::Draw()
{
	SetCullingMode(CULL_MODE_NONE);

	SetBlendState(BLEND_MODE_ADD);

	// ライティングを有効
	SetLightEnable(false);

	for (int i = 0; i < GetEffectNumMax(); i++)
	{	
		if (m_Objs[i].use == false)continue;
		CoordinateTransformation(&m_Objs[i]);

		DrawModel(&m_ModelCircle);
	}

	SetLightEnable(true);

	SetBlendState(BLEND_MODE_ALPHABLEND);

	SetCullingMode(CULL_MODE_BACK);
}

void Eff_Explosion::SetEffect()
{
	
}

void Eff_Explosion::SetEffect(D3DXVECTOR3 pos)
{
}

void Eff_Explosion::SetEffect(bool IsStart)
{
}
