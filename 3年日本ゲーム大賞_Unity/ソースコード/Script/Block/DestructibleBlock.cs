using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;

public class DestructibleBlock : MonoBehaviour
{
    [SerializeField] GameObject explosion;
    readonly private float PLAYER_MAGNITUDE = 5;

    //サウンド処理
    public AudioClip sound1;
    AudioSource audioSource;

    void Start()
    {
        //Componentを取得
        audioSource = GetComponent<AudioSource>();
    }

    public void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.gameObject.name == "Player")
        {
            Debug.Log("DestructibleBlockに衝突");

            if (collision.gameObject.GetComponent<Rigidbody2D>().velocity.sqrMagnitude > PLAYER_MAGNITUDE)
            {
                Debug.Log("破壊");
                Destroy(gameObject);
                AudioSource.PlayClipAtPoint(sound1, transform.position);//効果音をならす
                Instantiate(/*(GameObject)Resources.Load("Explosion001")*/explosion, transform.position, new Quaternion());
                
            }
        }
    }
}
