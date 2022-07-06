using UnityEngine;

//ハチ　待機状態定義用EnemyManagerのparctialスクリプト
public partial class EnemyManager
{
    public class BeeStateIdol : EnemyStateBase
    {
        public override void OnEnter(EnemyManager owner)
        {
            owner.SetAnimation(owner.idolAnimationName);
            owner.GetComponentInChildren<ParticleSystem>().GetComponentInChildren<Renderer>().material.SetFloat("Green", 3.0f);
            owner.GetComponentInChildren<ParticleSystem>().Stop();
            
        }
        public override void OnUpdate(EnemyManager owner)
        {
            owner.rigidbody2D.velocity = Vector2.zero;

            //画面内に敵が表示されたらホーミングへ遷移
            if (owner.isEnterScreen)
            {
                owner.StateTransition(owner.stateHoming);
                //Debug.Log("見えた");
            }
        }

        public override void OnCollision(EnemyManager owner)
        {
            owner.Destroy();
        }
    }
}
