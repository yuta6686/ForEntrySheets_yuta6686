using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class S_EffectLanding : MonoBehaviour
{
    public ParticleSystem StrongLanding;
    public ParticleSystem WeekLanding;

    public float minSpeed = 10.0f;
    private ParticleSystem strongLanding;
    //private ParticleSystem weekLanding;    
    public bool IsFire { get; set; }

    float movementSpeed;
    Rigidbody2D rigidbody2D;


    // Start is called before the first frame update
    void Start()
    {
        rigidbody2D = GetComponent<Rigidbody2D>();

        strongLanding = Instantiate(StrongLanding, transform.position, Quaternion.identity);
        strongLanding.Stop();

        //weekLanding = Instantiate(WeekLanding, transform.position, Quaternion.identity);
        //weekLanding.Stop();
    }

    // Update is called once per frame
    void Update()
    {
        movementSpeed = rigidbody2D.velocity.magnitude;
        

        if(movementSpeed >= minSpeed)
        {
            IsFire = true;
        }else
        {
            IsFire = false;
        }
    }
    private void OnCollisionEnter2D(Collision2D collision)
    {

        if (collision.transform.tag == "Bound")
        {
            foreach (ContactPoint2D contactPoint in collision.contacts)
            {
                Vector2 localPoint = transform.InverseTransformPoint(contactPoint.point);

                if (localPoint.y <= -0.15)
                {
                    if (IsFire == true)
                    {
                        //Debug.Log(movementSpeed);
                        strongLanding.transform.position = new Vector3(transform.position.x, transform.position.y - 0.5f, transform.position.z);
                        strongLanding.Play();
                        S_EffectLandingUI.instance.PlayUIEffects();
                    }
                    else
                    {
                        //weekLanding.transform.position = transform.position;
                        //weekLanding.Play();
                        Instantiate(WeekLanding, transform.position, Quaternion.identity);
                    }
                }
            }
        }
    }
}

