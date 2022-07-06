using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LifeManager : MonoBehaviour
{
    [SerializeField]
    private float ShowTime;
    [SerializeField]
    private float HideAlfaSpeed;

    // 表示するオブジェクトの登録
    [SerializeField]
    private LifeCange Life_3;
    [SerializeField]
    private LifeCange Life_2;
    [SerializeField]
    private LifeCange Life_1;

    public void ShowLife(int life)
    {
        if (life == 3)
        {
            Life_3.Set(ShowTime, HideAlfaSpeed);
        }

        if (life == 2)
        {
            Life_2.Set(ShowTime, HideAlfaSpeed);
        }

        if (life == 1)
        {
            Life_1.Set(ShowTime, HideAlfaSpeed);
        }
    }
}
