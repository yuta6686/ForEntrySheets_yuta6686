//=============================================================================
//
// ステージ背景 [StageBackground.cpp]
// Author : Yanagisawa Yuta
//	説明：ステージの背景
//=============================================================================
#include "StageBackground.h"
#include "CoordinateTransformation.h"

void StageBackground::Init()
{
	LoadModel((char*)"data/MODEL/circle_001.obj", &m_Circle_001);
	LoadModel((char*)"data/MODEL/circle_002.obj", &m_Circle_002);
	LoadModel((char*)"data/MODEL/circle_003.obj", &m_Circle_003);

	LoadModel((char*)"data/MODEL/akatsuki.obj", &m_Model);
	LoadModel((char*)"data/MODEL/torii1.obj", &m_ToriiModel);

	//	暁背景
	{
		m_Obj.pos = D3DXVECTOR3(0.0f, 500.0f, 0.0f);
		m_Obj.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		float fscale = 20.0f;
		m_Obj.scl = D3DXVECTOR3(fscale, fscale, fscale);
		m_Obj.size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	}

	//	鳥居背景
	{
		m_Torii.pos = D3DXVECTOR3(0.0f, -1050.0f, 0.0f);
		m_Torii.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		float fscale = 50.0f;
		m_Torii.scl = D3DXVECTOR3(fscale, fscale, fscale);
		m_Torii.size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
		m_Torii.rot.y = D3DX_PI/2.0f;
	}

	for (int i = 0; i < CIRCLE_MAX; i++) {

		//	m_Circles1
		{
			m_Circles1[i].pos = D3DXVECTOR3(CIRCLE_LIMIT * StageFrand(), 0.0f, 0.0f);
			m_Circles1[i].offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_Circles1[i].spd = 1.0f;
			m_Circles1[i].rot = D3DXVECTOR3(StageFrand(), 0.0f, D3DX_PI / 2.0f);

			float scale = 150.0f;
			m_Circles1[i].scl = D3DXVECTOR3(scale, scale, scale);
			m_Circles1[i].size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

			m_Circles1[i].col = D3DXCOLOR(1.0f, frand(), frand(), frand());
		}

		//	m_Circles2
		{
			m_Circles2[i].pos = D3DXVECTOR3(CIRCLE_LIMIT* StageFrand(), 0.0f, 0.0f);
			m_Circles2[i].offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_Circles2[i].spd = 1.0f;
			m_Circles2[i].rot = D3DXVECTOR3(StageFrand(), 0.0f, D3DX_PI / 2.0f);

			float scale = 200.0f;
			m_Circles2[i].scl = D3DXVECTOR3(scale, scale, scale);
			m_Circles2[i].size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

			m_Circles2[i].col = D3DXCOLOR(0.0f, frand(), frand(), frand());

		}

		//	m_Circles3
		{
			m_Circles3[i].pos = D3DXVECTOR3(CIRCLE_LIMIT * StageFrand(), 0.0f, 0.0f);
			m_Circles3[i].offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_Circles3[i].spd = 1.0f;
			m_Circles3[i].rot = D3DXVECTOR3(StageFrand(), 0.0f, D3DX_PI / 2.0f);

			float scale = 200.0f;
			m_Circles3[i].scl = D3DXVECTOR3(scale, scale, scale);
			m_Circles3[i].size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

			m_Circles3[i].col = D3DXCOLOR(0.0f, frand(), frand(), frand());

		}
	}
}

void StageBackground::Uninit()
{
	UnloadModel(&m_Circle_001);
	UnloadModel(&m_Circle_002);
	UnloadModel(&m_Circle_003);

	UnloadModel(&m_Model);
	UnloadModel(&m_ToriiModel);
}

void StageBackground::Update()
{
	for (int i = 0; i < CIRCLE_MAX; i++) {
		m_Circles1[i].rot.x += 0.01f;
		m_Circles2[i].rot.x -= 0.01f;
		m_Circles3[i].rot.x += 0.02f;
	}
}

void StageBackground::Draw()
{
	SetBlendState(BLEND_MODE_ALPHABLEND);


	for (int i = 0; i < CIRCLE_MAX; i++) {
		for (unsigned short j = 0; j < m_Circle_001.SubsetNum; j++)
		{
			m_Circle_001.SubsetArray[j].Material.Material.Emission = m_Circles1[i].col;

			m_Circle_002.SubsetArray[j].Material.Material.Emission = m_Circles2[i].col;

			m_Circle_003.SubsetArray[j].Material.Material.Emission = m_Circles3[i].col;
		}

		CoordinateTransformation(&m_Circles1[i]);

		DrawModel(&m_Circle_001);

		CoordinateTransformation(&m_Circles2[i]);

		DrawModel(&m_Circle_002);

		CoordinateTransformation(&m_Circles3[i]);

		DrawModel(&m_Circle_003);
	
	}

	CoordinateTransformation(&m_Obj);
	DrawModel(&m_Model);

	CoordinateTransformation(&m_Torii);
	DrawModel(&m_ToriiModel);

	// ライティングを無効
	//SetLightEnable(false);

	SetLightEnable(false);

	// ライティングを有効
	SetLightEnable(true);

	SetCullingMode(CULL_MODE_BACK);
}

float StageBackground::StageFrand()
{
	int index = rand() % 2;

	switch (index)
	{
	case 0:
		return frand();
	case 1:
		return frand() * (-1.0f);
	}

	return frand();
}



