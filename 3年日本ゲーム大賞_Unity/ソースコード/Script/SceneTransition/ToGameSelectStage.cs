using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class ToGameSelectStage : MonoBehaviour
{
    GameObject sceneControllerCam;

    // ステージ選択ではマウスで選択


    public void ToTitleScene()
    {
        sceneControllerCam.GetComponent<SceneController>().sceneChange("TitleScene_new");
    }

    public void ToGameScene(string areaStage)
    {        
        sceneControllerCam.GetComponent<SceneController>().sceneChange("GameScene"+areaStage);
    }
    
    public void ToStageSelectScene(string zeroStage)
    {
        sceneControllerCam.GetComponent<SceneController>().sceneChange("StageSelectScene"+ zeroStage);
    }
    public void ToAreaSelectScene()
    {
        sceneControllerCam.GetComponent<SceneController>().sceneChange("AreaSelectScene");
    }
      


    // Start is called before the first frame update
    void Start()
    {
        sceneControllerCam = Camera.main.gameObject;
    }



    // Update is called once per frame
    void Update()
    {

    }
}
