using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
/*==============================================================================
  Booster
														 Author :君島朝日
														 Date   :2022/03/10
--------------------------------------------------------------------------------
水噴射移動の処理をするスクリプト
==============================================================================*/

public class Booster : MonoBehaviour
{
    // 横方向の速度
    private float speed;
    public float SpeedLimit;

    // 縦方向の速度
    private float Highlowspeed;
    public float HighlowSpeedLimit;


    private Rigidbody2D rb;
    private float timer;

    private Vector2 move;

    PlayerActionInput input;

    void Start()
    {
        rb = GetComponent<Rigidbody2D>();

        speed = 0.0f;
        Highlowspeed = 0.0f;

        //InputSystemを有効化
        input = new PlayerActionInput();

        input.Enable();
    }

    void Update()
    {
        UseThruster();
    }

    //ブースターを使って移動を行う関数
    void UseThruster()
    {

        move = input.Player.Thruster.ReadValue<Vector2>();

        //右入力で右向きに動く
        if (move.x > 0)
        {
            speed = SpeedLimit;
            //左右の移動
            rb.AddForce(transform.right * speed);

        }
        //左入力で左向きに動く
        else if (move.x < 0)
        {
            speed = -SpeedLimit;
            //左右の移動
            rb.AddForce(transform.right * speed);

        }
        else
        {
            speed *= 0.99f;
        }

        //上入力で上向きに動く
        if (move.y > 0)
        {
            Highlowspeed = HighlowSpeedLimit;
            //上下の移動
            rb.AddForce(transform.up * Highlowspeed);

        }
        //下入力で下向きに動く
        else if (move.y < 0)
        {
            Highlowspeed = -HighlowSpeedLimit;
            //上下の移動
            rb.AddForce(transform.up * Highlowspeed);

        }
        else
        {
            Highlowspeed *= 0.99f;
        }

    }
}
