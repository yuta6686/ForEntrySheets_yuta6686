using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class TimeManager : MonoBehaviour
{
    [SerializeField]
    private TimeChange timeChange;

    [SerializeField]
    private int m_Time;

    private float seconds;

    private Goal goal;

    void Start()
    {
        timeChange.ShowTime(m_Time);

        // タグを付けないと機能しないので注意
        goal = GameObject.FindWithTag("Goal").GetComponent<Goal>();
    }

    void Update()
    {
        seconds += Time.deltaTime;

        if (seconds >= 1  && !goal.GetGoal())
        {
            seconds = 0;

            m_Time--;

            timeChange.ShowTime(m_Time);
        }

        if(m_Time < 0)
        {
            // ゲームオーバー
            SceneManager.LoadScene("GameOverScene");
        }
    }

    public int GetTime()
    {
        return m_Time;
    }
}
