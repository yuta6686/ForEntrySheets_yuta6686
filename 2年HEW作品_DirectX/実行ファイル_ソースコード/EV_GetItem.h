#pragma once
#include "Effect_Vertex.h"
class EV_GetItem :
    public Effect_Vertex
{
public:
    virtual void Initialize(void)override;

    virtual void Finalize(void)override;
   
    virtual void Update(void) override;

    virtual void Draw(void) override;

};

