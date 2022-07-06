using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SandSE : MonoBehaviour
{
    //サウンド
    public AudioClip SandSound;
    AudioSource audioSource;

    // Start is called before the first frame update
    void Start()
    {
        //AudioSourceの取得
        audioSource = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {

    }

    private void OnTriggerEnter2D(Collider2D other)
    {
        //プレイヤーに触れたら音を鳴らす
        if (other.gameObject.tag == "Player")
        {
            sandSound();
        }
    }

    //音を鳴らす処理
     public void sandSound()
    {
        audioSource.PlayOneShot(SandSound);
    }
}
