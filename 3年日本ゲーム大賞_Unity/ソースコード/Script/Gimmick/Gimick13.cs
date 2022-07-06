using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Gimick13 : MonoBehaviour
{
    private SpriteRenderer spriteRenderer;            //    スプライト変えるため
   
    public Sprite buttonSprite; //スプライト
    public Sprite buttonSprite2; //スプライト

   
    private bool IsCollision = false;

    // 親に通知のため
    private Gimick13_StateManager _SwitchManager;

    // Start is called before the first frame update
    void Start()
    {
        spriteRenderer = GetComponent<SpriteRenderer>();

        // 親オブジェクトのスクリプトを取得
        _SwitchManager = transform.parent.gameObject.GetComponent<Gimick13_StateManager>();
    }

    // Update is called once per frame
    void Update()
    {

    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        //プレイヤーならスプライト切り替え
        if (collision.gameObject.CompareTag("Player"))
        {
            if(IsCollision)
            {
                spriteRenderer.sprite = buttonSprite2;
               
                IsCollision = false;

                //スイッチオフを親に通知
                _SwitchManager.sendOFF();

            }
            else
            {
                spriteRenderer.sprite = buttonSprite;

                IsCollision = true;

                //スイッチオンを親に通知
                _SwitchManager.sendON();
            }
           
        }
    }
}
