using UnityEngine;

//ハチ　攻撃後の3秒待機定義用EnemyManagerのparctialスクリプト

public partial class EnemyManager
{
    public class BeeStateWaiting : EnemyStateBase
    {
        public override void OnEnter(EnemyManager owner)
        {
            owner.SetAnimation(owner.idolAnimationName);
            owner.StateTransition(owner.stateIdol, 3);
            owner.rigidbody2D.velocity = Vector2.zero;
            owner.GetComponentInChildren<ParticleSystem>().GetComponentInChildren<Renderer>().material.SetFloat("Green", 3.0f);
            owner.GetComponentInChildren<ParticleSystem>().Stop();
            
        }

        public override void OnCollision(EnemyManager owner)
        {
            owner.Destroy();
        }
    }
}