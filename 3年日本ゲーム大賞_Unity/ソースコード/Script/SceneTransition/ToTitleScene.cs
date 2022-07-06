using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ToTitleScene : MonoBehaviour
{
    GameObject sceneControllerCam;
    private void LoadTitleScene()
    {        
        sceneControllerCam.GetComponent<SceneController>().sceneChange("TitleScene_new");
    }

    // Start is called before the first frame update
    void Start()
    {
        sceneControllerCam = Camera.main.gameObject;
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Delete))
        {
            LoadTitleScene();
        }
    }
}
