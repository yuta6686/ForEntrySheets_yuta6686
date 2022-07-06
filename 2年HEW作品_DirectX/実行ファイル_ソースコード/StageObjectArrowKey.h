#pragma once
//=============================================================================
//
// ステージ選択画面処理の矢印キー・エンターキー入力処理 [SelectStage.h]
// Author :	yuta yanagisawa 
//
//=============================================================================
#include "StageObject.h"
class StageObjectArrowKey :
    public StageObject
{
public:
//  継承メンバ関数-------------------------------------------------------
    virtual HRESULT Init(void) override { return E_NOTIMPL; }
    
    virtual void Update(void) override;
    virtual void Draw(void) override;

    virtual void Uninit(void) override {}           //  空
    virtual bool IsClick(void) override             //  空
    { return false; }
    virtual void ClickUpdate(void) override {}      //  空
    virtual bool IsMouseOver(void) override         //  空
    { return false; }
    virtual void MouseOverUpdate(void) override {}  //  空

    virtual STAGE_NUM ReturnStageNum(void) override;

//  固有メンバ関数-------------------------------------------------------
    //  選択されているステージ番号を返す
    virtual int GetStageNumSelect(void) { return m_StageNumSelect; }

private:
//  メンバ変数-----------------------------------------------------------
    //  矢印キー状態取得用
    int m_ArrowKey = ARROW_KEY_NONE;

    //  選択されているステージ取得用
    int m_StageNumSelect = STAGE_NUM_NONE;

//  メンバ関数-----------------------------------------------------------
    //  矢印キー
    virtual int IsArrowKeyTriggerd(void);
    virtual void ArrowKeyUpdate(void);

    //  エンターキー
    virtual bool IsEnterTriggerd(void);
    virtual void EnterUpdate(void);

    //  m_StageNumSelectの振る舞い
    virtual void SetStageNumSelect(int stageNum) 
    { m_StageNumSelect = stageNum; }   //最大、最小など指定

    virtual void StageNumAdd(void) 
    { m_StageNumSelect++; }             //増加

    virtual void StageNumSub(void) 
    { m_StageNumSelect--; }             //減少
};

