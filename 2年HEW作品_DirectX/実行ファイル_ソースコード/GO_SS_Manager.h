#pragma once
#include "GameObject.h"
#include "GO_SS_Negi.h"
#include "GO_SS_Karashi.h"

class GO_ShootString;
class GO_SS_Player;
class GO_SS_Wall;
class GO_SS_BackGround;
class GO_SS_Movement;
class GO_SS_Target;
class GO_SS_ShotString;
class GO_SS_FileLoad;
class GO_SS_Map;
class GO_SS_Scramble;
class GO_SS_Timer;
class GO_SS_Goal;
class GO_SS_TimeDelay;
class GO_SS_Fan;
class GO_SS_KitchenTimer;

class GO_SS_Effect_Wind;

class GO_SS_Manager :
    public GameObject
{
public:
    GO_SS_Manager();
    ~GO_SS_Manager();

    // GameObject を介して継承されました
    virtual void Initialize(void) override;

    virtual void Finalize(void) override;

    virtual void Update(void) override;

    

    virtual void Draw(void) override;

    virtual int GetGameScene(void) override { return GAME_SCENE; }

    void Register(GameObject* pSSObject);

private:
    //ゲームシーン
    const int GAME_SCENE = GAMESCENE_GAME_TEST;

    static const int SS_GAMEOBJECT_MAX = 50;

    GameObject* m_ssGameObject[SS_GAMEOBJECT_MAX];
    GO_SS_Player* mp_ssPlayer;
    GO_SS_Wall* mp_ssWall;
    GO_SS_BackGround* mp_ssBackGround;
    GO_SS_Movement* mp_ssMovement;
    GO_SS_Target* mp_ssTarget;
    GO_SS_ShotString* mp_ssShotString;
    GO_SS_FileLoad* mp_ssFileLoad;
    GO_SS_Map* mp_ssMap;
    GO_SS_Effect_Wind* mp_ssEffWind;
    GO_SS_Scramble* mp_ssScramble;
    GO_SS_Timer* mp_ssTimer;
    GO_SS_Goal* mp_ssGoal;
    GO_SS_TimeDelay* mp_ssTimeDelay;
    GO_SS_Fan* mp_ssFan;
    GO_SS_KitchenTimer* mp_ssKitchenTimer;
    GO_SS_Negi* mp_ssNegi;
    GO_SS_Karashi* mp_ssKarashi;

    //nullptr代入ー＞newで動的生成ー＞Register登録をまとめてやる場所。
    //コンストラクタで使用
    void Create();

    //他のゲームフレームワークに干渉したい場合使用
    void SetGameObject();

    void LastUpdate(void);
};

