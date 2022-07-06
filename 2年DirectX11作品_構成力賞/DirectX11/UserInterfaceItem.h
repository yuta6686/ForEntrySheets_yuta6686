//=============================================================================
//
// UIのインタフェース [UserInterface.h]
// Author : Yanagisawa Yuta
//
//=============================================================================
#pragma once
#include "GameObject.h"
#include "sprite.h"

class UserInterfaceItem :
    public GameObject
{
public:
    // GameObject を介して継承されました
    virtual void Init() override=0;

    virtual void Uninit() override=0;

    virtual void Update() override=0;

    virtual void Draw() override=0;

    void SetPos(D3DXVECTOR3 pos) { m_Obj.pos = pos; }
protected:
    GAME_OBJECT m_Obj;
    DX11_MODEL  m_Model;

    MATERIAL m_Material;

    int m_texIndex;

    ID3D11Buffer* m_VertexBuffer = NULL;
};

