//=============================================================================
//
// UIの新しいやつ [UserInterface_new.h]
// Author : Yanagisawa Yuta
//
// 説明：テクスチャ出力Ver
//=============================================================================
#pragma once
#include "GameObject.h"
class UserInterface_new :
    public GameObject
{
private:
    const float UI_SIZE = 50.0f;
public:
    UserInterface_new(int texindex, FLOAT x, FLOAT y) 
        :m_TexIndex(texindex),m_x(x),m_y(y),m_width(UI_SIZE),m_height(UI_SIZE) {}

    UserInterface_new(int texindex, FLOAT x, FLOAT y,FLOAT width,FLOAT height)
        :m_TexIndex(texindex), m_x(x), m_y(y), m_width(width), m_height(height) {}

    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void SetPos(FLOAT x, FLOAT y);

    virtual void SetSize(FLOAT x, FLOAT y);

private:

    int m_TexIndex;

    FLOAT m_x, m_y;

    FLOAT m_width, m_height;
};

