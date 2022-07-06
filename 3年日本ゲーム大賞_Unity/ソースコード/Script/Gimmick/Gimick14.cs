using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Gimick14 : MonoBehaviour
{
    //このオブジェクトの開始時のサイズを格納する
    private Vector3 InitScale;

    //現在消えているか否か
    public bool IsClean = false;

    // Start is called before the first frame update
    void Start()
    {
        InitScale = transform.localScale;

        //消えているかどうかの初期化
        if (IsClean)
        {
            transform.localScale = new Vector3(0, 0, 0);
        }
        else
        {
            transform.localScale = new Vector3(InitScale.x, InitScale.y, InitScale.z);
        }

    }

    // Update is called once per frame
    void Update()
    {
      
    }

    //大きさを変えて出したり消したりします
    public void ChengeScale()
    {
        if (IsClean)
        {
            transform.localScale = new Vector3(InitScale.x, InitScale.y, InitScale.z);
            IsClean = false;
        }
        else
        {
            transform.localScale = new Vector3(0, 0, 0);
            IsClean = true;
        }
    }
}
