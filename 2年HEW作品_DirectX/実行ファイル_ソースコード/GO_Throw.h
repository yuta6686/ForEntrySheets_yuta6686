#pragma once
#include "GameObject.h"
class GO_Throw :
    public GameObject
{
    // GameObject を介して継承されました
    virtual void Initialize(void) override;
    virtual void Finalize(void) override;
    virtual void Update(void) override;
    virtual void Draw(void) override;

    virtual int GetGameScene(void) override { return GAME_SCENE; }

private:
    //Texture用のインデックス
    int Throw_Texture;

    //テクスチャの名前
    char TEX_NAME[128] = "data/TEXTURE/";

    //ゲームシーン    -> GameScene.hを参照
    const int GAME_SCENE = GAMESCENE_SCRAMBLE;

    
};

