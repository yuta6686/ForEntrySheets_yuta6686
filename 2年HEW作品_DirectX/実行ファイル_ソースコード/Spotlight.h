#pragma once
#include "main.h"
class Spotlight
{
public:
	void Init();
	void Draw();

	void SetIlluminate(bool flag ,D3DXVECTOR2 pos ,D3DXVECTOR2 size) { 
		m_Illuminate = flag; 
		m_pos = pos;
		m_size = size;
	}
private:
	int m_TexIndex;
	char m_TexName[64] = "data/TEXTURE/èWíÜê¸3.png";

	bool m_Illuminate;
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 m_size;
};

