using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class JumpSE : MonoBehaviour
{
    public AudioClip jumpSound;
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

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Bound")
        {
            audioSource.PlayOneShot(jumpSound);
        }
    }
}
