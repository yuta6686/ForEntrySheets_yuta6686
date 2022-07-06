using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/*=======================
  TestBoosterBullet
						 Author :君島朝日
						Date   :2022/04/5
--------------------------------------------
ブースターで発射される物の移動をするスクリプト
=========================*/

public class TestBoosterBullet : MonoBehaviour
{
    // 横方向の速度
    private float SpeedLimit = 0;

    // 縦方向の速度
    private float HighlowSpeedLimit = 0;

    //trueにすると軌跡の表示になる
    public bool LinerMode;

    // Start is called before the first frame update
    void Start()
    {
        //右入力で左向きに動く
        if (Input.GetKey(KeyCode.L))
        {
            SpeedLimit = -10;
        }
        //左入力で右向きに動く
        else if (Input.GetKey(KeyCode.J))
        {
            SpeedLimit = 10;
        }
       
        //上入力で下向きに動く
        if (Input.GetKey(KeyCode.I))
        {
            HighlowSpeedLimit = -10;
        }
        //下入力で上向きに動く
        else if (Input.GetKey(KeyCode.K))
        {
            HighlowSpeedLimit = 10;
        }

        // 2 秒後に削除する
        Destroy(gameObject, 2);
    }

    // Update is called once per frame
    void Update()
    {
        // 移動する
        
        Vector3 BulletPos = transform.position;
        BulletPos.x += SpeedLimit * Time.deltaTime;
        BulletPos.y += HighlowSpeedLimit * Time.deltaTime;

        if(!LinerMode)
        transform.position = BulletPos;
    }
}
