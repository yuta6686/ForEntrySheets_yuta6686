using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraZoom : MonoBehaviour
{
    Transform tf; //Main CameraのTransform
    Camera cam; //Main CameraのCamera

    public float zoomspeed;

    void Start()
    {
        tf = this.gameObject.GetComponent<Transform>(); //Main CameraのTransformを取得する。
        cam = this.gameObject.GetComponent<Camera>(); //Main CameraのCameraを取得する。
    }

    void Update()
    {
        if (Input.GetKey(KeyCode.Q)) //Qキーが押されていれば
        {
            cam.orthographicSize = cam.orthographicSize - zoomspeed; //ズームイン。
        }
        else if (Input.GetKey(KeyCode.E)) //Eキーが押されていれば
        {
            cam.orthographicSize = cam.orthographicSize + zoomspeed; //ズームアウト。
        }

        //if (Input.GetKey(KeyCode.UpArrow)) //上キーが押されていれば
        //{
        //    tf.position = tf.position + new Vector3(0.0f, 1.0f, 0.0f); //カメラを上へ移動。
        //}
        //else if (Input.GetKey(KeyCode.DownArrow)) //下キーが押されていれば
        //{
        //    tf.position = tf.position + new Vector3(0.0f, -1.0f, 0.0f); //カメラを下へ移動。
        //}
        //if (Input.GetKey(KeyCode.LeftArrow)) //左キーが押されていれば
        //{
        //    tf.position = tf.position + new Vector3(-1.0f, 0.0f, 0.0f); //カメラを左へ移動。
        //}
        //else if (Input.GetKey(KeyCode.RightArrow)) //右キーが押されていれば
        //{
        //    tf.position = tf.position + new Vector3(1.0f, 0.0f, 0.0f); //カメラを右へ移動。
        //}
    }
}