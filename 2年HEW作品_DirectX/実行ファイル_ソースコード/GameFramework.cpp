//---------------------------------------------
//	[GameFramework.cpp]
// --------------------------------------------
//	Haruyakakoubou
//---------------------------------------------

//インクルード
#include "GameFramework.h"
#include "GameObject.h"
#include "GO_Player.h"
#include "GO_Scramble.h"
#include "GO_ScrambleRotation.h"
#include "GO_Throw.h"
#include "GO_Timer.h"
#include "GO_Fall.h"
#include "GO_Bungee.h"
#include "GO_SS_Manager.h"
/*---------------------------------------------
				コンストラクタ
---------------------------------------------*/
GameFramework::GameFramework()
{
	for (int i = 0; i < GAME_OBJECT_MAX; i++) {
		m_pGameObjects[i] = nullptr;
	}

	Create();
}

/*---------------------------------------------
				クリエイト
-----------------------------------------------
	ポインタ初期化、生成、レジスター
---------------------------------------------*/
void GameFramework::Create()
{
	//null
	{
		mp_player = nullptr;
		mp_vortex = nullptr;
		mp_VoRot = nullptr;

		/*ここで新しいゲームオブジェクトのポインタを初期化する*/

		mp_Throw = nullptr;
		mp_Timer = nullptr;
		mp_Fall = nullptr;
		mp_Bungee = nullptr;
		mp_ssManager = nullptr;
	}


	//new
	{
		mp_player = new GO_Player;
		mp_vortex = new GO_Scramble;
		mp_VoRot = new GO_ScrambleRotation;

		/*ゲームオブジェクト動的生成*/

		mp_Throw = new GO_Throw;
		mp_Timer = new GO_Timer;
		mp_Fall = new GO_Fall;
		mp_Bungee = new GO_Bungee;
		mp_ssManager = new GO_SS_Manager;
	}

	//Register
	{
		Register(mp_vortex);
		Register(mp_player);
		Register(mp_VoRot);

		/*GameObjectクラスを継承してれば、登録できます。*/

		Register(mp_Throw);
		Register(mp_Timer);
		Register(mp_Fall);
		Register(mp_Bungee);
		Register(mp_ssManager);
	}

}

/*---------------------------------------------
	SetGameObject()	
-----------------------------------------------
	ゲームオブジェクト内で他のオブジェクトを使用したい場合

	自身のヘッダーファイルでSet関数を作って使用する

	*この関数は初期化処理の最後に使用
---------------------------------------------*/
void GameFramework::SetGameObject()
{
	mp_VoRot->SetPlayer(mp_player);
	mp_VoRot->SetVortex(mp_vortex);
}

/*---------------------------------------------
			シーン遷移処理
---------------------------------------------*/
/*---------------------------------------------
ex)	case GAMESCENE_SCRANBLE

	mp_Timerのuse

	最初は			true
	処理が終わると	false
	シーンを変えて	true
---------------------------------------------*/
void GameFramework::TransitionScene()
{
	switch (m_GameScene)
	{
	case GAMESCENE_SCRAMBLE:
		//Timerは10秒経過したらフラグがfalseになる
		if (!mp_Timer->GetTimerUse()) {

			//もうここに入らないように、true状態にしておく
			mp_Timer->SetTimerUse(true);

			//シーンが変わればTimerのUpdateも発生しない
			m_GameScene = GAMESCENE_FALL;
		}
		break;

	case GAMESCENE_FALL:
		if (!mp_Fall->GetIsTransition()) {

			mp_Fall->SetIsTransition(true);

			m_GameScene = GAMESCENE_BUNGEE_JUMP;
		}
		break;

	case GAMESCENE_BUNGEE_JUMP:
		if (mp_Bungee->GetPosY() >= SCREEN_HEIGHT) {

			m_GameScene = GAMESCENE_GAME_TEST;
		}
		break;

	case GAMESCENE_GAME_TEST:

		break;
	default:
		break;
	}

	
}

/*---------------------------------------------
*				デストラクタ
---------------------------------------------*/
GameFramework::~GameFramework()
{
	for (int i = 0; i < GAME_OBJECT_MAX; i++) {
		// nullptrをdeleteしても大丈夫
		delete m_pGameObjects[i];
	}
}

/*---------------------------------------------
*				初期化処理
---------------------------------------------*/
void GameFramework::Initialize(void)
{

	for (int i = 0; i < GAME_OBJECT_MAX; i++) {
		if (m_pGameObjects[i]) {
			m_pGameObjects[i]->Initialize();
		}
	}

	SetGameObject();
	
}

/*---------------------------------------------
*				終了処理
---------------------------------------------*/
void GameFramework::Finalize(void)
{
	for (int i = 0; i < GAME_OBJECT_MAX; i++) {
		if (m_pGameObjects[i]) {
			m_pGameObjects[i]->Finalize();
		}
	}
}

/*---------------------------------------------
*				更新処理
---------------------------------------------*/
void GameFramework::Update(void)
{
	TransitionScene();

	//GameScene.h参照してください
	for (int i = 0; i < GAME_OBJECT_MAX; i++) {
		if (!m_pGameObjects[i])continue;
		if (m_pGameObjects[i]->GetGameScene() != m_GameScene)continue;
		
		m_pGameObjects[i]->Update();
		
	}
}
/*---------------------------------------------
*				描画処理
---------------------------------------------*/
void GameFramework::Draw(void)
{
	//GameScene.h参照してください
	for (int i = 0; i < GAME_OBJECT_MAX; i++) {
		if (!m_pGameObjects[i])continue;
		if (m_pGameObjects[i]->GetGameScene() != m_GameScene)continue;
			m_pGameObjects[i]->Draw();
		
	}
}

/*---------------------------------------------
*				登録処理
---------------------------------------------*/
void GameFramework::Register(GameObject* pGameObject)
{
	for (int i = 0; i < GAME_OBJECT_MAX; i++) {
		if (!m_pGameObjects[i]) {
			m_pGameObjects[i] = pGameObject;
			break;
		}
	}
}

