//=============================================================================
//
// プレイヤーとエネミーの衝突処理 [PlayerAndEnemyCollision.cpp]
// Author : Yanagisawa Yuta
//
// 説明:プレイヤーとエネミーだけではなく、
//      プレイヤーと経験値
//      バレットとエネミーの衝突処理
//      また、プレイヤーとバレットのベクトル処理も実行
//=============================================================================
//  順番的にスクエアが優先されてしまう。
//  PlayerAndEnemyCollision(1) ... Enemy(1)
//  先：Square  -> PlayerAndEnemyCollision
//  後：Diamond -> PlayerAndEnemyCollision
//  
//  弾を撃つとクールタイムが発生する。
//  クールタイム中は撃てないので、順番が重要になる。
//  解決方法は、Enemy全体でこの処理を行えばよい
//  設計ミスだ
//  対策案：　DeployEnemyで処理する。
//  Playerのポインタを作成することにはなるけど、仕方がない。

#include "PlayerAndEnemyCollision.h"
#include "result.h"
#include "game.h"


void PlayerAndEnemyCollision::Init()
{
    //  初手で死ななくなる処理
    for (int i = 0; i < m_pEnemy->GetEnemyNumMax(); i++) 
    {
        if (!m_pEnemy)continue;

        if (IsCollisions(i) >= 0) 
        {
            m_pEnemy->SetUseFalse(false);
        }
    }

    m_CollExplosionIndex = -1;

    m_IsColl = false;

    m_Range = 0.0f;

    //アイテム（バレット）のポインタを取得
    m_pBullet = m_pPlayer->GetItemManager()->GetItem(ITEM_BULLET);  

    //アイテム（経験値）のポインタを取得
    m_pExpPoint = m_pPlayer->GetItemManager()->GetItem(ITEM_DROP_EXP_POINT);

    m_RockOn.Init();

    m_Explosion.Init();
   
}

void PlayerAndEnemyCollision::Uninit()
{
    m_RockOn.Uninit();
    m_Explosion.Uninit();
}

void PlayerAndEnemyCollision::Update()
{
    if (!m_pEnemy)return;

    SetDiamondVec();

    for (int i = 0; i < m_pEnemy->GetEnemyNumMax(); i++) 
    {
        if (m_pPlayer->IsClear())break; //  クリアしたら当たり判定無し
        if (m_pEnemy->GetObjInfo(i).free)continue;
        if (m_pEnemy->GetObjInfo(i).use == false)continue;
        

        if (IsCollisions(i) >= 0) 
        {
            CollisionUpdate(i);
           
        }
    }

    //  射程を得られる
    m_Range = m_pPlayer->GetSkillManager()->GetSkill(SKILL_RANGE)->GetValue();

    //  クールタイムをへらす
    m_pBullet->ChangeValue(
        static_cast<int>(m_pPlayer->GetSkillManager()->GetSkill(SKILL_COOLTIME)->GetValue()));

    ItemUpdate();

    RockOnNearestEnemy();

    ToNextScene();

    m_RockOn.Update();

    m_Explosion.Update();

    //  クリア条件を満たしてからの数秒
    ClearEffect();
}

void PlayerAndEnemyCollision::Draw()
{
    m_RockOn.Draw();

    m_Explosion.Draw();
}



void PlayerAndEnemyCollision::ItemUpdate()
{
    //  バレットの処理
    ItemUpdate_Bullet();

    //  アイテムとエネミーの当たり判定
    for (int i = 0; i < m_pEnemy->GetEnemyNumMax(); i++) 
    {
        if (m_pEnemy->GetObjInfo(i).use == false)continue;

        for (int j = 0; j < m_pBullet->GetItemNumMax(); j++) 
        {
            if (m_pBullet->GetObjInfo(j).use == false)continue;
            int k = IsCollisions_Bullets(i, j);

            if (k < 0)continue;

            CollisionUpdate_Bullet(i,j);

           

            break;
        }      
    }

    
        
    //  射程内の処理と衝突したときの処理
    for (int i = 0; i < m_pExpPoint->GetItemNumMax(); i++) {
        if (m_pExpPoint->GetObjInfo(i).use == false)continue;

        //  射程内の接近処理
        if (IsApproach(i, m_Range)) {
            ml_ExpPointIndex_Approach.push_back(i);
        }


        //  接触処理
        if (IsApproach(i, 0.0f)) {
            ml_ExpPointIndex_Contact.push_back(i);
        }
    }

    //  接近
    for (auto x : ml_ExpPointIndex_Approach) 
    {
        //  プレイヤーに近づく処理
        if (m_pExpPoint->GetObjInfo(x).use == false)continue;

        //  プレイヤーに向けたベクトル
        D3DXVECTOR3 vec = VectorOfPlayer_Set(m_pExpPoint->GetObjInfo(x).pos, m_pPlayer->GetObjInfo().pos, 3.0f);

        //  経験値のベクトルをセット
        m_pExpPoint->SetVec(x,vec);
        

    }

    ml_ExpPointIndex_Approach.clear();

    //  接触
    for (auto x : ml_ExpPointIndex_Contact) 
    {
        if (m_pExpPoint->GetObjInfo(x).use == false)continue;

        //  EXPを回収する処理
        m_pExpPoint->DeleteObj(x);

        m_pPlayer->GetEXP()->AddEXP(1);
    }

    if (!ml_ExpPointIndex_Contact.empty()) {
        GetSEManager()->PlaySE(SE_POTSUN, 0.3f);
    }

    ml_ExpPointIndex_Contact.clear();
}

