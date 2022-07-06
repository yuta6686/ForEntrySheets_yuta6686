#pragma once
#include "GameObject.h"

class GO_Bungee :
    public GameObject
{
public:
    // GameObject を介して継承されました
    virtual void Initialize(void) override;

    virtual void Finalize(void) override;

    virtual void Update(void) override;

    virtual void Draw(void) override;

    virtual int GetGameScene(void) override { return GAME_SCENE; }
    
    FLOAT GetPosY(void) { return Player_Vertex.pos.y; }

private:
    //ジャンプ用変数
    float m_Gravity;                        //重力
    float m_Jump = -15.0f;                  //ジャンプ
    const float GRAVITY_ACCELERATION = 0.3f;      //重力加速度
    const float DEFAULT_GRAVITY = 1.0f;     //重力を元に戻す用


    //テクスチャ用変数
    int Player_Texture;
    char TEX_NAME[128] = "data/TEXTURE/fall1.png";

    //ゲームシーン用変数
    const int GAME_SCENE = GAMESCENE_BUNGEE_JUMP;


    //頂点データ
    VERTEX_NOMAL Player_Vertex;
};

