using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class HPwarehouse : MonoBehaviour
{
    public static int h_PlayerHP = 0;
    
    void Update()
    {
        // ステージセレクト、ゲームオーバーシーンになったら
        if(SceneManager.GetActiveScene().name == "StageSelectScene" ||
            SceneManager.GetActiveScene().name == "GameOverScene")
        {
            h_PlayerHP = 0;
        }

    }
}
