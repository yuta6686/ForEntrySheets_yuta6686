//=============================================================================
//
// 射程上昇スキル [Skill_Range.cpp]
// Author : Yanagisawa Yuta
//
// 説明：射程をリングで表示
//=============================================================================
#include "Skill_Range.h"
#include "CoordinateTransformation.h"

void Skill_Range::Init()
{
	LoadModel(m_pModelName, &m_Model);
	m_TexIndex = LoadTexture(m_TexName);
	
	m_range = RANGE_DEFAULT;

	

	m_Obj.pos = { 0.0f,0.0f,0.0f };
	m_Obj.size = { m_range,m_range,m_range };

	float scale = m_range/10.0f;
	m_Obj.scl = { scale,scale,scale };
	m_Obj.col = { 1.0f,1.0f,1.0f,0.0f };

	
}

void Skill_Range::Uninit()
{
	UnloadModel(&m_Model);
}

void Skill_Range::Update()
{	
	float scale = ( m_range + ( m_SelectedNum * RANGE_DEFAULT * RANGE_FACTOR))/ 10.0f;
	m_Obj.scl = { scale,scale,scale };
}

void Skill_Range::Draw()
{
	//SetBlendState(BLEND_MODE_ADD);

	//SetAlphaTestEnable(true);

		// ライティングを有効
	//SetLightEnable(false);

	SetCullingMode(CULL_MODE_BACK);

	//for (unsigned short i = 0; i < m_Model.SubsetNum; i++)
	//{
	//	m_Model.SubsetArray[i].Material.Material.Diffuse.a = 0.0f;
	//	//m_Model.SubsetArray[i].Material.Material.Emission = { 1.0f,1.0f,1.0f,0.0f };
	//}

	//	座標変換
	CoordinateTransformation(&m_Obj);

	DrawModel(&m_Model);


	SetBlendState(BLEND_MODE_ALPHABLEND);
}



