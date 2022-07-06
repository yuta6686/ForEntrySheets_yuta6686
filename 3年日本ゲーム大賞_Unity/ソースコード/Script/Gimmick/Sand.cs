using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Sand : MonoBehaviour
{
    //thrusterのスクリプト取得
    GameObject thruster;
    Thruster thrusterScript;
    SandSE sandSE;
    
    //砂の抵抗力
    public int SandDrag = 10;
    // Start is called before the first frame update
    void Start()
    {
        thruster = GameObject.Find("Player");
        thrusterScript = thruster.GetComponent<Thruster>();

    }

    // Update is called once per frame
    void Update()
    {
        
    }


    //砂の中にいる時
    void OnTriggerStay2D(Collider2D collider)
    {
        if (collider.gameObject.tag == "Player")
        {
            //Debug.Log("すり抜けている");
            GameObject.Find("Player").GetComponent<Rigidbody2D>().drag = SandDrag;
            thrusterScript.SwitchThrusterCheck = true;
        }
    }

    //砂からでた時
    void OnTriggerExit2D(Collider2D collider)
    {
        if (collider.gameObject.tag == "Player")
        {
            //Debug.Log("すり抜けた");
            GameObject.Find("Player").GetComponent<Rigidbody2D>().drag = 0;
            
        }
    }
}
