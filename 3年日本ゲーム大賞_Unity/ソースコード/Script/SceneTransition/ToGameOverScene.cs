using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ToGameOverScene : MonoBehaviour
{
    GameObject sceneControllerCam;

    private void LoadGameOverScene()
    {
        
        sceneControllerCam.GetComponent<SceneController>().sceneChange("GameOverScene");
    }

    // Start is called before the first frame update
    void Start()
    {
        sceneControllerCam = Camera.main.gameObject;
    }

    // Update is called once per frame
    void Update()
    {
        // ]のこと
        if (Input.GetKeyDown(KeyCode.RightBracket))
        {
            LoadGameOverScene();    
        }
    }
}
