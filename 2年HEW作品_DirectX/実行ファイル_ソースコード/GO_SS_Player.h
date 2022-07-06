#pragma once
#include "GO_SS_TimeDelay.h"

#define PLAYER_X_NUM 5
#define PLAYER_Y_NUM 4

#define PLAYER_WIDTH  (1.0f / PLAYER_X_NUM)
#define PLAYER_HEIGHT (1.0f / PLAYER_Y_NUM)

enum PLAYER_STATE {
    
    PS_NONE,
    PS_RIGHT,
    PS_LEFT,
};

class GO_SS_Player :
    public GO_SS_TimeDelay
{
private:
    const FLOAT m_Jump = -12.5f;

    const FLOAT GRAVITY_ACCELERATION = 0.3f;

    const FLOAT DEFAULT_GRAVITY = 1.0f;

    const FLOAT JUMP_DELAY = 12.0f;

    const FLOAT SPEED_UP = 1.5f;
    const FLOAT SPEED_DEFAULT = 1.0f;

    static const int SPEED_UP_TIME = 60 * 10;
public:
    virtual void Initialize(void) override;

    virtual void Finalize(void) override;

    virtual void Update(void) override;

    virtual void Draw(void) override;

    virtual int GetGameScene(void) override { return GAME_SCENE; }

    //?????o???

    D3DXVECTOR2 GetPos() { return Player_Vertex.pos; }
    D3DXVECTOR2 GetSize() { return  Player_Vertex.size; }
    
    void SetPosY(FLOAT y) { Player_Vertex.pos.y = y; }
    void SetPosX(FLOAT x) { Player_Vertex.pos.x = x; }

    void SetGravityDefault(void) { m_Gravity = DEFAULT_GRAVITY; }
    void SetGravity(FLOAT f) { m_Gravity = f; }


    void AddXPos(FLOAT x) { Player_Vertex.pos.x += x; }
    void AddYPos(FLOAT y) { Player_Vertex.pos.y += y; }

    void SetSpeedUp(bool flag) { 
        if (m_KarashiSpeedUp == flag) {
            m_SpeedUpCounter = 0;
        }
        m_KarashiSpeedUp = flag; 
    }
    FLOAT GetSpeedUp(void) { return m_SpeedUP; }

    bool IsJump;
    bool OkJump;
    bool IsColl;
    bool IsCollUp;
    bool UpCollOnce;

    //not:-1 left:1 right:2 
    int IsCollSide;
    

    FLOAT m_TimeDelay = 1.0f;

private:

    //GameScene
    const int GAME_SCENE = GAMESCENE_GAME_TEST;

    //Texture
    int m_nowTexIndex;

    int Player_TexIndex;
    char TEX_NAME[64] = "data/TEXTURE/fall1.png";
    
    int m_RunTexIndex;
    char RUN_NAME[64] = "data/TEXTURE/run.png";

    int m_RunMirrorTexIndex;
    char RUN_MIRROR_NAME[64] = "data/TEXTURE/run2.png";

    //Action
    FLOAT m_Gravity;
    int m_delay = 0;

    bool m_KarashiSpeedUp;
    FLOAT m_SpeedUP;
    int m_SpeedUpCounter;

    void KrashiSpeedUp(void);

    void PlayerState(void);
    int m_State = PS_NONE;
    bool m_IsKeyPress = false;

    //Vertex Parameter
    VERTEX_PLAYER Player_Vertex;

//ÉÅÉìÉoä÷êî

    //?v???C???[???????????????Gameover??
    void SceneToGameOver(void);

    //?L?[?{?[?h?E?}?E?X??????????????v???C???[??????????????
    void InputPlayerMove(void);

    //?v???C???[??d?????
    void PlayerGravity(void);

    void PlayerJumpMove(void);
    
    void DebugOut(void);
};

