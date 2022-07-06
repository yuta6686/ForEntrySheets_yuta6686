using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Attack_SpiderColonel : IState<Spider>
{
    bool once;
    public void Initialize(Spider owner)
    {
        once = true;
        owner.enemyAnimeState.SetAnimation(0, owner.ATTACK_ANIMATION, true);
    }

    public void Execute(Spider owner)
    {
        if(once)
        {
            once = false;
            owner.Attack();
        }

        if(owner.isAttackable)
        {
            owner.m_StateContext.ChangeState(new Chase_SpiderColonel());
        }
    }

    public void Terminate(Spider owner)
    {
    }
}
