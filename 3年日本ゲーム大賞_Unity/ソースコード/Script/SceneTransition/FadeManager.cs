using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class FadeManager : MonoBehaviour
{
    public static bool isFadeInstance = false;

    public bool isFadeIn = false;
    public bool isFadeOut = false;

    public float alpha = 0.0f;
    private float fadeSpeed = 2.0f;

    public float xsize = 1920.0f;
    public float ysize = 1080.0f;

    public float rotation = 10.0f;

    Image image;

    [SerializeField]
    private float fadeEmissionAmount = 25;

    private void Awake()
    {
        if (!isFadeInstance)
        {
            DontDestroyOnLoad(this);
            isFadeInstance = true;
        }
        else
        {
            Destroy(this);
        }

      
    }

    // Start is called before the first frame update
    void Start()
    {
        image = this.GetComponentInChildren<Image>();

    }

    // Update is called once per frame
    void Update()
    {
        if (isFadeIn)
        {
            alpha -= Time.deltaTime / fadeSpeed;
            if (alpha <= 0.0f)//透明になったら、フェードインを終了
            {
                isFadeIn = false;
                alpha = 0.0f;
            }



            //image.color = new Color(0.0f, 0.0f, 0.0f, alpha);
            image.material.SetFloat("_Emission",alpha* fadeEmissionAmount);
            //image.transform.localScale = new Vector3(xsize * alpha, ysize * alpha, 1.0f);
            //image.transform.Rotate(new Vector3(0.0f, 0.0f, alpha * rotation));
        }
        else if (isFadeOut)
        {
            alpha += Time.deltaTime / fadeSpeed;
            if (alpha >= 1.0f)//真っ黒になったら、フェードアウトを終了
            {
                isFadeOut = false;
                alpha = 1.0f;
            }



            //image.color = new Color(0.0f, 0.0f, 0.0f, alpha);
            image.material.SetFloat("_Emission",alpha* fadeEmissionAmount);
            //image.transform.localScale = new Vector3(xsize * alpha, ysize * alpha, 1.0f);
            //image.transform.Rotate(new Vector3(0.0f, 0.0f, alpha * rotation));
        }

        
        //image.material.SetFloat("_Emission", alpha*2.0f);
        

        //image.rectTransform.sizeDelta = new Vector2(xsize*alpha, ysize*alpha);        
        //Debug.Log(alpha);
    }

    public void fadeIn()
    {
        isFadeIn = true;
        isFadeOut = false;
    }

    public void fadeOut()
    {
        isFadeIn = false;
        isFadeOut = true;

    }
}
