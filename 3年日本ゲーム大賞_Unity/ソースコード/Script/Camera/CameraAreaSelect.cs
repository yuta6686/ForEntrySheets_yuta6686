using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraAreaSelect : MonoBehaviour
{
    public GameObject player;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 playerPos = player.transform.position;
        //カメラとプレイヤーの位置を同じにする
        transform.position = new Vector3(playerPos.x, 0.0f, -10);
    }
}
