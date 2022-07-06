using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "BoundPower",menuName = "CreateBoundPower")]

//ブロックのバウンドパワーデータScriptableObject生成用
public class BlockVariable : ScriptableObject
{
    public float boundPower;
}
