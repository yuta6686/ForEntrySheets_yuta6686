using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class PlayerBoundManager : MonoBehaviour
{
    [SerializeField] float sideBoundCor; //横バウンド時Y+方向補正値
    BlockVariable blockVariable;
    new Rigidbody2D rigidbody2D;

    float boundPower;
    bool isBound;   //何回もバウンドされるバグ修正用
    int boundCnt;
    const int BOUND_CNT_MAX = 10;

    GameObject[] groundObj = null;

    GameObject nearobj = null;


    private void Start()
    {
        rigidbody2D = GetComponent<Rigidbody2D>();

        //タイルマップの子オブジェクト取得
        groundObj = GetChildrens(GameObject.Find("Tilemap"));
    }

    private void Update()
    {
        //Debug.Log(rigidbody2D.velocity.x);

        if(isBound)
        {
            boundCnt++;
        }
    }

    private void OnCollisionStay2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Bound")
        {

            //衝突位置取得

            if (CheckBoundObject(collision))
            {
                if (!isBound)
                {
                    GroundBound(collision);
                }
            }

        }
    }

    private void OnCollisionExit2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Bound")
        {
            if (isBound)
            {
                isBound = false;
            }
        }
        
    }

    //バウンドする関数
    void GroundBound(Collision2D collision)
    {
        //バウンドパワーをスクリプタブルオブジェクトから代入
        boundPower = blockVariable.boundPower;

        //Debug.Log(collsion.contacts[0].normal);

        //上方向に跳ねるとき前フレームの力を加算していく
        float boundAddition = Mathf.Abs(rigidbody2D.velocity.y * 0.5f);

        //上方向
        if (collision.contacts[0].normal == Vector2.up)
        {
            rigidbody2D.velocity = new Vector2(rigidbody2D.velocity.x, boundPower + boundAddition);
        }  
        //下方向
        else if (collision.contacts[0].normal == Vector2.down)
        {
            rigidbody2D.velocity = new Vector2(rigidbody2D.velocity.x, -boundPower * 0.5f);
        }

        //横方向
        if (collision.contacts[0].normal == Vector2.right)
        {
            float velY = rigidbody2D.velocity.y * 0.5f;

            if (velY <= 0)
                velY = 0;

            //左方向
            //Debug.Log("hidari");
            rigidbody2D.velocity = new Vector2(boundPower, velY + sideBoundCor);

        }
        else if (collision.contacts[0].normal == Vector2.left)
        {
            float velY = rigidbody2D.velocity.y * 0.5f;

            if (velY <= 0)
                velY = 0;
            //右方向
            // Debug.Log("migi");
            rigidbody2D.velocity = new Vector2(-boundPower, velY + sideBoundCor);
        }

        boundCnt = 0;
        isBound = true;
    }


    bool CheckBoundObject(Collision2D collision)
    {
        if (collision.gameObject.name != "Tilemap")
        {
            //衝突がタイルマップじゃなかったら衝突オブジェクトでリソースを探す
            blockVariable = Resources.Load<BlockVariable>(collision.gameObject.name);
            if (blockVariable == null)
            {
                Debug.LogError("プレハブの名前とBoundPowerの名前を一致させてください");
            }
        }
        else
        {
            //タイルマップだったら1番近いオブジェクトでリソースを探す
            GetNearObject(collision.contacts[0].point);
            //跳ねないオブジェクト
            if (nearobj.tag == "GroundNotBound")
            {
                if (boundCnt >= BOUND_CNT_MAX)
                {
                    boundCnt = 0;
                    isBound = false;
                }
                //跳ねないオブジェクトに横方向で当たったら
                if (collision.contacts[0].normal == Vector2.right)
                {
                    //右方向
                    //Debug.Log("migi");
                    rigidbody2D.velocity = new Vector2(5, rigidbody2D.velocity.y);
                }
                else if (collision.contacts[0].normal == Vector2.left)
                {
                    //左方向
                    //Debug.Log("hidari");
                    rigidbody2D.velocity = new Vector2(-5, rigidbody2D.velocity.y);
                }
                

                return false;
            }

            //タグでスクリプタブルオブジェクト取得
            blockVariable = Resources.Load<BlockVariable>(nearobj.tag);
            if (blockVariable == null)
            {
                Debug.LogError("タグの名前とBoundPowerの名前を一致させてください");
            }
        }

        return true;
    }

    void GetNearObject(Vector3 pos)
    {
        float tmpDis = 0;           //距離用一時変数
        float nearDis = 0;          //最も近いオブジェクトの距離

        //タグ指定されたオブジェクトを配列で取得する
        foreach (GameObject obs in groundObj)
        {
            //自身と取得したオブジェクトの距離を取得
            tmpDis = Vector3.Distance(obs.transform.position, pos);

            if (obs.tag != "GroundNotBound")
            {
                tmpDis -= 0.1f;
            }

            //オブジェクトの距離が近いか、距離0であればオブジェクト名を取得
            //一時変数に距離を格納
            if (nearDis == 0 || nearDis > tmpDis)
            {
                nearDis = tmpDis;
                nearobj = obs;
            }
        }
    }

    GameObject[] GetChildrens(GameObject parent)
    {
        //返す配列作成
        GameObject[] childrens = new GameObject[parent.transform.childCount];
        //子オブジェクト分のループ
        for (int i = 0; i < childrens.Length; i++)
        {
            childrens[i] = parent.transform.GetChild(i).gameObject;
        }

        return childrens;
    }
}