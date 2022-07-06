using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class S_Thuruster : MonoBehaviour
{
    //  Shader 
    [SerializeField] float minSpeed = 30.0f;
    private MeshRenderer mesh;
    private float moveNoiseSpeed;
    [SerializeField] float maxSpeed = 30.0f;

    //  Rotation    
    private Vector2 last, curr;


    //  Scale (親の影響を受けないようにする)
    public Vector3 defaultScale = Vector3.zero;
    

    public GameObject thurusterEffect;
    private GameObject thuruster;

    // Start is called before the first frame update
    void Start()
    {
        thuruster = Instantiate(thurusterEffect, transform.position, Quaternion.identity);

        mesh = thuruster.GetComponent<MeshRenderer>();
                       
    }

    // Update is called once per frame
    void Update()
    {
        //NotInfluencedByParent();

        //  Shader
        SetShaderValues();

        SetThrusterRotate();
    }
    private void SetThrusterRotate()
    {
        curr = transform.position;

        float angleDir = GetAngle(last, curr);
        //Debug.Log(angleDir);
        //Vector3 dir = new Vector3(Mathf.Cos(angleDir), Mathf.Sin(angleDir), 0.0f);

        //transform.localEulerAngles = dir;
        //transform.localRotation = Quaternion.Euler(dir);
        thuruster.transform.localRotation = Quaternion.AngleAxis(angleDir, Vector3.forward);

        last = transform.position;
        thuruster.transform.position = transform.position;
    }

    float GetAngle(Vector2 start, Vector2 end)
    {
        Vector2 dt = end - start;
        float rad = Mathf.Atan2(dt.y, dt.x);
        float degree = rad * Mathf.Rad2Deg;
        return degree;
    }


    private void SetShaderValues()
    {
        //  Shader 
        if (S_EffectBubble.movementSpeed < minSpeed)
        {
            moveNoiseSpeed *= 0.9f;
        }
        else
        {
            
            moveNoiseSpeed = S_EffectBubble.movementSpeed;
               
        }

        mesh.material.SetFloat("_Emission", moveNoiseSpeed);
        mesh.material.SetFloat("_BubbleSpeed", moveNoiseSpeed / 100.0f);
    }

    /*private void NotInfluencedByParent()
    {
        Vector3 lossScale = transform.lossyScale;
        Vector3 localScale = transform.localScale;

        transform.localScale = new Vector3(
                localScale.x / lossScale.x * defaultScale.x,
                localScale.y / lossScale.y * defaultScale.y,
                localScale.z / lossScale.z * defaultScale.z
        );


    }*/
}
