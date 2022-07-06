//=============================================================================
//
// バレット [Item_Bullet.cpp]
// Author : Yanagisawa Yuta
//
// バレットをアイテムとして管理していたが、他のアイテムを作成せずに終わってしまった。
// 
//=============================================================================
#include "Item_Bullet.h"
#include "CoordinateTransformation.h"


void Item_Bullet::Init()
{
    LoadModel((char*)"data/MODEL/bullet.obj", &m_Model);

	for(int i=0;i<GetItemNumMax();i++){
		m_Obj[i].pos = D3DXVECTOR3(0.0f, 35.0f, 0.0f);
		m_Obj[i].offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Obj[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Obj[i].vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		float scale = 2.5f;
		m_Obj[i].scl = D3DXVECTOR3(scale, scale, scale);
		m_Obj[i].size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
		m_Obj[i].idxShadow = 0;
		m_Obj[i].use = false;

		m_Obj[i].counter = 0;
	}

	m_CoolTimeMax = COOL_TIME_MAX_DEFAULT;
	m_CoolTimeCounter = 0;
	m_IsCoolTime = false;

	for (unsigned short i = 0; i < m_Model.SubsetNum; i++)
	{
		m_Model.SubsetArray[i].Material.Material.Emission = D3DXCOLOR(0.0f,1.0f, 1.0f, 1.0f);
	}
}

void Item_Bullet::Uninit()
{
    UnloadModel(&m_Model);
}

void Item_Bullet::Update()
{
	for (int i = 0; i < GetItemNumMax(); i++) {
		if (!m_Obj[i].use)continue;
		m_Obj[i].pos += m_Obj[i].vec;
	}

	CoolTimeManager();
}

void Item_Bullet::Draw()
{
	for (int i = 0; i < GetItemNumMax(); i++) {
		if (!m_Obj[i].use)continue;

		CoordinateTransformation(&m_Obj[i]);

		DrawModel(&m_Model);
	}
}

int Item_Bullet::ReturnIndex(void)
{
    return ITEM_BULLET;
}

void Item_Bullet::SetItem()
{
	for (int i = 0; i < GetItemNumMax(); i++) {
		if (m_Obj[i].use)continue;
		m_Obj[i].use = true;
		m_Obj[i].counter = 0;
		m_IsCoolTime = true;
		break;
	}
}

void Item_Bullet::SetItem(D3DXVECTOR3 vec)
{
	for (int i = 0; i < GetItemNumMax(); i++) {
		if (m_Obj[i].use)continue;

		m_Obj[i].use = true;
		m_Obj[i].vec = vec;
		m_Obj[i].counter = 0;
		m_IsCoolTime = true;
		break;
	}
}

void Item_Bullet::SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 vec)
{
	for (int i = 0; i < GetItemNumMax(); i++) {
		if (m_Obj[i].use)continue;

		m_Obj[i].use = true;
		m_Obj[i].vec = vec;
		m_Obj[i].pos = pos;
		m_Obj[i].counter = 0;
		m_IsCoolTime = true;
		break;
	}
}

bool Item_Bullet::EndOfCoolTime()
{
	if (m_CoolTimeCounter >= m_CoolTimeMax)
		return true;

	return false;
}

void Item_Bullet::CoolTimeManager()
{
	if (m_IsCoolTime == false)return;

	if (EndOfCoolTime())
	{
		m_CoolTimeCounter = 0;
		m_IsCoolTime = false;
	}
	else {
		m_CoolTimeCounter++;
	}
}





