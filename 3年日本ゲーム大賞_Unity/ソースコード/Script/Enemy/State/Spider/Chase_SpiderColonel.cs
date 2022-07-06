using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Chase_SpiderColonel : IState<Spider>
{
    readonly float      CHASABLE_DISTANCE = 15;
    Vector3             previousPosition;
    float               attackTimer;

    public void Initialize(Spider owner)
    {
        owner.enemyAnimeState.SetAnimation(0, owner.MOVE_ANIMATION, true);
    }

    public void Execute(Spider owner)
    {
        if (!owner.IsOnNet(owner.player.transform.position))
        {
            owner.m_StateContext.ChangeState(new ReturnToInitialBase_SpiderColonel());
        }
        if (owner.IsContact(owner.gameObject, owner.player))
        {
            if (owner.isAttackable)
            {
                owner.m_StateContext.ChangeState(new Attack_SpiderColonel());
            }
        }
        else //追いかける
        {
            owner.transform.position = Vector3.MoveTowards(
                                                    owner.transform.position, 
                                                    owner.player.transform.position, 
                                                    owner.Speed);
            owner.transform.position = 
                new Vector3(
                    Mathf.Clamp(owner.transform.position.x, owner.netRangeMin.x, owner.netRangeMax.x),
                    Mathf.Clamp(owner.transform.position.y, owner.netRangeMin.y, owner.netRangeMax.y),
                    0
                );

            if (!owner.IsOnNet(owner.transform.position) || owner.IsContact(owner.gameObject, owner.player))
            {
                owner.transform.position = previousPosition;
            }

        }
        previousPosition = owner.transform.position;
    }

    public void Terminate(Spider owner)
    {
    }
}
