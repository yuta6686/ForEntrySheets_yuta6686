using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ReturnToInitialBase_SpiderColonel : IState<Spider>
{
    Vector3 previousPosition;
    public void Initialize(Spider owner)
    {
        owner.enemyAnimeState.SetAnimation(0, owner.MOVE_ANIMATION, true);
    }

    public void Execute(Spider owner)
    {
        Transform children = owner.spiderNetParent.GetComponentInChildren<Transform>();
        if (children.childCount == 0)
            return;
        foreach (Transform nets in children)
            if (nets.GetComponent<SpiderNet>().playerOnNet)
            {
                owner.m_StateContext.ChangeState(new Chase_SpiderColonel());
            }
        // if(owner.transform.position != initialPosition)

        if(Vector3.Distance(owner.initialPosition, owner.transform.position) > 0.1f)
        {
            owner.transform.position = Vector3.MoveTowards(
                                                    owner.transform.position,
                                                    owner.initialPosition,
                                                    owner.Speed);
        }
        else
        {
            owner.m_StateContext.ChangeState(new Sleep_SpiderColonel());
        }

        if (!owner.IsOnNet(owner.transform.position))
        {
            owner.transform.position = previousPosition;
        }

        previousPosition = owner.transform.position;
    }

    public void Terminate(Spider owner)
    {
    }
}