void PlayerAndEnemyCollision::ItemUpdate_Bullet()
{
    if (m_pPlayer->IsClear())return;

    //  自動で弾発射
    if (!m_pBullet->GetFlag())
    {
        int minIndex = NearestEnemy();

        if (minIndex < 0)return;

        //  プレイヤーとエネミーの位置を変数にいれる。
        D3DXVECTOR3 ppos = m_pPlayer->GetObjInfo().pos;
        D3DXVECTOR3 epos = m_pEnemy->GetObjInfo(minIndex).pos;

        //  プレイヤーのベクトルに設定       
        D3DXVECTOR3 toEnemyVec = VectorOfPlayer_Set(ppos, epos, ITEM_BULLET_SPEED);
        m_pPlayer->SetObjVec(toEnemyVec);

        //  弾の数を取得
        int BulletsNum = 
            static_cast<int>(m_pPlayer->GetSkillManager()->GetSkill(SKILL_NEWBULLETS)->GetValue());

        //  バレットにベクトルをセットして発射
        m_pBullet->SetItem(m_pPlayer->GetObjInfo().pos, m_pPlayer->GetObjInfo().vec);


        //  バレットのスキルを１度でも取るとここに来るよ
        //  ベクトルを乱数で調整
        for (int i = 0; i < BulletsNum - 1; i++)
        {
            D3DXVECTOR3 randvec = m_pPlayer->GetObjInfo().vec;

            randvec.x += m_pBullet->ItemRand()*BULLETS_DIFFUSION;
            randvec.y += m_pBullet->ItemRand()*BULLETS_DIFFUSION;
            randvec.z += m_pBullet->ItemRand()*BULLETS_DIFFUSION;

            //  バレットにベクトルをセットして発射
            m_pBullet->SetItem(m_pPlayer->GetObjInfo().pos, randvec);
        }
        


    }
}




int PlayerAndEnemyCollision::NearestEnemy(void)
{
    //  一番近いエネミーのインデックスを保存する
    int minIndex = -1;

    //  最短距離を保持
    float prelength = 10000000.0f;    

    //  射程内のインデックスをもらう
    std::list<int> elist = InRangeEnemyIndex();

    for (auto x : elist) {        

        D3DXVECTOR3 dist = m_pEnemy->GetObjInfo(x).pos - m_pPlayer->GetObjInfo().pos;
        float length = D3DXVec3LengthSq(&dist);

        if (length < prelength) {
            prelength = length;
            minIndex = x;
        }        
    }  

    elist.clear();

    return minIndex;
}

void PlayerAndEnemyCollision::RockOnNearestEnemy(void)
{
    int minIndex = NearestEnemy();

    if (minIndex < 0) {
        m_RockOn.SetEffectUse(false);
        return;
    }

    D3DXVECTOR3 epos = m_pEnemy->GetObjInfo(minIndex).pos;

    epos.y -= 200.0f;

    //  照準エフェクト
    m_RockOn.SetEffect(epos);
}

void PlayerAndEnemyCollision::ClearEffect(void)
{
    if (!m_pPlayer->IsClear())return;

    //  クリアしてからの時間
    if (m_ClearEffectCounter <= 150 + 30) {

        //  １体のエネミーが爆発
        //  毎フレーム１体が爆発
       EnemyExplosionOnece();               

        m_ClearEffectCounter++;

        if (m_ClearEffectCounter == 1) {         
            GetClearEffect()->SetEffect(false);
        }

        
        return;
    }    
    else {
        m_ClearEffectCounter = 0;
    }

    

    /*for (int i = 0; i < m_Explosion.GetEffectNumMax(); i++) {
        if (m_Explosion.GetObjs(i)->use)
            return;                           
    }*/



    m_pPlayer->GetEXP()->NextStage();
}



