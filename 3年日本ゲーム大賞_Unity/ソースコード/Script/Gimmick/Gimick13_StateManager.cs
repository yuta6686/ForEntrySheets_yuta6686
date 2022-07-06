using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Gimick13_StateManager : MonoBehaviour
{
    // フロア内スイッチ数カウント保持
    protected uint _switchCount = 0;
    public uint SwitchCount
    {
        get { return _switchCount; }
        protected set { _switchCount = value; }
    }
    // プレイヤーステータス確保用変数
    //protected Player _State;

    // 踏む順番の番号照らし合わせ用変数
    //protected int _flowSwitchNo = 0;
    //public int FlowSwitchNo
    //{
    //    get { return _flowSwitchNo; }
    //}

    public GameObject particleObject;
    [SerializeField] GameObject  DestroyObject;      //　破壊するオブジェクト

    private bool DestroyCheck = false;              //trueになったらすでに破壊済み

    // Start is called before the first frame update
    protected virtual void Start()
    {
        // 初回時にカウントしておく
        _checkAreaSwitches();
        // プレイヤーステータスを取得
        //_State = GameObject.FindGameObjectsWithTag("State_Manager")[0].GetComponent<Player>();

    }

    // Update is called once per frame
    protected virtual void Update()
    {
        _checkSuccess();
       
    }

    // フロア内スイッチをカウント
    private uint _checkAreaSwitches()
    {
        foreach (Transform child in transform)
        {
            SwitchCount += 1;
        }

        return SwitchCount;
    }

    // 子からマイナンバーを送ってもらうための関数
    //public void sendMyNumber(uint myNumber)
    //{
    //    // 次に踏むナンバーとマイナンバーが同じであれば
    //    if (myNumber == _flowSwitchNo)
    //    {
    //        // 次に踏むナンバーをインクリメントする
    //        _flowSwitchNo++;
    //    }
    //    else
    //    {
    //        // 間違っていた場合はリセットする
    //        _flowSwitchNo = 0;
    //    }
    //}

    // 子からスイッチが入った時に送ってもらうための関数
    public void sendON()
    {
        
        if (_switchCount > 0)
        {
            _switchCount--;
        }
    }
    // 子からスイッチが戻った時に送ってもらうための関数
    public void sendOFF()
    {
        // 
        if (_switchCount > 0)
        {
            _switchCount++;
        }
    }

    // 正解チェック
    private void _checkSuccess()
    {
        if (_switchCount <= 0 && ! DestroyCheck)
        {
            //  パーティクル生成
            Instantiate(particleObject, DestroyObject.transform.position, Quaternion.identity);

            //  オブジェクト破壊
            Destroy(DestroyObject);

            //  破壊済みフラグオン
            DestroyCheck = true;

        }
    }

}
