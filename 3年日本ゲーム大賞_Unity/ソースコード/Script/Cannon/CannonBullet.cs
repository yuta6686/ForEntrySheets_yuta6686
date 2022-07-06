using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CannonBullet : MonoBehaviour
{   
    public GameObject explosion;
    public float speed;
    // Start is called before the first frame update
    void Start()
    {
        Instantiate(explosion, transform.position, new Quaternion());
    }

    // Update is called once per frame
    void Update()
    {
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.gameObject.CompareTag("Player"))
        {
            collision.gameObject.GetComponent<PlayerLife>().GetDamege(1);
            Destroy(gameObject);
            Instantiate(explosion, transform.position, new Quaternion());
        }
        else if(collision.gameObject.CompareTag("Cannon"))
        {

        }
        else
        {
            Destroy(gameObject);
            Instantiate(explosion, transform.position, new Quaternion());
        }
    }
}