//  プレイヤーとエネミーがあたった時の処理
void PlayerAndEnemyCollision::CollisionUpdate(int index)
{
    if (m_pPlayer->IsClear()) 
    {
        m_pEnemy->SetUseFalse(index);        

        //  爆発とかのエフェクト表示してる間はreturn;
        m_CollExplosionIndex = m_Explosion.SetEffects(m_pEnemy->GetObjInfo(index).pos);
        m_Explosion.SetEffects(m_pEnemy->GetObjInfo(index).pos, D3DX_PI / 2.0f);
    }
    else {
        m_pEnemy->SetUseFalse(index);
        m_pPlayer->SetUse(false);

        //  爆発とかのエフェクト表示してる間はreturn;
        m_CollExplosionIndex = m_Explosion.SetEffects(m_pEnemy->GetObjInfo(index).pos);
        m_Explosion.SetEffects(m_pEnemy->GetObjInfo(index).pos, D3DX_PI / 2.0f);
    }    
}

//  プレイヤーのアイテムとエネミーがあたった時の処理
void PlayerAndEnemyCollision::CollisionUpdate_Bullet(int index,int index2)
{
    
    //  弾貫通するかしないかの処理はこちらで
    // 
    //  弾消す処理
    m_pBullet->DeleteObj(index2);

    //  HPの処理
    {
        int attack = (int)m_pPlayer->GetSkillManager()->GetSkill(SKILL_ATTACK)->GetValue();
        m_pEnemy->ReduceHpOfEnemy(index,attack);
    }

    //  経験値とかの処理
    if(m_pEnemy->GetIsDeathEnemy(index))
    {
        //  エネミー死亡
        m_pEnemy->SetUseFalse(index);

        //  エネミーのHPを経験値としている
        //int hp_max = m_pEnemy->GetHpMax(index);
        //m_pPlayer->GetEXP()->AddEXP(hp_max);

        //  エネミーのHPの数だけ経験値を落とす
        for (int i = 0; i < m_pEnemy->GetHpMax(index); i++) 
        {
            m_pExpPoint->SetItem(m_pEnemy->GetObjInfo(index).pos);
        }
    }    

    
    m_Explosion.SetEffects(m_pEnemy->GetObjInfo(index).pos);
    m_Explosion.SetEffects(m_pEnemy->GetObjInfo(index).pos, D3DX_PI/2.0f);

    m_RockOn.SetEffectUse(false);
}

//  プレイヤーとEXPPointの接近判定
bool PlayerAndEnemyCollision::IsApproach(int index, FLOAT range)
{
    //  プレイヤー
    D3DXVECTOR3 ppos = m_pPlayer->GetObjInfo().pos;
    D3DXVECTOR3 psize = m_pPlayer->GetObjInfo().size;

    //  ExpPoint
    D3DXVECTOR3 epos = m_pExpPoint->GetObjInfo(index).pos;
    D3DXVECTOR3 esize = m_pExpPoint->GetObjInfo(index).size;

    //  距離
    D3DXVECTOR3 dist = ppos - epos;

    
    //  Sqがついている関数は平方根の計算をしないバージョン
    FLOAT length = D3DXVec3LengthSq(&dist);

    //  サイズ
    FLOAT size = powf(psize.x + esize.x,2.0f);

    if (length < size + powf(range,2.0f))
        return true;

    return false;
}

bool PlayerAndEnemyCollision::IsApproach(FLOAT range, D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, FLOAT size1, FLOAT size2)
{
    //  距離
    D3DXVECTOR3 dist = pos1 - pos2;


    //  Sqがついている関数は平方根の計算をしないバージョン
    FLOAT length = D3DXVec3LengthSq(&dist);

    //  サイズ
    FLOAT size = powf(size1 + size2, 2.0f);

    if (length < size + powf(range, 2.0f))
        return true;

    return false;
}

//  プレイヤーの射程内いるエネミーのインデックスを調べて返す
std::list<int> PlayerAndEnemyCollision::InRangeEnemyIndex()
{
    std::list<int> nlist;

    GAME_OBJECT player = m_pPlayer->GetObjInfo();

    for (int i = 0; i < m_pEnemy->GetEnemyNumMax(); i++) 
    {
        if (m_pEnemy->GetObjInfo(i).use == false)continue;

        GAME_OBJECT enemy = m_pEnemy->GetObjInfo(i);

        //  プレイヤーの射程内なら
        if (IsApproach(m_Range, player.pos, enemy.pos, player.size.x, enemy.size.x)) 
        {
            nlist.push_back(i);
        }

    }


    return nlist;
}










