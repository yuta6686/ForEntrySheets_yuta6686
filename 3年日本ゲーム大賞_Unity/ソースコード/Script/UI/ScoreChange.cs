using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoreChange : MonoBehaviour
{
    [SerializeField]
    private RawImage ScoreDigit_2; // ２桁目

    [SerializeField]
    private RawImage ScoreDigit_1; // １桁目


    public void ShowScore(int score)
    {
        int dig_1 = score % 10; // 1桁目
        int dig_2 = score / 10; // 2桁目

        ScoreDigit_1.uvRect = new Rect(dig_1 * 0.1f,
            ScoreDigit_1.uvRect.y, ScoreDigit_1.uvRect.width, ScoreDigit_1.uvRect.height);

        ScoreDigit_2.uvRect = new Rect(dig_2 * 0.1f,
            ScoreDigit_2.uvRect.y, ScoreDigit_2.uvRect.width, ScoreDigit_2.uvRect.height);
    }
}
