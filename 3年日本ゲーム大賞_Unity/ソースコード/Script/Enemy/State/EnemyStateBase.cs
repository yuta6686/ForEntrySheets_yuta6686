using UnityEngine;

//敵Stateの抽象クラス

public abstract class EnemyStateBase
{
    //Stateを変更したときに呼ばれる
    public virtual void OnEnter(EnemyManager owner) { }

    //ループで呼ばれる
    public virtual void OnUpdate(EnemyManager owner) { }

    //Stateを変更するときに呼ばれる
    public virtual void OnExit(EnemyManager owner) { }

    public virtual void OnCollision(EnemyManager owner) { }
}