int PlayerAndEnemyCollision::IsCollisions(int index)
{
    //  エネミーの位置とサイズ
    D3DXVECTOR3 e_pos = m_pEnemy->GetObjInfo(index).pos;
    D3DXVECTOR3 e_size = m_pEnemy->GetObjInfo(index).size;

    //  プレイヤーの位置とサイズ
    D3DXVECTOR3 p_pos = m_pPlayer->GetObjInfo().pos;
    D3DXVECTOR3 p_size = m_pPlayer->GetObjInfo().size / 2.0f;

    //  当たり判定
    if (e_pos.x + e_size.x >= p_pos.x - p_size.x &&
        e_pos.x - e_size.x <= p_pos.x + p_size.x) {

        if (e_pos.y + e_size.y >= p_pos.y - p_size.y &&
            e_pos.y - e_size.y <= p_pos.y + p_size.y) {

            if (e_pos.z + e_size.z >= p_pos.z - p_size.z &&
                e_pos.z - e_size.z <= p_pos.z + p_size.z) {

                return index;
            }
        }
    }

    return -1;
}

int PlayerAndEnemyCollision::IsCollisions_Bullets(int index, int index2)
{
    //  エネミーの位置とサイズ
    D3DXVECTOR3 e_pos = m_pEnemy->GetObjInfo(index).pos;
    D3DXVECTOR3 e_size = m_pEnemy->GetObjInfo(index).size;

    //  プレイヤーの位置とサイズ
    D3DXVECTOR3 i_pos = m_pBullet->GetObjInfo(index2).pos;
    D3DXVECTOR3 i_size = m_pBullet->GetObjInfo(index2).size / 2.0f;

    //  当たり判定
    if (e_pos.x + e_size.x >= i_pos.x - i_size.x &&
        e_pos.x - e_size.x <= i_pos.x + i_size.x) {

        if (e_pos.y + e_size.y >= i_pos.y - i_size.y &&
            e_pos.y - e_size.y <= i_pos.y + i_size.y) {

            if (e_pos.z + e_size.z >= i_pos.z - i_size.z &&
                e_pos.z - e_size.z <= i_pos.z + i_size.z) {

                return index;
            }
        }
    }

    return -1;
}

D3DXVECTOR3 PlayerAndEnemyCollision::VectorOfPlayer_Set(D3DXVECTOR3 pos1 ,D3DXVECTOR3 pos2,FLOAT speed)
{
    //  各二組の軸に対応する面上での角度取得
    float xyRot = atan2f(pos2.y - pos1.y, pos2.x - pos1.x);
    float xzRot = atan2f(pos2.z - pos1.z, pos2.x - pos1.x);
    float zyRot = atan2f(pos2.y - pos1.y, pos2.z - pos1.z);

    //  プレイヤーに送るようの変数
    D3DXVECTOR3 vec;
    vec.x = (cosf(xyRot) + cosf(xzRot)) * speed;
    vec.y = (sinf(xyRot) + sinf(zyRot)) * speed;
    vec.z = (sinf(xzRot) + cosf(zyRot)) * speed;

    return vec;
}

void PlayerAndEnemyCollision::SetDiamondVec()
{
    //  エネミーがDiamondの時だけ実行
    if (m_pEnemy[0].ReturnIndex() != ENEMY_DIAMOND)return;

    for (int i = 0; i < m_pEnemy->GetEnemyNumMax(); i++) 
    {
        if (m_pEnemy->GetObjInfo(i).use == false)continue;
        if (m_pEnemy->GetObjInfo(i).free != false)continue;

        // vec設定
        m_pEnemy->SetVec(i,VectorOfPlayer_Set( m_pEnemy->GetObjInfo(i).pos, m_pPlayer->GetObjInfo().pos, 1.0f));
    }
}

//  エネミー殺してエフェクト表示
void PlayerAndEnemyCollision::EnemyExplosionOnece()
{
    for (int i = 0; i < m_pEnemy->GetEnemyNumMax(); i++)
    {
        if (m_pEnemy->GetObjInfo(i).use == false)continue;

        m_Explosion.SetEffects(m_pEnemy->GetObjInfo(i).pos);
        m_pEnemy->SetUseFalse(i);
        
    }
}

//  プレイヤーが死んだらリザルトシーンへ
void PlayerAndEnemyCollision::ToNextScene()
{
    if (m_CollExplosionIndex >= 0)
        m_IsColl = true;

    if (m_IsColl)
    {
        if (m_Explosion.GetObjs(m_CollExplosionIndex)->use == false)
        {

            SetIsClear(false);
            SceneTransition(SCENE_RESULT);
        }
    }


}
