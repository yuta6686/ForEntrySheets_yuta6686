using System.Collections;
using System.Collections.Generic;
using UnityEngine;
/*==============================================================================
   File [StateContext.h]
														Author : AT12B173/18/sawada
														Date   : 2022/02/26
--------------------------------------------------------------------------------
any comments that you want someone to read
==============================================================================*/

public class StateContext<StateOwner>
{
    private StateOwner         m_Owner;
    public  IState<StateOwner> m_CurrentState ;
    public  IState<StateOwner> m_PreviousState;
    public  IState<StateOwner> m_GlobalState  ;

    public StateContext(StateOwner owner)
    {
        m_Owner         = owner;
        m_CurrentState  = null ;
        m_PreviousState = null ;
        m_GlobalState   = null ;
    }
    public void Update()
    {
        if (m_GlobalState  != null) m_GlobalState.Execute(m_Owner);
        if (m_CurrentState != null) m_CurrentState.Execute(m_Owner);
    }
    public void ChangeState(IState<StateOwner> nextState)
    {
        m_PreviousState = m_CurrentState;
        m_CurrentState.Terminate(m_Owner);
        m_CurrentState = nextState;
        m_CurrentState.Initialize(m_Owner);
    }
    public void RevertToPreviousState()
    {
        ChangeState(m_PreviousState);
    }
    //bool isInState(IState<StateOwner> state){}
}
