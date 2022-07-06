using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerBGManager : MonoBehaviour
{
    GameObject parallaxBG;
    ParallaxBackground pb;
    // Start is called before the first frame update
    void Start()
    {
        parallaxBG = GameObject.Find("Background");
        if (!parallaxBG)
            Debug.Log("ヒエラルキーに背景がありません。");
        if(parallaxBG)
            pb = parallaxBG.GetComponent<ParallaxBackground>();
    }

    // Update is called once per frame
    void Update()
    {
        if(pb != null)
            pb.StartScroll(transform.position);
    }
}
