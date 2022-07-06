using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//----------------------------------------------------------------------
//  バブルエフェクトの設定
//  
//----------------------------------------------------------------------

public class S_EffectBubble : MonoBehaviour
{
    public ParticleSystem BubbleEffect;
    public float NomalizeValue = 2.5f;
    public float NomalizeValue_Trail = 20.0f;
    public float MinValue_Trail = 20.0f;
    private TrailRenderer trail;

    private ParticleSystem[] childrenBubble;
    private ParticleSystem particle;
    

    Rigidbody2D rigidbody2D;
    public static float movementSpeed { get; set; }
    float movementSpeed_Trail;

   

    // Start is called before the first frame update
    void Start()
    {
        rigidbody2D = GetComponent<Rigidbody2D>();

        particle = Instantiate(BubbleEffect,transform.position,Quaternion.identity);

        childrenBubble = particle.GetComponentsInChildren<ParticleSystem>();

        trail = GetComponentInChildren<TrailRenderer>();
    }

    // Update is called once per frame
    void Update()
    {
        movementSpeed = rigidbody2D.velocity.magnitude;

        foreach(var x in childrenBubble)
        {
            var em = x.emission;
            em.enabled = true;

            em.rateOverTime = movementSpeed / NomalizeValue - 1.0f;
        }

        if (movementSpeed < MinValue_Trail)
        {
            movementSpeed_Trail *= 0.9f;
        }
        else
        {
            movementSpeed_Trail = movementSpeed / NomalizeValue_Trail;
        }

        

        

        trail.material.SetFloat("_Alpha", movementSpeed_Trail);
        trail.material.SetFloat("_ScrollSpeed", movementSpeed_Trail);

        particle.transform.position = this.transform.position;

        trail.transform.position = this.transform.position;
    }
}
