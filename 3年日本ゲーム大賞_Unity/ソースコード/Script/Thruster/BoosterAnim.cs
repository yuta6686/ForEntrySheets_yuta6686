using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
/*==============================================================================
  BoosterAnim
														 Author :君島朝日
														 Date   :2022/03/10
--------------------------------------------------------------------------------
水噴射移動の処理をするスクリプト
==============================================================================*/
public class BoosterAnim : MonoBehaviour
{
    [SerializeField] private GameObject TestBoosterBullet = null; //発射されるものを格納

    private Vector2 move;

    PlayerActionInput input;

    void Start()
    {
        //InputSystemを有効化
        input = new PlayerActionInput();

        input.Enable();
    }

    void Update()
    {
        move = input.Player.Thruster.ReadValue<Vector2>();

        //右入力
        if (move.x > 0)
        {
            Instantiate(TestBoosterBullet, transform.position,transform.rotation);
        }
        //左入力
        else if (move.x < 0)
        {
            Instantiate(TestBoosterBullet, transform.position, transform.rotation);
        }

        //上入力
        if (move.y > 0)
        {
            Instantiate(TestBoosterBullet, transform.position, transform.rotation);
        }
        //下入力
        else if (move.y < 0)
        {
            Instantiate(TestBoosterBullet, transform.position, transform.rotation);
        }
    }
}
