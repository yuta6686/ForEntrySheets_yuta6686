using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScoreManager : MonoBehaviour
{
    [SerializeField]
    private ScoreChange ScoreChange;

    // 現在のスコア
    private int m_Score;
    public static ScoreManager scoreManagerInstance;

    private void Awake()
    {
        if (scoreManagerInstance == null)
        {
            scoreManagerInstance = this;
        }

        m_Score = 0;

        ScoreChange.ShowScore(m_Score);
    }

    void Start()
    {

    }

    public void AddScore(int score)
    {
        m_Score += score;

        ScoreChange.ShowScore(m_Score);
    }

    public void SubstractScore(int score)
    {
        m_Score -= score;

        ScoreChange.ShowScore(m_Score);
    }

    public int GetCoinNum()
    {
        return m_Score;
    }
}
