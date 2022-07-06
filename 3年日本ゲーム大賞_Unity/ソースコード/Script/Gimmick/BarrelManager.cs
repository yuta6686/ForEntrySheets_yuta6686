using UnityEngine;

public class BarrelManager : MonoBehaviour
{
    [SerializeField] GameObject player;
    [SerializeField] int THROW_POWER = 10;
    private bool isCatch;
    private Rigidbody2D playerRigitBody2D;

    void Start()
    {
        isCatch = false;
        playerRigitBody2D = player.GetComponent<Rigidbody2D>();
    }

    void Update()
    {
        //プレイヤーを掴む
        if (isCatch)
        {
            player.transform.position = this.transform.position;
            playerRigitBody2D.velocity = Vector3.zero;
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {   
        //Playerと当たった時
        if (collision.gameObject.tag == "Player")
        {
            //Debug.Log("当たった");

            isCatch = true;

            //1秒後にプレイヤーを投げる
            Invoke("ThrowPlayer", 1);
        }
    }

    void ThrowPlayer()
    {
        isCatch = false;

        playerRigitBody2D.AddForce(this.transform.up * THROW_POWER * 100);
    }
}