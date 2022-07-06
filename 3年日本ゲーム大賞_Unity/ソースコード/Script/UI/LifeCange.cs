using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LifeCange : MonoBehaviour
{
    SpriteRenderer Lifesprite;

    void Start()
    {
        Lifesprite = GetComponent<SpriteRenderer>();

        Lifesprite.color = new Color(1, 1, 1, 0);
    }

    public void Set(float showtime, float minusAlfa)
    {
        StartCoroutine(ShowLife(showtime,minusAlfa));
    }

    private IEnumerator ShowLife(float showtime, float minusAlfa)
    {
        Lifesprite.color = new Color(1, 1, 1, 1);

        yield return new WaitForSeconds(showtime);

        StartCoroutine("HideLife", minusAlfa);
        yield break;
    }

    private IEnumerator HideLife(float minusAlfa)
    {
        float alfa = 1.0f;

        while (true)
        {
            alfa -= minusAlfa;
            if (alfa < 0.0f)
                alfa = 0.0f;

            Lifesprite.color = new Color(1, 1, 1, alfa);

            if (alfa <= 0.0f)
            {
                yield break;
            }

            yield return new WaitForSeconds(0.05f);
        }

    }
}
