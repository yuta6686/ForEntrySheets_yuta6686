using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TimeChange : MonoBehaviour
{
    [SerializeField]
    private RawImage TimeDigit_3; // ３桁目

    [SerializeField]
    private RawImage TimeDigit_2; // ２桁目

    [SerializeField]
    private RawImage TimeDigit_1; // １桁目

    public void ShowTime(int time)
    {
        int dig_3 = time / 100;      // 1桁目
        int dig_2 = time % 100 / 10; // 2桁目
        int dig_1 = time % 100 % 10; // 2桁目

        TimeDigit_1.uvRect = new Rect(dig_1 * 0.1f,
            TimeDigit_1.uvRect.y, TimeDigit_1.uvRect.width, TimeDigit_1.uvRect.height);

        TimeDigit_2.uvRect = new Rect(dig_2 * 0.1f,
            TimeDigit_2.uvRect.y, TimeDigit_2.uvRect.width, TimeDigit_2.uvRect.height);

        TimeDigit_3.uvRect = new Rect(dig_3 * 0.1f,
            TimeDigit_3.uvRect.y, TimeDigit_3.uvRect.width, TimeDigit_3.uvRect.height);
    }
}
