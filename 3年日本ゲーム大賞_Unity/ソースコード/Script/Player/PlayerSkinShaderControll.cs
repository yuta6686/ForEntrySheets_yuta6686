using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//  製作者：柳澤優太
//  プレイヤーの速度に応じたシェーダグラフの値設定

public class PlayerSkinShaderControll : MonoBehaviour
{
    Rigidbody2D rigidbody2D;
    SpriteRenderer renderer;
    float movementSpeed;
    Color movementColor;

    public float nomalizeValue = 20.0f;
    public float minValue = 0.5f;

    

    private void Start()
    {
        rigidbody2D = GetComponent<Rigidbody2D>();
        renderer = GetComponent<SpriteRenderer>();

        movementColor.r = 1.0f;
        movementColor.g = 1.0f;
        movementColor.b = 1.0f;
        movementColor.a = 1.0f;
    }

    void Update()
    {
        movementSpeed = rigidbody2D.velocity.magnitude;

        movementSpeed = movementSpeed / nomalizeValue + minValue;

        //movementColor.g = movementColor.b = 255 - movementSpeed * 2.0f;         


        renderer.material.SetFloat("_Emission", movementSpeed);

        renderer.material.SetColor("_Color", movementColor);

        //Debug.Log(movementSpeed);
    }

    void ChangeRedColor(byte rColor)
    {
        renderer.color = new Color32(255, (byte)(255 - rColor), (byte)(255 - rColor), 255);
    }
}
