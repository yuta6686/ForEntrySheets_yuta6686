using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

// DX
/*==============================================================================
  Thruster
														 Author :君島朝日
														 Date   :2022/03/10
--------------------------------------------------------------------------------
スラスターの処理をするスクリプト
==============================================================================*/

public class Thruster : MonoBehaviour
{
    [SerializeField] bool isButton = false;

    public float X_SpeedAirDush;
    public float Y_SpeedAirDush;

    // スラスターを使える状態かのチェック
    public bool SwitchThrusterCheck;

    // レンジに入ってどれぐらいの時間で使えるようになるか 0.5秒の場合は0.5と入力
    public float ThrusterCooltime;

    private Rigidbody2D rb;

    private Vector2 Lstick;

    static public PlayerActionInput input;

    [SerializeField] ParticleSystem thrusterEffect;

    public static ParticleSystem particle;

    int stayCount;

    //スラスタークールダウン用変数
    int cooldown = 0;
    const int COOL_DOWN_COUNT = 30;

    // アニメーション用変数
    PlayerAnimationManager pAM;

    void Start()
    {
        rb = GetComponent<Rigidbody2D>();

        SwitchThrusterCheck = true;

        //InputSystemを有効化
        input = new PlayerActionInput();

        input.Enable();

        // アニメーション用変数
        pAM = transform.GetComponent<PlayerAnimationManager>();
    }

    private void Awake()
    {
        //Invoke("ThrusterSet", 1);

        particle = Instantiate(thrusterEffect, transform.position, Quaternion.identity);
        particle.Stop();
    }

    void Update()
    {
        cooldown--;

        if (cooldown <= 0)
        {
            if (input.Player.ThrusterButton.triggered)
            {
                ButtonThruster();
                cooldown = COOL_DOWN_COUNT;
            }
        }

        particle.transform.position = transform.position;
    }

    private void OnCollisionStay2D(Collision2D collision)
    {
        //レイヤーネーム取得
        string layerName = LayerMask.LayerToName(collision.gameObject.layer);

        if (layerName == "Ground")
        {
            //衝突位置取得
            foreach (ContactPoint2D contactPoint in collision.contacts)
            {
                //プレイヤーのローカル座標に変換
                Vector2 localPoint = transform.InverseTransformPoint(contactPoint.point);

                //Debug.Log(localPoint);

                //プレイヤーの下面に当たっていたら
                if (localPoint.y <= -0.2)
                {
                    if (localPoint.x < 0.25)
                    {
                        stayCount++;
                        if (stayCount >= 20)
                        {
                            SwitchThruster();
                            stayCount = 0;
                        }
                    }
                }
            }
        }
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        //レイヤーネーム取得
        string layerName = LayerMask.LayerToName(collision.gameObject.layer);

        if (layerName == "Ground")
        {
            //衝突位置取得
            foreach (ContactPoint2D contactPoint in collision.contacts)
            {
                //プレイヤーのローカル座標に変換
                Vector2 localPoint = transform.InverseTransformPoint(contactPoint.point);

                //プレイヤーの下面に当たっていたら
                if (localPoint.y <= -0.2)
                {
                    if (localPoint.x < 0.25)
                    {
                        SwitchThruster();
                    }
                }
            }
        }
    }

    void SwitchThruster()
    {
        if (!SwitchThrusterCheck)
        {
            //Debug.Log(ThrusterCooltime + "秒後にスラスター使用可能になった");
            SwitchThrusterCheck = true;
        }
    }

    public void ButtonThruster()
    {
        if (SwitchThrusterCheck)
        {
            Lstick = input.Player.Move.ReadValue<Vector2>();

            pAM.AnimationJump();
            particle.Play();

            rb.velocity = new Vector3(0, 0, 0);

            //Lスティックを入力してなかったら
            if (Lstick.y <= 0.6f && Lstick.y >= -0.6f
                && Lstick.x <= 0.6f && Lstick.x >= -0.6f)
            {
                rb.AddForce(transform.up * Y_SpeedAirDush, ForceMode2D.Impulse);
            }
            else
            {
                //左右の移動
                rb.AddForce(transform.right * X_SpeedAirDush * Lstick.x, ForceMode2D.Impulse);
                //上下の移動
                rb.AddForce(transform.up * Y_SpeedAirDush * Lstick.y, ForceMode2D.Impulse);
            }
            SwitchThrusterCheck = false;
        }
    }
}