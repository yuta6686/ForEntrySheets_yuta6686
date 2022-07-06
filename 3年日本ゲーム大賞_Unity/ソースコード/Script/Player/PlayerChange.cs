using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/*---------------------------------------------------------------------------------------------------------
 *  「ボールチェンジ実装」 PlayerChange
 *                                                                          Author:柳澤優太
 *                                                                          2022/3/24 (木)
 ---------------------------------------------------------------------------------------------------------*/

public class PlayerChange : MonoBehaviour
{
    /* public */
    
    private PlayerJumpController playerJumpController;//    PlayerJumpControllerから、BoundForceを貰うため
    private SpriteRenderer spriteRenderer;            //    スプライト変えるため
    

    /* List */
    private List<Sprite>    l_Sprites;
    private List<float>     l_BoundForce;

    /* public */
    public Sprite sprite_00;
    public Sprite sprite_01;
    public Sprite sprite_02;
    public Sprite sprite_03;

    //  Playerの状態
    public int playerState;
   

    private enum BOUND_FORCE
    {
        BOUND_FORCE_NOMAL,
        BOUND_FORCE_FAST,
        BOUND_FORCE_VERYFAST,
        BOUND_FORCE_SLOW,
        BOUND_FORCE_MAX,
    }

      

    // Start is called before the first frame update
    void Start()
    {
        /* Get Component */
        playerJumpController = GetComponent<PlayerJumpController>();
        spriteRenderer = GetComponent<SpriteRenderer>();

        //  playerStateによって、スプライトが変わるようにするための配列
        l_Sprites = new List<Sprite> { sprite_00, sprite_01, sprite_02, sprite_03 };

        //  力をセット
        l_BoundForce = new List<float> {600.0f,1200.0f,1800.0f,300.0f, };       
        
        //  初手ノーマル
        playerState = ((int)BOUND_FORCE.BOUND_FORCE_NOMAL);
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.R))
        {          
            //  playerStateの上限処理
            if (playerState >= ((int)BOUND_FORCE.BOUND_FORCE_MAX)-1)
            {
                playerState = 0;
            }
            else
            {
                playerState++;
            }


            //  PlayerJumpControllerのBoundForceとjumpForceを書き換える
            playerJumpController.jumpForce = (float)l_BoundForce[playerState]/2;
            playerJumpController.BoundForce = (float)l_BoundForce[playerState] / 2;

            //  スプライト（画像（テクスチャ））差し替え
            spriteRenderer.sprite = l_Sprites[playerState];
        }
    }
}
