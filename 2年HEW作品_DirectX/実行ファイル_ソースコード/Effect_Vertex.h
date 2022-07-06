#pragma once
#include "Effect.h"
class Effect_Vertex :
    public Effect
{
private:
    int NUM_VERTEX = 3;
public:
    // Effect ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void Initialize(void) override;

    virtual void Finalize(void) override;

    virtual void Update(void) override=0;

    virtual void Draw(void) override=0;

    virtual void SetEffect()override;
    virtual void SetEffect(int num);

protected:
    ID3D11Buffer* m_VertexBuffer = nullptr;	// ’¸“_î•ñ

    VERTEX_3D* m_pVertex = nullptr;
};

