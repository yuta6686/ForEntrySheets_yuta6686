#pragma once
#include "GameObject.h"
#include "GO_SS_Timer.h"
#include "GO_SS_Negi.h"
#include "GO_SS_Karashi.h"

class GO_SS_BackGround;
class GO_SS_Player;
class GO_SS_Goal;
class GO_SS_Wall;
class GO_SS_ShotString;
class GO_SS_Target;
class GO_SS_ZipLine;
class GO_SS_Fan;
class GO_SS_KitchenTimer;


class GO_SS_Collision
{
public:
    //?Z?b?^?[
    void SetBackGround(GO_SS_BackGround* p_BackGround) { m_pBackGround = p_BackGround; }
    void SetPlayer(GO_SS_Player* p_Player) { m_pPlayer = p_Player; }
    void SetGoal(GO_SS_Goal* p_Goal) { m_pGoal = p_Goal; }
    void SetWall(GO_SS_Wall* pWall) { m_pWall = pWall; }
    void SetShotString(GO_SS_ShotString* p) { m_pShotString = p; }
    void SetTarget(GO_SS_Target* pTarget) { m_pTarget = pTarget; }
    void SetZipLine(GO_SS_ZipLine* p) { m_pZipLine = p; }
    void SetFan(GO_SS_Fan* p) { m_pFan = p; }
    void SetKitchenTimer(GO_SS_KitchenTimer* p_KitchenTimer) { m_pKitchenTimer = p_KitchenTimer; }
    void SetTimer(GO_SS_Timer* pTimer) { m_pTimer = pTimer; }
    void SetNegi(GO_SS_Negi* pNegi) { m_pNegi = pNegi; }
    void SetKarashi(GO_SS_Karashi* pKarashi) { m_pKarashi = pKarashi; }

    //??????????????????
    void CollisionInit(void);
    void CollisionUpdate(void);

private:
    //?????o???
    D3DXVECTOR2 playerPos;
    D3DXVECTOR2 playerSize;

    VERTEX_T Goal_Vertex;

    //VERTEX_T KitchenTimer_Vertex;

    FAN_VARTEX* m_FanInfo;


    //?|?C???^???
    GO_SS_BackGround* m_pBackGround;
    GO_SS_Player* m_pPlayer;
    GO_SS_Goal* m_pGoal;
    GO_SS_Wall* m_pWall;
    GO_SS_ShotString* m_pShotString;
    GO_SS_Target* m_pTarget;
    GO_SS_ZipLine* m_pZipLine;
    GO_SS_Fan* m_pFan;
    GO_SS_KitchenTimer* m_pKitchenTimer;
    GO_SS_Timer* m_pTimer;
    GO_SS_Negi* m_pNegi;
    GO_SS_Karashi* m_pKarashi;
 
//????????         CollisionJudge_ -> CJ_
    int collTemp;
    bool jumpOnce;
    bool upCollOnce;

//?v???C???[???
    int CJ_PlayerWall(void);
    bool CJ_PlayerUpper(void);
    int CJ_PWSide(void);
    void CJ_PlayerFan(void);
     

//????????e???v???[?g
    bool BBCollision(D3DXVECTOR2 pos1,D3DXVECTOR2 size1, D3DXVECTOR2 pos2, D3DXVECTOR2 size2);

//3????~????????????LeftTop                                              ??                ??
    bool BBCollision_LeftTop2(D3DXVECTOR2 pos1, D3DXVECTOR2 size1, D3DXVECTOR2 pos2, D3DXVECTOR2 size2);

    void DebugOut(void);
    void CJ_GoalPlayer(void);
    void PlayerYCorrection(int index);
    void CJ_KitchenTimerPlayer(void);
    void CJ_NegiAndPlayer(void);
    void CJ_KarashiAndPlayer(void);
};

