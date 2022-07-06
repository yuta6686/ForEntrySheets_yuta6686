#include "NattoRotateObject.h"

void NattoRotateObject::Initialize(void)
{

    for (int i = 0; i < NATTO_MAX; i++) {
        //  D3DXVECTOR2
        m_Vertex[i].pos = D3DXVECTOR2(SCREEN_WIDTH / 4 * frand(), 100.0f * frand());
        m_Vertex[i].dpos = m_Vertex[i].pos;
        m_Vertex[i].size = D3DXVECTOR2(50.0, 40.0f * frand_r() + 20.0f);

        //  FLOAT
        m_Vertex[i].angle = 0.1f;
        m_Vertex[i].rot = frand_r();       
        m_Vertex[i].alpha = 1.0f;
        m_Vertex[i].radius = frand() * 100.0f + 50.0f;

        //  bool
        m_Vertex[i].use = false;

        //  初期Rot保存用
        m_Rots[i] = m_Vertex[i].rot;

        //  初期Radius保存用
        m_Radius[i] = m_Vertex[i].radius;
    }

    //  初期状態の納豆保有数
    for (int i = 0; i < FIRST_NATTO; i++) 
    {
        SetNatto();
    }
}

void NattoRotateObject::Finalize(void)
{
}

void NattoRotateObject::Update(void)
{
    for (int i = 0; i < NATTO_MAX; i++) {
        if (!m_Vertex[i].use)continue;

        //   納豆回転（描画時回転）
        m_Vertex[i].angle += m_Vertex[i].rot;

        //  回転処理
        Rotation(i);

    }

    
}

void NattoRotateObject::Draw(void)
{
    for (int i = 0; i < NATTO_MAX; i++) {
        if (!m_Vertex[i].use)continue;
        DrawSpriteColorRotate(m_TexIndex, m_Vertex[i].pos.x, m_Vertex[i].pos.y,
            m_Vertex[i].size.x, m_Vertex[i].size.y, 1.0f, 1.0f, 1.0f, 1.0f,
            D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Vertex[i].alpha),
            m_Vertex[i].angle);
    }
}

void NattoRotateObject::SetNatto(void)
{
    for (int i = 0; i < NATTO_MAX; i++) {
        if (m_Vertex[i].use)continue;
        m_Vertex[i].use = true;
        break;
    }
}

void NattoRotateObject::Rotation(int index)
{
    float hw, hh;
    hw = m_PlayerPos.x - m_Vertex[index].pos.x;
    hh = m_PlayerPos.y - m_Vertex[index].pos.y;

    // 中心点（プレイヤー）から納豆の座標に対する角度
    float BaseAngle = atan2f(hh, hw);

    //  プレイヤー中心に回転
    float x = m_PlayerPos.x - cosf(BaseAngle + m_Vertex[index].rot) * m_Vertex[index].radius;
    float y = m_PlayerPos.y - sinf(BaseAngle + m_Vertex[index].rot) * m_Vertex[index].radius;

    //  ポジションセット
    m_Vertex[index].pos = D3DXVECTOR2(x, y);
}

FLOAT NattoRotateObject::frand()
{
    return (FLOAT)rand() / (FLOAT)RAND_MAX;
}

FLOAT NattoRotateObject::frand_r()
{
    return ANGLE_MIN + (FLOAT)(rand()) / (FLOAT)(RAND_MAX / (ANGLE_MAX - ANGLE_MIN));
}
