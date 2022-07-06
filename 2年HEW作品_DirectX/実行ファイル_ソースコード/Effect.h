#pragma once
#include "GameObject.h"
class Effect :public GameObject
{
private:
	static const int VERTEX_NUM_MAX = 50;
public:
	virtual void Initialize(void) =0;

	virtual void Finalize(void) =0;

	virtual void Update(void) =0;

	virtual void Draw(void) =0;

	virtual int GetGameScene(void) {
		return GAMESCENE_GAME_TEST;
	}

	//	マウスに追尾するセッター
	virtual void SetEffect(void) {
		m_Vertex.use = true;
		IsMousePlace = true;
	}
	virtual void SetEffect(D3DXVECTOR2 pos) {
		m_Vertex.use = true;
		IsMousePlace = true;
		m_Vertex.pos = pos;
	}
	virtual void SetEffect(D3DXVECTOR2 pos, float size) {
		m_Vertex.use = true;
		IsMousePlace = true;
		m_Vertex.pos = pos;
		m_Vertex.size.x = m_Vertex.size.y = size;
	}

	//	マウスに追尾しないセッター
	virtual void SetEffectNoMouse(void) {
		m_Vertex.alpha = 2.0f;
		m_Vertex.use = true;
		IsMousePlace = false;
	}
	virtual void SetEffectNoMouse(D3DXVECTOR2 pos) {
		m_Vertex.alpha = 2.0f;
		m_Vertex.use = true;
		IsMousePlace = false;
		m_Vertex.pos = pos;
	}
	virtual void SetEffectNoMouse(D3DXVECTOR2 pos, float size) {
		m_Vertex.alpha = 2.0f;
		m_Vertex.use = true;
		IsMousePlace = false;
		m_Vertex.pos = pos;
		m_Vertex.size.x = m_Vertex.size.y = size;
	}

	bool GetUse() { return m_Vertex.use; }

	int GetVERTEXNUMMAX(void) {
		return VERTEX_NUM_MAX;
	}

private:

protected:
	VERTEX_ALL_EFFECT m_Vertex;
	VERTEX_ALL_EFFECT m_Vertexes[VERTEX_NUM_MAX];

	int m_TexIndex;
	//char m_TexName[64];

	static const int m_Xnum = 5;
	static const int m_Ynum = 6;

	const float m_Width = (1.0f / m_Xnum);
	const float m_Height = (1.0f / m_Ynum);

	//	マウスにエフェクトを追尾させるか？
	bool IsMousePlace;
};

