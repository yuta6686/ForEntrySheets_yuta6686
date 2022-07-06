//=============================================================================
//
// プレイヤー様 [GO_Player.h]
// Author : Yanagisawa Yuta
//
//=============================================================================
#pragma once
#include "GameObject.h"
#include "shadow.h"
#include "ItemManager.h"
#include "ItemFactory.h"
#include "UserInterface.h"
#include "SkillManager.h"
#include "SkillFactory.h"


#define	VALUE_MOVE		(5.0f)						// 移動量
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// 回転量

class GO_Player :
    public GameObject
{
public:
    // GameObject を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    GAME_OBJECT GetObjInfo() { return m_Obj; }

    ItemManager* GetItemManager() { return &m_ItemManager; }
    SkillManager* GetSkillManager() { return m_SkillManeger; }

    ExperiencePoint* GetEXP() { return m_UI.GetEXP(); }

    void SetObjVec(D3DXVECTOR3 vec) { m_Obj.vec = vec; }

    void SetUse(bool flag) { m_Obj.use = flag; }

    void AddPos(D3DXVECTOR3 vec) { m_Obj.pos += vec; }

    //  ゲームクリアになったら
    bool IsClear() { return GetEXP()->GetIsClear(); }
private:
    //  モデル
    DX11_MODEL m_Model;
    DX11_MODEL m_ChildModel;

    //  オブジェクト情報
    GAME_OBJECT m_Obj;
    GAME_OBJECT m_ChildObj;

    //  ライト
    LIGHT* pLight;

    //  カメラ
    CAMERA* cam;

    //  アイテム
    ItemManager m_ItemManager;
    ItemFactory m_ItemFactory;

    //  スキル
    SkillManager* m_SkillManeger;
    SkillFactory m_SkillFactory;
    
    // UI
    UserInterface m_UI;

    float       m_Rot;		// キャラクターの向き
    float		m_Rot_x;
    float		m_PrePlayerPosY;



//  メンバ関数
    void CameraUpdate();
    void PlayerUpdate();
    void PlayerInputUpdate();
    void LightUpdate();


};

