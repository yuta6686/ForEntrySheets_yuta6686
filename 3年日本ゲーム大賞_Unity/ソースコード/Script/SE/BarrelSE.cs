using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BarrelSE : MonoBehaviour
{
    public AudioClip BarrelSound;
    AudioSource audioSource;

    // Start is called before the first frame update
    void Start()
    {
        audioSource = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        //Playerと当たった時
        if (collision.gameObject.tag == "Player")
        {
            //1秒後に音を鳴らす
            Invoke("barrelSound", 1);
        }
    }

    //音を鳴らす処理
    void barrelSound()
    {
        audioSource.PlayOneShot(BarrelSound);
    }
}
