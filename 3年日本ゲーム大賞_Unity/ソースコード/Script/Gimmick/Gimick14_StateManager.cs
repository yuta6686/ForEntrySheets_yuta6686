using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Gimick14_StateManager : MonoBehaviour
{
    //消える・戻るまでの時間
    public float ActionInterval = 4;

    //時間を数える変数
    private float CountTime = 0;

    //ピッが鳴る間隔
    public float SEInterval = 0.5f;
    //ピッが鳴る回数
    public uint CountSEMAX = 3;
    private uint CountSE;

    //子のオブジェクト取得用
    [SerializeField]
    private GameObject ParentObject;
    private GameObject[] ChildObject;

    //SE関連
    public AudioClip sound1;
    public AudioClip sound2;
    AudioSource audioSource;

    // Start is called before the first frame update
    protected virtual void Start()
    {
        // 初回時にカウントしておく
        GetAllChildObject();

        //0以下だと目に良くなさそう
        if (ActionInterval <= 0)
        {
            ActionInterval = 1;
        }

        CountSE = CountSEMAX;

        audioSource = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    protected virtual void Update()
    {
        //秒数加算
        CountTime += Time.deltaTime;

        //目標の時間に届いたら
        if (CountTime >= ActionInterval)
        {
            //全ての子の表示と消滅を切り替える
            for (int i = 0; i < ChildObject.Length; i++)
            {
                ChildObject[i].GetComponent<Gimick14>().ChengeScale();
            }

            audioSource.PlayOneShot(sound1);
            CountTime = 0;
            CountSE = CountSEMAX;
        }

        //ピッを鳴らす
        if(CountTime >= ActionInterval - CountSE * SEInterval && CountSE > 0)
        {
            audioSource.PlayOneShot(sound2);
            CountSE--;
        }
    }

    //子をすべて取得する
    private void GetAllChildObject()
    {
        ChildObject = new GameObject[ParentObject.transform.childCount];

        for (int i = 0; i < ParentObject.transform.childCount; i++)
        {
            ChildObject[i] = ParentObject.transform.GetChild(i).gameObject;
        }
    }


}
