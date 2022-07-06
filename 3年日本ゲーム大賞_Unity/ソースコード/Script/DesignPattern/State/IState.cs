using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/*==============================================================================
   File [IState.h]
														Author : AT12B173/18/sawada
														Date   : 2022/02/26
--------------------------------------------------------------------------------
any comments that you want someone to read
==============================================================================*/

public interface IState<StateOwner>
{
    void Initialize(StateOwner owner);
    void Execute   (StateOwner owner);
    void Terminate (StateOwner owner);
}
