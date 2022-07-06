using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Item : MonoBehaviour
{
    public AudioClip ItemSound;
    AudioSource audioSource;

    [SerializeField] ParticleSystem getParticle;

    private ScoreManager scoreManager;

    void Start()
    {
        audioSource = GetComponent<AudioSource>();

        // スコアマネージャーにタグを付けないと機能しないので注意
        scoreManager = GameObject.FindWithTag("Score").GetComponent<ScoreManager>();
    }

    public void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.name == "Player")
        {
            // スコア加算
            scoreManager.AddScore(1);

            //Debug.Log("Itemに衝突");
            Destroy(gameObject);
            AudioSource.PlayClipAtPoint(ItemSound, transform.position);//効果音をならす
            
            Instantiate(getParticle, transform.position, Quaternion.identity);            
        }

        if(collision.gameObject.name == "Gatekeeper")
        {
            Destroy(gameObject);
            Instantiate(getParticle, transform.position, Quaternion.identity);
            AudioSource.PlayClipAtPoint(ItemSound, transform.position);//効果音をならす
        }
    }


}
