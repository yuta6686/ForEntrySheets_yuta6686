using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class S_EffectLandingUI : MonoBehaviour
{
    public static S_EffectLandingUI instance;

    public  ParticleSystem landingEffect;
    private ParticleSystem effect;

    public float posY = -400;

    public void Awake()
    {
        if(instance == null)
        {
            instance = this;
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        effect = Instantiate(landingEffect,transform.position,Quaternion.identity);
        effect.Stop();
        effect.transform.SetParent(transform, false);
        effect.transform.localPosition = new Vector3(0, posY, 0);
    }

    public void PlayUIEffects()
    {
        effect.Play();
    }

    // Update is called once per frame
    void Update()
    {
    }
}
