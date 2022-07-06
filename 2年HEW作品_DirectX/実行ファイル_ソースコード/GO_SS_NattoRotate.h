#pragma once
#include "GameObject.h"
#include "NRO_Natto.h"

enum NATTO_ROTATE_NUM {
    NRN_NONE = -1,
    NRN_NATTO,
    NRN_TIMER,
    NRN_NEGI,
    NRN_KARASHI,
    NRN_MAX,
};

class GO_SS_NattoRotate :
    public GameObject
{
public:
    GO_SS_NattoRotate();
    virtual ~GO_SS_NattoRotate();

    // GameObject ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Initialize(void) override;

    virtual void Finalize(void) override;

    virtual void Update(void) override;

    virtual void Draw(void) override;

    virtual int GetGameScene(void) override;

    void SetNatto(void);
    void SetNatto(int index);

    void SetPos(D3DXVECTOR2 pos);

    NattoRotateObject* GetNRObject(int index) { return m_pNattoRotateObjects[index]; }

    int GetNattoRotateObjectMax(void) { return NATTO_ROTATE_OBJECT_MAX; }
private:


    static const int NATTO_ROTATE_OBJECT_MAX = 10;
    NattoRotateObject* m_pNattoRotateObjects[NATTO_ROTATE_OBJECT_MAX];

};

