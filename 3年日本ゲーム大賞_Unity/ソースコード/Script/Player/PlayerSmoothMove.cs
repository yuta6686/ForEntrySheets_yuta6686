using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/*=======================
  PlayerSmoothMove
						 Author :君島朝日
						Date   :2022/04/09
--------------------------------------------
機敏にプレイヤーを動かしてみるスクリプト
=========================*/

public class PlayerSmoothMove : MonoBehaviour
{
    private float speed;
    //Addforceでかける力
    public float XYSpeed = 5;
    //左右の速度の限界
    public float SpeedLimit = 65;

    //減速度
    public float SpeedDece = 3;
    //これ以下の速度になると動きを止める
    public float SpeedDeadZone = 0.001f;

    private Rigidbody2D rb;
    private float timer;

    private Vector2 move;

    PlayerActionInput input;

    void Start()
    {
        rb = GetComponent<Rigidbody2D>();

        //InputSystemを有効化
        input = new PlayerActionInput();

        input.Enable();

        speed = 0.0f;
    }

    void Update()
    {
        var vec1 = new Vector3(0, 0, 0);
        vec1 = rb.velocity;

        move = input.Player.Move.ReadValue<Vector2>();
        //Debug.Log(move);

        //右入力で右向きに動く
        if (move.x > 0)
        {
            speed = XYSpeed;
            rb.AddForce(transform.right * speed);

            //一定以上の速度にならない
            if (SpeedLimit <= rb.velocity.x)
            {
                rb.GetComponent<Rigidbody2D>().velocity = new Vector3(SpeedLimit, vec1.y, vec1.z);
            }
        }
        //左入力で左向きに動く
        else if (move.x < 0)
        {
            speed = -XYSpeed;
            rb.AddForce(transform.right * speed);

            //一定以上の速度にならない
            if (-SpeedLimit >= rb.velocity.x)
            {
                rb.GetComponent<Rigidbody2D>().velocity = new Vector3(-SpeedLimit, vec1.y, vec1.z);
            }
        }
        else
        {
            //操作していないときは減速する
           
            if (vec1.x <= SpeedDeadZone && vec1.x >= -SpeedDeadZone)
                rb.GetComponent<Rigidbody2D>().velocity = new Vector3(0, vec1.y, vec1.z);
            else if(vec1.x >= SpeedDeadZone)
                rb.AddForce(transform.right * -SpeedDece);
            else if(vec1.x <= -SpeedDeadZone)
                rb.AddForce(transform.right * SpeedDece);

           
        }


    }
}
