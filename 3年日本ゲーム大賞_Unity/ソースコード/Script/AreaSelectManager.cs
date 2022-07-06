using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.InputSystem;


public class AreaSelectManager : MonoBehaviour
{

    Camera sceneCamera;
    GameObject selectObject;
    int objectNo = 0;
    GameObject currentObject;
    bool moveCam = false;

    AreaSelect input;

    private void Start()
    {
        sceneCamera = Camera.main;
        EventSystem.current.SetSelectedGameObject(GameObject.Find("ButtonArea01"));
        currentObject = GameObject.Find("ButtonArea01");

        input = new AreaSelect();
        input.Enable();
    }

    private void Update()
    {
        //カメラ移動
        selectObject = EventSystem.current.currentSelectedGameObject;

        if (currentObject == selectObject)
            moveCam = true;

        if (moveCam)
        {
            MoveCamera(sceneCamera.transform.position, selectObject.transform.position);
        }


        //決定ボタン
        if (Gamepad.current != null)
        {
            if (input.controller.Enterkey.triggered)
            {
                if (selectObject.name == "ButtonToTitle")
                    sceneCamera.gameObject.GetComponent<SceneController>().sceneChange("TitleScene_new");
                else
                {
                    Debug.Log(selectObject.name);
                    sceneCamera.gameObject.GetComponent<SceneController>().sceneChange("StageSelectScene" + selectObject.name.Remove(0, 10));
                }
            }
            //右
            if (input.controller.Right.triggered)
            {
                SwitchButton(false);
            }
            //左
            else if (input.controller.Left.triggered)
            {
                SwitchButton(true);
            }
        }
    }
    void SwitchButton(bool isLeft)
    {
        //右
        if (!isLeft)
        {
            objectNo++;
            if (objectNo >= 5)
                objectNo = 5;

            selectObject.GetComponent<SelectButton>().DeselectBehavior();

            GameObject obj = GameObject.Find("ButtonArea0" + objectNo);

            EventSystem.current.SetSelectedGameObject(obj);

            obj.GetComponent<SelectButton>().SelectBehavior();
        }
        else
        {
            objectNo--;
            if (objectNo <= 1)
                objectNo = 1;

            selectObject.GetComponent<SelectButton>().DeselectBehavior();

            GameObject obj = GameObject.Find("ButtonArea0" + objectNo);

            EventSystem.current.SetSelectedGameObject(obj);

            obj.GetComponent<SelectButton>().SelectBehavior();
        }
    }

    void MoveCamera(Vector3 pos1, Vector3 pos2)
    {

        //球面線形補間
        sceneCamera.transform.position = Vector3.Slerp(pos1, pos2, Time.deltaTime * 5.0f);
        sceneCamera.transform.position =
            new Vector3(sceneCamera.transform.position.x, sceneCamera.transform.position.y, -20.0f);
    }
}