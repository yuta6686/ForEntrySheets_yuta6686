//---------------------------------------------
//	オブジェクト間通信をここでやる	[GO_SS_Movement.h]	
//                          Author: Yanagisawa
//---------------------------------------------
// GameSceneTestのオブジェクト（GO_SS_Managerにあるポインタ）を
// ここで使って、値をいじり合う
//  
// 自分自身が他のオブジェクトの情報をしる必要がない。
//      
// こいつだけがすべてを知っている
// 
// セッターは下に移動しました
//
//---------------------------------------------
#include "GameObject.h"
#include "GO_SS_Collision.h"
#include "GO_SS_Fan.h"
#include "GO_SS_Timer.h"


#define TIME_DELAY_VALUE 0.3f

class GO_SS_BackGround;
class GO_SS_Player;
class GO_SS_Wall;
class GO_SS_ShotString;
class GO_SS_Target;
class GO_SS_Map;
class GO_SS_Effect_Wind;
class GO_SS_Goal;
class GO_SS_TimeDelay;
class GO_SS_Fan;
class GO_SS_KitchenTimer;

enum PlayerMove {
    PLAYERMOVE_NONE,
    PLAYERMOVE_LINEAR,
    PLAYERMOVE_PENDULUM,
    PLAYERMOVE_MAX,
};

class GO_SS_Movement :
    public GameObject
{
private:
    //  定数
    const FLOAT BG_SCROLL_SPEED = 0.001f;
    const FLOAT MAP_OBJ_MOVING_SPEED = 5.0f;
    const FLOAT GOAL_MOVING_SPEED = 5.0f;
    const FLOAT KTIMER_MOVING_SPEED = 5.0f;

    const int PENDULUM_COUNTER_MAX = 100;

    //変更可能変数
    FLOAT m_TimeDelay = 1.0f;
public:
    // GameObject を介して継承されました
    virtual void Initialize(void) override;
    virtual void Finalize(void) override {};
    virtual void Update(void) override;
    virtual void Draw(void) override {};
    virtual int GetGameScene(void) override { return GAME_SCENE; }

    void SetMap(GO_SS_Map* p) { m_pMap = p; }
    void SetEffWind(GO_SS_Effect_Wind* p) { m_pEffectWind = p; }
    void SetTimeDelay(GO_SS_TimeDelay* p) { m_pTimeDelay = p; }

private:
    //ゲームシーン
    const int GAME_SCENE = GAMESCENE_GAME_TEST;

    GO_SS_BackGround* m_pBackGround;
    GO_SS_Player* m_pPlayer;
    GO_SS_Wall* m_pWall;
    GO_SS_ShotString* m_pShotString;
    GO_SS_Target* m_pTarget;
    GO_SS_Map* m_pMap;
    GO_SS_Effect_Wind* m_pEffectWind;
    GO_SS_Goal* m_pGoal;
    GO_SS_TimeDelay* m_pTimeDelay;
    GO_SS_Fan* m_pFan;
    GO_SS_KitchenTimer* m_pKitchenTimer;
    GO_SS_Timer* m_pTimer;
    GO_SS_Negi* m_pNegi;
    GO_SS_Karashi* m_pKarashi;


    //メンバ変数
    int JumpCounter = 0;
    int JumpCountMax = 60;
    int Pendulum_Counter = 0;

    float m_Angle = 0.0f;

    bool IsPendulum = false;
    bool IsLiner = false;
    bool m_ChengeMove = false;

    int m_CoolTime = 0;
    int m_CoolMax = 30;

    int m_NowMove = PLAYERMOVE_NONE;
    int m_PreMove = PLAYERMOVE_NONE;
    int m_ChaMove = PLAYERMOVE_NONE;

    void CheckNowMove();

    GO_SS_Collision m_ssCollision;      //当たり判定を司る者

    //
    PlayerMoveForFan m_ForFan;

//メンバ関数

    //  リニアー
    void JumpMove_Liner();

    //  振り子
    void JumpMove_Pendulum();

    //↑JumpMove_Pendulumに含まれる処理
    //{
        void PlayerMove_Pendulum();
        void BackGroundMovement_Pendulum();
    //}
    

    //  プレイヤーの動き切り替え

    void Update_PlayerMoveSwitch();
    void PlayerMoveSwitch(PlayerMove index);


    //移動
    void MovementManager(void);
       
    //  風の移動
    //{
        void MovementManager_ForFan();
    //}

    //奈落からの期間
    void FromAbyss();

    //プレイヤー遅延処理
    void SetTimeDelay(void);

    //デバッグ用
    void DebugOut(int i);



public:
//セッター
    void SetBackGround(GO_SS_BackGround* p_BackGround) {
        m_pBackGround = p_BackGround;
        m_ssCollision.SetBackGround(p_BackGround);
    }
    void SetPlayer(GO_SS_Player* p_Player) {
        m_pPlayer = p_Player;
        m_ssCollision.SetPlayer(p_Player);
    }
    void SetGoal(GO_SS_Goal* p_Goal) {
        m_pGoal = p_Goal;
        m_ssCollision.SetGoal(p_Goal);
    }
    void SetWall(GO_SS_Wall* pWall) {
        m_pWall = pWall;
        m_ssCollision.SetWall(pWall);
    }
    void SetShotString(GO_SS_ShotString* p) {
        m_pShotString = p;
        m_ssCollision.SetShotString(p);
    }
    void SetTarget(GO_SS_Target* pTarget) {
        m_pTarget = pTarget;
        m_ssCollision.SetTarget(pTarget);
    }
    void SetFan(GO_SS_Fan* p) {
        m_pFan = p;
        m_ssCollision.SetFan(p);
    }
    void SetKitchenTimer(GO_SS_KitchenTimer* p_KitchenTimer) {
        m_pKitchenTimer = p_KitchenTimer;
        m_ssCollision.SetKitchenTimer(p_KitchenTimer);
    }
    void SetTimer(GO_SS_Timer* pTimer) {
        m_pTimer = pTimer;
        m_ssCollision.SetTimer(pTimer);
    }

    void SetNegi(GO_SS_Negi* pNegi) {
        m_pNegi = pNegi;
        m_ssCollision.SetNegi(pNegi);
    }

    void SetKarashi(GO_SS_Karashi* pKarashi) {
        m_pKarashi = pKarashi;
        m_ssCollision.SetKarashi(pKarashi);
    }
};


