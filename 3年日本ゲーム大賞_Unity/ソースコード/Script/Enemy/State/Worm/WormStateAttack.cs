using UnityEngine;
using UnityEngine.SceneManagement;

//毛虫　攻撃状態定義用partialスクリプト

public partial class EnemyManager
{
    public class WormStateAttack : EnemyStateBase
    {
        int ATTACK_TIME = 60;
        int atkCnt = 0;
        EnemyManager m_owner;

        public override void OnEnter(EnemyManager owner)
        {
            m_owner = owner;
            Spine.TrackEntry trackEntry = owner.SetAnimation(owner.attackAnimationName);
            trackEntry.Complete += TrackEntryComplete;
            //owner.GetComponentInChildren<ParticleSystem>().Play();
            //Debug.Log(owner.transform.eulerAngles.z);
            //owner.transform.GetChild(0).GetChild(0).GetComponent<ParticleSystem>().startRotation
            //    = owner.transform.eulerAngles.z;
        }

        public override void OnUpdate(EnemyManager owner)
        {
            owner.rigidbody2D.velocity = new Vector2(0.0f, 0.0f);
        }

        public override void OnCollision(EnemyManager owner)
        {
            //SceneManager.LoadScene("GameOverScene");
        }

        private void TrackEntryComplete(Spine.TrackEntry trackEntry)
        {
            m_owner.StateTransition(m_owner.stateIdol);
        }
    }
}