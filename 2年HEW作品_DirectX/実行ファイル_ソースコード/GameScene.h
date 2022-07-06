#pragma once
//---------------------------
//	[GameScene.h]
//	Yuta Yanagisawa 
//---------------------------

//ゲーム内でのシーン遷移を管理します。


enum GAMESCENE{
    GAMESCENE_NONE,
    GAMESCENE_SCRAMBLE,         //納豆混ぜるシーン
    GAMESCENE_FALL,             //落ちるシーン
    GAMESCENE_BUNGEE_JUMP,      //バンジージャンプのシーン
    GAMESCENE_GAME_TEST,
    GAMESCENE_MAX
};

class GameScene
{
public:
    int m_GameScene = GAMESCENE_BUNGEE_JUMP;
};

