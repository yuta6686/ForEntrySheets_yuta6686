#pragma once
#include "GameObject.h"
class NattoRotateObject :
    public GameObject
{
protected:
    static const int NATTO_MAX = 50;
    static const int FIRST_NATTO = 10;

    const FLOAT ANGLE_MIN = 0.0f;
    const FLOAT ANGLE_MAX = 0.1f;

public:    
    NattoRotateObject(char* texName){
        m_TexIndex = LoadTexture(texName);
    }

    virtual void Initialize(void) override;

    virtual void Finalize(void) override;

    virtual void Update(void) override;

    virtual void Draw(void) override;

    virtual int GetGameScene(void) override { return GAMESCENE_GAME_TEST; }

    virtual int GetTexIndex(void) { return m_TexIndex; }

    //  セッター  //
    // 
    //  引数無し
    void SetNatto(void);
    
    //  引数有り
    // 
    //  D3DXVECTOR2
    void SetPos(D3DXVECTOR2 pos) { m_PlayerPos = pos; }

    // int    &   float
    void SetRots(int index, float rot) { m_Vertex[index].rot = rot; }
    void SetRadius(int index, float radius) { m_Vertex[index].radius = radius; }

    //  ゲッター   //
    //  int

    //  float
    FLOAT GetRots(int index) { return m_Vertex[index].rot; }
    FLOAT GetFirstRots(int index) { return m_Rots[index]; }

    FLOAT GetRadius(int index) { return m_Vertex[index].radius; }
    FLOAT GetFirstRadius(int index) { return m_Radius[index]; }
    
protected:
    //  メンバ変数
    int m_TexIndex;

    //  頂点情報
    VERTEX_NATTO m_Vertex[NATTO_MAX];

    //  前のフレームのポジション
    D3DXVECTOR2 m_PlayerPos = D3DXVECTOR2(0.0f, 0.0f);

    //  初期Rot保存用
    FLOAT m_Rots[NATTO_MAX];

    //  初期Radius
    FLOAT m_Radius[NATTO_MAX];

//  メンバ関数
    void Rotation(int index);

    FLOAT frand();
    FLOAT frand_r();
};

