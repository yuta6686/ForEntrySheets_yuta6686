using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShaderController : MonoBehaviour
{

    [SerializeField] Material material = null;

    SpriteRenderer spriter;

    public float m_Emission = 1.0f;

    // Start is called before the first frame update
    void Start()
    {
        spriter = GetComponent<SpriteRenderer>();
        
    }

    // Update is called once per frame
    void Update()
    {

        if (Input.GetKeyDown(KeyCode.E))
        {
            m_Emission += 0.1f;

            spriter.material.SetFloat("_Emission_Vec1", m_Emission);
            
        }
        
    }
}


