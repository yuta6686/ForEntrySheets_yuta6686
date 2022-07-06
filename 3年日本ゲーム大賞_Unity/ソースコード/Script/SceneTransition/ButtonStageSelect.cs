using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ButtonStageSelect : MonoBehaviour
{
    private Button[] buttons;

    // Start is called before the first frame update
    void Start()
    {
        buttons = GetComponentsInChildren<Button>();
        /* length = buttons.Length;*/

        buttons[0].Select();
    }

    //  以下残骸。

    /*private int length;

    [SerializeField] int horizontal = 3;
    [SerializeField] int virtical = 2;

    private int curNum = 0;*/

    // Update is called once per frame

   /* void Update()
    {*/

     // ☆無駄になった☆    Unity 最強！Unity しか勝たん！ふざけんな。

      /*  //  調整
        if (curNum < 0) curNum += length;
        if (curNum >= length) curNum -= length;

        //  curNumの選択
        buttons[curNum].Select();*/

    /*}*/

   /* private void KeyBoardInput()
    {
        //  キーボードで、押されたキーに応じてcurNumが変更される。
        if (Input.GetKeyDown(KeyCode.D) ||
            Input.GetKeyDown(KeyCode.RightArrow))
        {
            curNum++;
        }
        if (Input.GetKeyDown(KeyCode.A) ||
            Input.GetKeyDown(KeyCode.LeftArrow))
        {
            curNum--;
        }
        if (Input.GetKeyDown(KeyCode.W) ||
            Input.GetKeyDown(KeyCode.UpArrow))
        {
            curNum -= horizontal;
        }
        if (Input.GetKeyDown(KeyCode.S) ||
            Input.GetKeyDown(KeyCode.DownArrow))
        {
            curNum += horizontal;
        }
    }*/
}
