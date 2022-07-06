using UnityEngine;
using UnityEngine.SceneManagement;

//ハチ　攻撃状態定義用EnemyManagerのparctialスクリプト

public partial class EnemyManager
{
    public class BeeStateAttack : EnemyStateBase
    {
        EnemyManager m_owner;
        float ATTACK_SPEED = 10;

        public override void OnEnter(EnemyManager owner)
        {
            m_owner = owner;
            Spine.TrackEntry trackEntry = owner.SetAnimation(owner.attackAnimationName);
            trackEntry.Complete += TrackEntryComplete;

            Vector2 vec = owner.player.transform.position - owner.transform.position;

            //向き補正
            if(vec.x >= 0)
            {
                owner.transform.localScale = new Vector2(-0.6f, 0.6f);
            }
            else if(vec.x <= 0)
            {
                owner.transform.localScale = new Vector2(0.6f, 0.6f);
            }

            vec.Normalize();
            owner.rigidbody2D.velocity = vec * ATTACK_SPEED;
        }

        public override void OnUpdate(EnemyManager owner)
        {
        }

        public override void OnCollision(EnemyManager owner)
        {
            //SceneManager.LoadScene("GameOverScene");

        }

        private void TrackEntryComplete(Spine.TrackEntry trackEntry)
        {
            m_owner.StateTransition(m_owner.stateWaiting);
        }
    }
}