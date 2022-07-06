using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Cinemachine;

public class Goal : MonoBehaviour
{
    
    [SerializeField] GameObject playerGoal;    
    [SerializeField] GameObject coin;
    [SerializeField] float awakeTime = 1.0f;
    [SerializeField] float oneCoinTime = 0.1f;
    [SerializeField] float animationTime = 1.0f;

    [Header("クリアシーンに遷移するか？")]
    [SerializeField]
    bool IsClear = false;

    [Header("クリアシーンに遷移しないときのシーン")]
    [SerializeField] SceneObject m_nextScene;

    private GameObject sceneControllerCam;
    private GameObject playerGoalInstance;
    //private GameObject CMvcam1;    
    private Rigidbody2D ridig2DPlayerGoal;    
    private Animator playerGoalAnimator;
    private float coinTime = 1.0f;
    
    private bool IsEnter2D = false;
    private bool IsCoin = false;
    private bool IsLeave = false;

    private bool isGoal = false;


    // Start is called before the first frame update
    void Start()
    {
        //  Get
        sceneControllerCam = Camera.main.gameObject;        
        //CMvcam1 = GameObject.Find("CM vcam1");

                
    }

    

    // Update is called once per frame
    void Update()
    {
        if (IsEnter2D)
        {
            IsCoinTrue();
        }

        if (IsCoin)
        {
            playerGoalInstance.GetComponent<Rigidbody2D>().AddForce(new Vector3(0, 50, 0));
            Invoke("startCoroutin", 1.0f);
            IsCoin = false;
        }
        
        
        if (IsLeave)
        {
            //  これはコイン処理が終わってからにしたい。
            //  「去る」アニメーションフラグ設定
            playerGoalAnimator.SetBool("IsLeave", true);
            
            coinTime = oneCoinTime  *  ScoreManager.scoreManagerInstance.GetCoinNum();                       

            //  アニメーション遷移時間＋コイン処理時間
            float totalTime = animationTime + coinTime;

           

            IsLeave = false;

            //  シーン遷移・
            Invoke("SetIsLeaveFalse", totalTime);
        }
    }
    

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.transform.name == "Player")
        {            

            IsEnter2D = true;

            //  プレイヤーをそのまま使うのは変更するのがだるいので
            //  新しいゴール用のプレイヤーを使う
            collision.gameObject.SetActive(false);            
            playerGoalInstance = Instantiate(playerGoal, collision.transform.position, Quaternion.identity);

            //  GetComponent
            ridig2DPlayerGoal = playerGoalInstance.GetComponent<Rigidbody2D>();
            //Camera.main.gameObject.GetComponent<Animator>().SetBool("IsGoal", true);
            playerGoalAnimator = playerGoalInstance.GetComponent<Animator>();

            //  Animator SetBool
            playerGoalAnimator.SetBool("IsEnter", true);

            //collision.GetComponent<SaveManager>().StageClear();
            //collision.GetComponent<SaveManager>().Save();

            // other            
            //CMvcam1.GetComponent<CinemachineVirtualCamera>().Follow = playerGoalInstance.transform;
            
            isGoal = true;
        }
    }

    //  コインの枚数分をoneCoinTime秒毎に投げる
    private IEnumerator CoinThrowCol()
    {
        //  コインの枚数取得
        int coinNum = ScoreManager.scoreManagerInstance.GetCoinNum();

        for (int i = 0; i < coinNum; i++)
        {
            GameObject coinInstance = Instantiate(coin, playerGoalInstance.transform.position, Quaternion.identity);

            //  コイン数-1
            ScoreManager.scoreManagerInstance.SubstractScore(1);
            
            //  oneCoinTime秒後に
            yield return new WaitForSeconds(oneCoinTime);
        }

        IsLeave = true;               
    }

    private void IsCoinTrue()
    {
        IsEnter2D = false;
        IsCoin = true;
    }

    private void startCoroutin()
    {
        StartCoroutine("CoinThrowCol");
    }
    private void SetIsLeaveFalse()
    {
        //  フラグ初期化
        playerGoalAnimator.SetBool("IsLeave", false);
        playerGoalAnimator.SetBool("IsGoal", false);

        if (IsClear)
        {
            sceneControllerCam.GetComponent<SceneController>().sceneChange("GameClearScene");
        }
        else
        {
            sceneControllerCam.GetComponent<SceneController>().sceneChange(m_nextScene);
        }

    }

    private void OnTriggerStay2D(Collider2D collision)
    {
        if (collision.transform.name == "Player")
        {
            IsEnter2D = false;
        }
    }

    public bool GetGoal()
    {
        return isGoal;
    }
}
