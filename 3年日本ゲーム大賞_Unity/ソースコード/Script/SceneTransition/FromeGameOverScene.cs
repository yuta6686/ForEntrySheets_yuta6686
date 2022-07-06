using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class FromeGameClearScene : MonoBehaviour
{

    GameObject sceneControllerCam;

    bool IsOnce = false;

    // Start is called before the first frame update
    void Start()
    {
        sceneControllerCam = Camera.main.gameObject;

        IsOnce = false;

    }

    // Update is called once per frame
    void Update()
    {
        if (Input.anyKey && !IsOnce)
        {
            sceneControllerCam.GetComponent<SceneController>().sceneChange("TitleScene_new");
            IsOnce = true;
        }
    }
}
