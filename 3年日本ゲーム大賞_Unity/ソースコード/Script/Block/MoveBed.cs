using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/*==============================================================================
  MoveBed
														 Author :君島朝日
														 Date   :2022/03/16
--------------------------------------------------------------------------------
移動床の処理をするスクリプト
==============================================================================*/

public class MoveBed : MonoBehaviour
{
    // 速度
    private float speed;
    public float SpeedLimit;

    //移動する距離
    public float DistanceX;
    public float DistanceY;

    //足場の座標
    private Vector2 Pos;

    //開始時の座標
    private Vector2 InitPos;

    //進む方向の判定フラグ
    private bool DirectionX;
    private bool DirectionY;

    private Rigidbody2D rb;
    private float timer;

    void Start()
    {
        rb = GetComponent<Rigidbody2D>();

        speed = 0.0f;

        InitPos = transform.position;
        Pos = transform.position;

        if (Pos.x <= InitPos.x + DistanceX)
            DirectionX = true;
        else
            DirectionX = false;

        if (Pos.y <= InitPos.y + DistanceY)
            DirectionY = true;
        else
            DirectionY = false;
    }

    void Update()
    {

        Move();
        Pos = transform.position;
    }

    //移動を行う関数
    void Move()
    {
        var vec1 = new Vector3(0, 0, 0);

        if (DistanceX != 0)
            if (DirectionX)
            {
                //右の移動
                speed = SpeedLimit;
                vec1.x = speed;

                rb.GetComponent<Rigidbody2D>().velocity = new Vector3(vec1.x, vec1.y, vec1.z);

                if (DistanceX > 0)
                {
                    if (Pos.x > InitPos.x + DistanceX)
                        DirectionX = false;
                }
                else
                {
                    if (Pos.x > InitPos.x)
                        DirectionX = false;
                }
            }
            else
            {
                //左の移動
                speed = -SpeedLimit;
                vec1.x = speed;

                rb.GetComponent<Rigidbody2D>().velocity = new Vector3(vec1.x, vec1.y, vec1.z);

                if (DistanceX > 0)
                {
                    if (Pos.x < InitPos.x)
                        DirectionX = true;
                }
                else
                {
                    if (Pos.x < InitPos.x + DistanceX)
                        DirectionX = true;
                }
            }

        if (DistanceY != 0)
            if (DirectionY)
            {
                //上の移動
                speed = SpeedLimit;
                vec1.y = speed;

                rb.GetComponent<Rigidbody2D>().velocity = new Vector3(vec1.x, vec1.y, vec1.z);

                if (DistanceY > 0)
                {
                    if (Pos.y > InitPos.y + DistanceY)
                        DirectionY = false;
                }
                else
                {
                    if (Pos.y > InitPos.y)
                        DirectionY = false;
                }
            }
            else
            {
                //下の移動
                speed = -SpeedLimit;
                vec1.y = speed;

                rb.GetComponent<Rigidbody2D>().velocity = new Vector3(vec1.x, vec1.y, vec1.z);

                if (DistanceY > 0)
                {
                    if (Pos.y <= InitPos.y)
                        DirectionY = true;
                }
                else
                {
                    if (Pos.y < InitPos.y + DistanceY)
                        DirectionY = true;
                }
            }
    }
}
