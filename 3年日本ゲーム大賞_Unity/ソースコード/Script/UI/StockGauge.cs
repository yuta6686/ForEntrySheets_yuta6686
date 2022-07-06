using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class StockGauge : MonoBehaviour
{
    //　残機プレハブ
    [SerializeField]
    private GameObject stockObj;

    private bool useSwitch = false;

    private RawImage lastStock;

    private int animCnt = 0;

    public int AnimSpeed;

    public int AnimCooltime;

    void Update()
    {
        // 残機が一つ以上あるとき
        if(transform.childCount > 0)
        {
            animCnt++;
            if(animCnt > 8 * AnimSpeed + AnimCooltime)
            {
                animCnt = 0;
            }

            int useCnt;
            if(animCnt < 8 * AnimSpeed)
            {
                useCnt = animCnt / AnimSpeed;
            }
            else
            {
                useCnt = 0;
            }

            if (useSwitch)
            {
                if(animCnt < 8 * AnimSpeed)
                {
                    // アニメーションさせる処理
                    int UVx = useCnt % 4;
                    int UVy = useCnt / 4;

                    lastStock.uvRect = new Rect(UVx * 0.25f, UVy * 0.5f,
                        lastStock.uvRect.width, lastStock.uvRect.height);
                }
                else
                {
                    // クールタイム中
                    lastStock.uvRect = new Rect(0, 0.5f,
                        lastStock.uvRect.width, lastStock.uvRect.height);
                }

                
            }
            else
            {
                // lastStockに先頭の残機を格納
                lastStock = transform.GetChild(0).gameObject.GetComponent<RawImage>();

                useSwitch = true;
            }

        }
    }

    // 残機全削除＆残機分作成
    public void SetStockGauge(int life)
    {
        // 残機を一旦全削除
        for (int i = 0; i < transform.childCount; i++)
        {
            Destroy(transform.GetChild(i).gameObject);
        }
        // 現在の残機数分のライフゲージを作成
        for (int i = 0; i < life; i++)
        {
            Instantiate(stockObj, transform);
        }

        // 先頭のサイズ、アルファ値変更
        transform.GetChild(0).gameObject.GetComponent<RawImage>().color = new Color(255.0f, 255.0f, 255.0f, 190.0f);
        transform.GetChild(0).gameObject.GetComponent<RectTransform>().sizeDelta = new Vector2(110.0f, 110.0f);
    }
    //　ダメージ分だけ削除
    public void StockDamege(int damage)
    {
        // ストックが0より多いとき
        if (transform.childCount > 0)
        {
            for (int i = 0; i < damage; i++)
            {
                // 列の最後のライフゲージを削除
                Destroy(transform.GetChild(transform.childCount - 1 - i).gameObject);
            }
        }

    }
}