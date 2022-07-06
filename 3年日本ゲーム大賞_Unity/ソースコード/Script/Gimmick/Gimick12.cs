using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Gimick12 : MonoBehaviour
{
    [SerializeField] GameObject player;
    public float GimickPower = 50;
    private Rigidbody2D playerRigitBody2D;

    //一気に飛ぶモードかどうか
    public bool ImplusMode = false;
    public float GimickImplusPower = 30;

    // Start is called before the first frame update
    void Start()
    {
        playerRigitBody2D = player.GetComponent<Rigidbody2D>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnTriggerStay2D(Collider2D collision)
    {
        //Playerと当たった時
        if (collision.gameObject.tag == "Player" && ! ImplusMode)
        {
            //プレイヤーを移動
            ThrowPlayer();
        }
    }
    private void OnTriggerEnter2D(Collider2D collision)
    {
        //Playerと当たった時
        if (collision.gameObject.tag == "Player" && ImplusMode)
        {
            //プレイヤーを移動
            ThrowPlayer();
        }
    }

    void ThrowPlayer()
    {
        Quaternion angle = gameObject.transform.rotation;

        transform.rotation.ToAngleAxis(out float angle1, out Vector3 axis);

        Debug.Log(Mathf.Sin(angle.z * Mathf.PI / 180));

        if (! ImplusMode)
        {
            playerRigitBody2D.AddForce(this.transform.up * GimickPower * Mathf.Cos((angle.z) * Mathf.PI / 180));
            playerRigitBody2D.AddForce(this.transform.right * GimickPower * Mathf.Sin((angle.z ) * Mathf.PI / 180));
        }
        else
        {
            playerRigitBody2D.AddForce(this.transform.up * GimickImplusPower * -Mathf.Sin((angle.z - 90)* Mathf.PI / 180),ForceMode2D.Impulse);
            playerRigitBody2D.AddForce(this.transform.right * GimickImplusPower * Mathf.Cos((angle.z - 90) * Mathf.PI / 180), ForceMode2D.Impulse);
        }
        
    }
}
