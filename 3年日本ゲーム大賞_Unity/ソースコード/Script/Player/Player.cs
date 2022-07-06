using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
/*=======================
  PlayerSmoothMove(Author:君島朝日 Date:2022/04/09)
  機敏にプレイヤーを動かしてみるスクリプト
  PlayerJumpControllerの一部
=========================*/

public class Player : MonoBehaviour
{

    private float speed;
    //Addforceでかける力
    public float XSpeed;
    //左右の速度の限界
    public float SpeedLimit_X;

    public bool Brake;
    public float BrakeForce;

    //// 速度制限一覧
    //public float HardSpeedLimit_Y;
    //public float MiddleSpeedLimit_Y;
    //public float SoftSpeedLimit_Y;

    //減速度
    public float SpeedDece = 3;
    //これ以下の速度になると動きを止める
    public float SpeedDeadZone = 0.001f;

    static public  Rigidbody2D rb;

    public Vector2 move { get; private set; }

    static public PlayerActionInput input;

    void Start()
    {
        //Application.targetFrameRate = 120;

        rb = GetComponent<Rigidbody2D>();

        //InputSystemを有効化
        input = new PlayerActionInput();

        input.Enable();

        speed = 0.0f;

        //mTouch = GrandTouch.NONE;
    }

    void Update()
    {
        var vec1 = new Vector3(0, 0, 0);
        vec1 = rb.velocity;

        move = input.Player.Move.ReadValue<Vector2>();
        
        // 左右入力で動く
        if (move.x != 0)
        {
            // スティックの倒し具合で速度も変わる
            rb.AddForce(transform.right * XSpeed * move.x);

            //入力している方向と反対に力がかかっているとき更に入力方向に力を加える ※要はブレーキ
            if (Brake)
            {
                if (rb.velocity.x < 0 && move.x > 0 ||
                rb.velocity.x > 0 && move.x < 0)
                {
                    rb.AddForce(transform.right * XSpeed * move.x * BrakeForce);
                }
            }


            //一定以上の速度にならない
            //if (SpeedLimit_X <= rb.velocity.x)
            //{
            //    rb.velocity = new Vector3(SpeedLimit_X, vec1.y, vec1.z);
            //}
            //else if (-SpeedLimit_X >= rb.velocity.x)
            //{
            //    rb.velocity = new Vector3(-SpeedLimit_X, vec1.y, vec1.z);
            //}
        }
        //操作していないときは減速する (X方向)
        else
        {
            if (vec1.x <= SpeedDeadZone && vec1.x >= -SpeedDeadZone)
                rb.velocity = new Vector3(0, vec1.y, vec1.z);
            else if (vec1.x >= SpeedDeadZone)
                rb.AddForce(transform.right * -SpeedDece);
            else if (vec1.x <= -SpeedDeadZone)
                rb.AddForce(transform.right * SpeedDece);

        }
    }


    // オブジェクトと接地しているとき
    private void OnCollisionEnter2D(Collision2D other)
    {
        //// 地面に触れている間 HARD
        //if (other.gameObject.CompareTag("Ground Hard") || other.gameObject.CompareTag("Wall"))
        //{
        //    mTouch = GrandTouch.HARD;
        //}

        //// 地面に触れている間 MIDDLE
        //if (other.gameObject.CompareTag("Ground Middle"))
        //{
        //    mTouch = GrandTouch.MIDDLE;
        //}

        //// 地面に触れている間 SOFT
        //if (other.gameObject.CompareTag("Ground Soft"))
        //{
        //    mTouch = GrandTouch.SOFT;
        //}

        //Debug.Log("OnCollisionEnter2D: " + other.gameObject.name);

    }

    // オブジェクトと接地してないとき
    private void OnCollisionExit2D(Collision2D other)
    {

    }

    // 侵入判定
    void OnTriggerEnter2D(Collider2D other)
    {

    }

    void OnTriggerExit2D(Collider2D other)
    {

    }

}