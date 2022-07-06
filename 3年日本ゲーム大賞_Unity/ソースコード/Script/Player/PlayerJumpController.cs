using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class PlayerJumpController : MonoBehaviour
{
    private Rigidbody2D rbody2D;

    public float jumpForce;
    public float BoundForce;

    private bool jumpCount = false;
    private bool BoundCount = false;

    private Vector2 move;

    PlayerActionInput input;


    void Start()
    {
        rbody2D = GetComponent<Rigidbody2D>();

        //InputSystemを有効化
        input = new PlayerActionInput();

        input.Enable();

    }

    void Update()
    {
        move = input.Player.Move.ReadValue<Vector2>();

        // ジャンプボタン(↓)が押されたか
        bool jumpswitch = false;

        // 下入力
        if (move.y < 0)
        {
            jumpswitch = true;
        }
        else
        {
            jumpswitch = false;
        }


        // 地面の反発(↓ボタン + Lスティック)
        if (jumpswitch && this.jumpCount)
        {
            //this.rbody2D.AddForce(transform.up * jumpForce);
            jumpCount = false;
        }


    }

    // オブジェクトと接地しているとき
    private void OnCollisionEnter2D(Collision2D other)
    {
        // 地面に触れている間 HARD
        if (other.gameObject.CompareTag("Ground Hard") || other.gameObject.CompareTag("Wall"))
        {
            jumpCount = true;
        }

        // 地面に触れている間 MIDDLE
        if (other.gameObject.CompareTag("Ground Middle"))
        {
            jumpCount = true;
        }

        // 地面に触れている間 SOFT
        if (other.gameObject.CompareTag("Ground Soft"))
        {
            jumpCount = true;
        }

        //Debug.Log("OnCollisionEnter2D: " + other.gameObject.name);

    }

    // オブジェクトと接地してないとき
    private void OnCollisionExit2D(Collision2D other)
    {
        jumpCount = false;
        BoundCount = false;
    }

    // 侵入判定
    void OnTriggerEnter2D(Collider2D other)
    {

    }

    void OnTriggerExit2D(Collider2D other)
    {

    }

    //オブジェクトと接地しているかを返すゲッター
    public bool GetJumpCount()
    {
        return jumpCount;
    }
}