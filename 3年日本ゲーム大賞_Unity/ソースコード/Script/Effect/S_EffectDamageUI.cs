using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class S_EffectDamageUI : MonoBehaviour
{
    public static S_EffectDamageUI instance;

    public  ParticleSystem landingEffect;    
    public float posY = -400;

    private ParticleSystem effect;
    private ParticleSystem[] cEffects;

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
        cEffects = effect.GetComponentsInChildren<ParticleSystem>();
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
      /*  if (Input.GetKeyDown(KeyCode.E))
        {
            PlayUIEffects();
        }*/
    }
}
