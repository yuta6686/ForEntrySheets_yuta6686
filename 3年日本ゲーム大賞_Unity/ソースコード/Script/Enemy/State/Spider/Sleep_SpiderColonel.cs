using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Sleep_SpiderColonel : IState<Spider>
{
    public void Initialize(Spider owner)
    {
        if (owner.enemyAnimeState != null)
            owner.enemyAnimeState.SetAnimation(0, owner.IDOL_ANIMATION, true);
        else
            Debug.Log("enemyAnimeStateがnullです");
    }

    public void Execute(Spider owner)
    {
        Transform children = owner.spiderNetParent.GetComponentInChildren<Transform>();
        if (children.childCount == 0)
            return;
        foreach(Transform nets in children)
            if(nets.GetComponent<SpiderNet>().playerOnNet)
            {
                owner.m_StateContext.ChangeState(new Chase_SpiderColonel());
            }
    }

    public void Terminate(Spider owner)
    {
    }
}
