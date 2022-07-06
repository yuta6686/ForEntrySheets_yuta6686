using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ToGameClearScene : MonoBehaviour
{
    GameObject sceneControllerCam;

    public void LoadGameClearScene()
    {        
        sceneControllerCam.GetComponent<SceneController>().sceneChange("GameClearScene");
    }

    // Start is called before the first frame update
    void Start()
    {
         sceneControllerCam = Camera.main.gameObject;
    }

    // Update is called once per frame
    void Update()
    {
        // [のこと
        if (Input.GetKeyDown(KeyCode.LeftBracket))
        {
            LoadGameClearScene();
        }
    }
}
