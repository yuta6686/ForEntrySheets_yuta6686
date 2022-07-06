using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

//  GameStartオブジェクトのスクリプト操作
//  Author :柳澤優太

public class ToGameStart : MonoBehaviour
{
    GameObject sceneControllerCam;
    GameObject player;
    
    [SerializeField] float TransitionTime = 2.0f;
    [SerializeField] float xPos = -2.0f;
    [SerializeField] float EmissionNormalize = 3.0f;

    private Animator animator;
    private MeshRenderer renderer;
    private SpriteRenderer childRenderer;
    private float FirstEmission;

    // Start is called before the first frame update
    void Start()
    {
        sceneControllerCam = Camera.main.gameObject;
        player = GameObject.Find("Player");
        animator = GetComponent<Animator>();
        renderer = GetComponent<MeshRenderer>();
        childRenderer = GetComponentInChildren<SpriteRenderer>();
        FirstEmission = renderer.material.GetFloat("_Emission");
    }

    // Update is called once per frame
    void Update()
    {
        //  アニメーション・シェーダの制御
        GameStartRange();
    }

    //  少し左に動いたら、GameStartのスケールを大きくするアニメーションなどの制御
    private void GameStartRange()
    {
        float diff = Mathf.Abs(player.transform.position.x + xPos) / EmissionNormalize;


        if (player.transform.position.x < xPos)
        {

            renderer.material.SetFloat("_Emission", diff);
            renderer.material.SetFloat("_BlinkMinAlphaValue", 0.75f);
            childRenderer.material.SetFloat("_Emission", diff);
            childRenderer.material.SetFloat("_BlinkMinAlphaValue", 0.75f);

            animator.SetBool("blScaleStart", true);
        }
        else
        {           
            renderer.material.SetFloat("_Emission", FirstEmission);
            renderer.material.SetFloat("_BlinkMinAlphaValue", 0.25f);
            childRenderer.material.SetFloat("_Emission", FirstEmission);
            childRenderer.material.SetFloat("_BlinkMinAlphaValue", 0.25f);

            animator.SetBool("blScaleStart", false);
        }
    }

    //  衝突から数秒後シーン遷移
    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.transform.tag == "Player")
        {
            animator.SetBool("blMoveStart", true);
            Invoke("ChangeStageSelectScene", TransitionTime);
        }
    }
    private void OnCollisionStay2D(Collision2D collision)
    {
        Invoke("AnimatorSetBoolFalse", 1.0f);
    }

    void AnimatorSetBoolFalse()
    {
        animator.SetBool("blMoveStart", false);
    }


    void ChangeStageSelectScene()
    {
        sceneControllerCam.GetComponent<SceneController>().sceneChange("AreaSelectScene");
        //SceneManager.LoadScene("AreaSelectScene");
    }
}
