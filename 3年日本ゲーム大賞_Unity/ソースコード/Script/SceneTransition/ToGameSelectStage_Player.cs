using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ToGameSelectStage_Player : MonoBehaviour
{
    GameObject sceneControllerCam;

    static public bool IsGameStart = false;
    static public bool IsExit = false;

    private float yMove = 0.0f;
    private float sinValue = 0.0f;        

    public float waveSpeed = 0.01f;
    public float waveHeight = 200.0f;

    // Start is called before the first frame update
    void Start()
    {
        sceneControllerCam = Camera.main.gameObject;
    }

    // Update is called once per frame
    void Update()
    {
        

       
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.transform.name == "GameStart")
        {
            IsGameStart = true;
            //Invoke("ChangeStageSelectScene", 3);
            
        }

        if (collision.transform.name == "Exit")
        {
            IsExit = true;
            //Invoke("Quit", 3);
        }
    }






    void Quit()
    {
#if UNITY_EDITOR
        UnityEditor.EditorApplication.isPlaying = false;
#elif UNITY_STANDALONE
      UnityEngine.Application.Quit();
#endif
    }
}
