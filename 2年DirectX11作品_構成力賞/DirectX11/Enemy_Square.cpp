//=============================================================================
//
// 無相の形をした立方体エネミー [Enemy_Square.cpp]
// Author : Yanagisawa Yuta
// 
// 説明：ランダムに動く
//=============================================================================
#include "Enemy_Square.h"
#include "CoordinateTransformation.h"


float Enemyfrand();

void Enemy_Square::Init()
{
	LoadModel((char*)"data/MODEL/musou2.obj", &m_Model);

	for (int i = 0; i<GetEnemyNumMax(); i++) {

		m_ObjInfo[i].hp = 1 + rand() % 3;
		m_ObjInfo[i].hp_max = m_ObjInfo[i].hp;
		m_ObjInfo[i].pos = D3DXVECTOR3(Enemyfrand()*ENEMY_POS_MAX, Enemyfrand() * ENEMY_POS_MAX, Enemyfrand() * ENEMY_POS_MAX);
		m_ObjInfo[i].offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_ObjInfo[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_ObjInfo[i].vec = D3DXVECTOR3(Enemyfrand(), Enemyfrand(), Enemyfrand());

		FLOAT scale = (0.5f + (m_ObjInfo[i].hp_max / A_STAGE_NUM_MAX)) * 5.0f;
		m_ObjInfo[i].scl = D3DXVECTOR3(scale, scale, scale);
		
		m_ObjInfo[i].size = D3DXVECTOR3(ENEMY_SQUARE_X* scale, ENEMY_SQUARE_Y * scale, ENEMY_SQUARE_Z * scale);
		m_ObjInfo[i].idxShadow = 0;
		m_ObjInfo[i].use = false;
		m_ObjInfo[i].free = false;
		m_ObjInfo[i].counter = 0;
		m_ObjInfo[i].IsDeath = false;

		//	Emissionとして使用
		m_ObjInfo[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}

	for (int i = 0; i < GetNumOfEnemiesThatAppear(); i++) {
		SetEnemy();
	}

	

	m_Emission = 1.0f;
}

void Enemy_Square::Uninit()
{
	UnloadModel(&m_Model);
}

void Enemy_Square::Update()
{
	//	開始からTIME_COUNTER_MAX秒はコリジョンなし
	for (int i = 0; i < GetEnemyNumMax(); i++) {

		if (m_ObjInfo[i].use == false)continue;
		if (m_ObjInfo[i].free == false)continue;


		

		if (m_ObjInfo[i].counter >= GetTimeCounterMax()) {
			m_ObjInfo[i].counter = GetTimeCounterMax();
			m_ObjInfo[i].free = false;
		}
		else {
			m_ObjInfo[i].counter++;

			m_ObjInfo[i].col.a += 1.0f / GetTimeCounterMax();
		}

		
			
	}

	

	//	モデルのアルファいじってます
	
	for (int i = 0; i < GetEnemyNumMax(); i++)
	{
		if (m_ObjInfo[i].use == false)continue;

		if (i == 26) {
			int a = 0;
		}

		if (m_ObjInfo[i].free) {
			m_ObjInfo[i].col.b = m_Emission;
		}
		else {
			m_ObjInfo[i].col.r = m_Emission;
		}
	}

	//Death();
}

void Enemy_Square::Draw()
{
	for (int i = 0; i < GetEnemyNumMax(); i++) {
		if (m_ObjInfo[i].use) {	

			for (unsigned short i = 0; i < m_Model.SubsetNum; i++)
			{
				m_Model.SubsetArray[i].Material.Material.Diffuse.a = m_ObjInfo[i].col.a;
				m_Model.SubsetArray[i].Material.Material.Emission = 
					D3DXCOLOR(m_ObjInfo[i].col.r, m_ObjInfo[i].col.g, m_ObjInfo[i].col.b, 0.0f);
			}

			CoordinateTransformation(&m_ObjInfo[i]);

			DrawModel(&m_Model);
		}
	}


}

void Enemy_Square::Action()
{
	for (int i = 0; i < GetEnemyNumMax(); i++) {
		if (m_ObjInfo[i].use) {
			m_ObjInfo[i].pos += m_ObjInfo[i].vec;
		}
	}
}

bool Enemy_Square::Death()
{

	return false;
}

void Enemy_Square::SetEnemy()
{
	for (int i = 0; i < GetEnemyNumMax(); i++) {
		if (m_ObjInfo[i].use)continue;
		m_ObjInfo[i].use = true;
		m_ObjInfo[i].free = true;
		m_ObjInfo[i].IsDeath = false;
		m_ObjInfo[i].counter = 0;
		m_ObjInfo[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		m_ObjInfo[i].hp = m_ObjInfo[i].hp_max;
		break;
	}
}

void Enemy_Square::SetEnemy(D3DXVECTOR3 pos)
{
	for (int i = 0; i < GetEnemyNumMax(); i++) {
		if (m_ObjInfo[i].use)continue;
		m_ObjInfo[i].use = true;
		m_ObjInfo[i].free = true;
		m_ObjInfo[i].IsDeath = false;
		m_ObjInfo[i].counter = 0;
		m_ObjInfo[i].pos = pos;
		m_ObjInfo[i].hp = m_ObjInfo[i].hp_max;
		break;
	}
}

void Enemy_Square::SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int i = 0; i < GetEnemyNumMax(); i++) {
		if (m_ObjInfo[i].use)continue;
		m_ObjInfo[i].use = true;
		m_ObjInfo[i].free = true;
		m_ObjInfo[i].IsDeath = false;
		m_ObjInfo[i].counter = 0;
		m_ObjInfo[i].pos = pos;
		m_ObjInfo[i].size = size;
		m_ObjInfo[i].hp = m_ObjInfo[i].hp_max;
		break;
	}
}

void Enemy_Square::SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 vec)
{
	for (int i = 0; i < GetEnemyNumMax(); i++) {
		if (m_ObjInfo[i].use)continue;
		m_ObjInfo[i].use = true;
		m_ObjInfo[i].free = true;
		m_ObjInfo[i].IsDeath = false;
		m_ObjInfo[i].counter = 0;
		m_ObjInfo[i].pos = pos;
		m_ObjInfo[i].size = size;
		m_ObjInfo[i].vec = vec;
		m_ObjInfo[i].hp = m_ObjInfo[i].hp_max;
		break;
	}
}



float Enemyfrand() {
	int index = rand() % 2;
	switch (index)
	{
	case 0:
		return frand();
		break;
	case 1:
		return -1 * frand();
		break;
	default:
		break;
	}
}