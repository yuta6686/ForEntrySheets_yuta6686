using UnityEngine;
using System.Collections;
using System.Collections.Generic;

//毛虫　通常(移動)状態定義用partialスクリプト

public partial class EnemyManager
{

    public class WormStateIdol : EnemyStateBase
    {
        enum MOVE_DIR
        {
            RIGHT,
            LEFT,
            UP,
            DOWN,
        }

        int layerNo = LayerName.Ground;
        int turnLayer;

        MOVE_DIR dir = MOVE_DIR.RIGHT;

        int MOVE_SPEED = 5;
        int ATTACK_INTERVAL = 300;
        int atkCnt = 0;
        bool once = true;
        static public bool isRotate;

        public override void OnEnter(EnemyManager owner)
        {
            owner.SetAnimation(owner.moveAnimationName);

            if (owner.dir == DIR.RIGHT && once)
            {
                owner.transform.localScale = new Vector3(owner.transform.localScale.x * 1, 1, 1);
                dir = MOVE_DIR.RIGHT;
            }
            else if (owner.dir == DIR.LEFT && once)
            {
                owner.transform.localScale = new Vector3(owner.transform.localScale.x * -1, 1, 1);
                dir = MOVE_DIR.LEFT;
            }
            turnLayer = 1 << layerNo;
            once = false;
        }

        public override void OnUpdate(EnemyManager owner)
        {
            //移動
            Move(owner);

            //攻撃状態遷移
            atkCnt++;
            if (atkCnt >= ATTACK_INTERVAL)
            {
                owner.StateTransition(owner.stateAttack);
                atkCnt = 0;
            }
        }
        public override void OnCollision(EnemyManager owner)
        {
            owner.Destroy();
        }

        private void Move(EnemyManager owner)
        {
            RaycastHit2D hit;

            if (!isRotate)
            {
                //前方に地面がなかったら
                if (!IsGround(owner))
                {
                    SwitchDir(owner);
                }

                //前方が壁だったら
                if (hit = IsWall(owner))
                {
                    switch (dir)
                    {
                        case MOVE_DIR.RIGHT:
                            if (owner.transform.localScale.x <= 0)
                            {
                                FollowWall(owner, hit, false);
                                dir = MOVE_DIR.DOWN;
                            }
                            else if (owner.transform.localScale.x >= 0)
                            {
                                FollowWall(owner, hit, true);
                                dir = MOVE_DIR.UP;
                            }
                            break;
                        case MOVE_DIR.LEFT:
                            if (owner.transform.localScale.x <= 0)
                            {
                                FollowWall(owner, hit, false);
                                dir = MOVE_DIR.UP;
                            }
                            else if (owner.transform.localScale.x >= 0)
                            {
                                FollowWall(owner, hit, true);
                                dir = MOVE_DIR.DOWN;
                            }
                            break;
                        case MOVE_DIR.UP:
                            if (owner.transform.localScale.x <= 0)
                            {
                                FollowWall(owner, hit, false);
                                dir = MOVE_DIR.RIGHT;
                            }
                            else if (owner.transform.localScale.x >= 0)
                            {
                                FollowWall(owner, hit, true);
                                dir = MOVE_DIR.LEFT;
                            }
                            break;
                        case MOVE_DIR.DOWN:
                            if (owner.transform.localScale.x <= 0)
                            {
                                FollowWall(owner, hit, false);
                                dir = MOVE_DIR.LEFT;

                            }
                            else if (owner.transform.localScale.x >= 0)
                            {
                                FollowWall(owner, hit, true);
                                dir = MOVE_DIR.RIGHT;
                            }
                            break;
                    }
                }
            }

            //移動
            switch (dir)
            {
                case MOVE_DIR.RIGHT:
                    owner.rigidbody2D.velocity = new Vector2(MOVE_SPEED, 0);
                    break;

                case MOVE_DIR.LEFT:
                    owner.rigidbody2D.velocity = new Vector2(-MOVE_SPEED, 0);
                    break;

                case MOVE_DIR.UP:
                    owner.rigidbody2D.velocity = new Vector2(0, MOVE_SPEED);
                    break;

                case MOVE_DIR.DOWN:
                    owner.rigidbody2D.velocity = new Vector2(0, -MOVE_SPEED);
                    break;
            }
        }

        //足元に地面があればtrue
        bool IsGround(EnemyManager owner)
        {
            Vector3 startPoint = owner.transform.position + owner.transform.right * 0.8f * owner.transform.localScale.x;
            Vector3 endPoint = startPoint - owner.transform.up * 0.5f;

            //Debug.DrawLine(startPoint, endPoint);
            return Physics2D.Linecast(startPoint, endPoint, turnLayer);
        }

        //目の前に壁があればtrue
        RaycastHit2D IsWall(EnemyManager owner)
        {
            Vector3 startPoint = owner.transform.position + owner.transform.right * owner.transform.localScale.x + owner.transform.up * 0.5f;
            Vector3 endPoint = startPoint + owner.transform.right* 1.5f  * owner.transform.localScale.x;

            Debug.DrawLine(startPoint, endPoint);
            return Physics2D.Linecast(startPoint, endPoint, turnLayer);
        }

        void SwitchDir(EnemyManager owner)
        {
            if (dir == MOVE_DIR.RIGHT)
            {
                dir = MOVE_DIR.LEFT;
                owner.transform.localScale = new Vector3(owner.transform.localScale.x * -1, 1, 1);
            }
            else if (dir == MOVE_DIR.LEFT)
            {
                dir = MOVE_DIR.RIGHT;
                owner.transform.localScale = new Vector3(owner.transform.localScale.x * -1, 1, 1);
            }

            if (dir == MOVE_DIR.UP)
            {
                dir = MOVE_DIR.DOWN;
                owner.transform.localScale = new Vector3(owner.transform.localScale.x * -1, 1, 1);
            }
            else if (dir == MOVE_DIR.DOWN)
            {
                dir = MOVE_DIR.UP;
                owner.transform.localScale = new Vector3(owner.transform.localScale.x * -1, 1, 1);
            }
        }

        //壁にくっつく
        void FollowWall(EnemyManager owner, RaycastHit2D hit, bool isRightWall)
        {
            //位置調整
            switch (dir)
            {
                case MOVE_DIR.RIGHT:
                    PositionAdjust(owner, GetNearBlock(hit));
                    break;

                case MOVE_DIR.LEFT:
                    PositionAdjust(owner, GetNearBlock(hit));
                    break;

                case MOVE_DIR.UP:
                    PositionAdjust(owner, GetNearBlock(hit));
                    break;

                case MOVE_DIR.DOWN:
                    PositionAdjust(owner, GetNearBlock(hit));
                    break;
            }
        }

        //位置の補正
        void PositionAdjust(EnemyManager owner, GameObject nearBlock)
        {
            float xPos = 0, yPos = 0;
            float rotate = 90;

            if (owner.transform.localScale.x <= 0)
                rotate = -90;
            else
                rotate = 90;
            
            switch (dir)
            {
                //右壁にくっつく
                case MOVE_DIR.RIGHT:
                    xPos = nearBlock.transform.position.x - nearBlock.transform.localScale.x / 2 - 0.005f;
                        /*hit.transform.position.x - hit.transform.localScale.x / 2 - 0.005f;*/
                        //Debug.Log(xPos + "Xpos DirRight");

                    MoveTo(owner, new Vector2(xPos, nearBlock.transform.position.y));
                    iTween.RotateAdd(owner.gameObject, iTween.Hash("z", rotate, "time", 0.5f));
                    break;

                //左壁にくっつく
                case MOVE_DIR.LEFT:
                    xPos = nearBlock.transform.position.x + nearBlock.transform.localScale.x / 2 + 0.005f;
                    //Debug.Log(xPos + "Xpos  DirLeft");

                    iTween.RotateAdd(owner.gameObject, iTween.Hash("z", rotate, "time", 0.5f));
                    MoveTo(owner, new Vector2(xPos, nearBlock.transform.position.y));
                    break;

                //天井にくっつく
                case MOVE_DIR.UP:
                    yPos = nearBlock.transform.position.y - nearBlock.transform.localScale.y / 2 - 0.005f;
                    //Debug.Log(yPos + "Ypos DirUp");

                    iTween.RotateAdd(owner.gameObject, iTween.Hash("z", rotate, "time", 0.5f));
                    MoveTo(owner, new Vector2(nearBlock.transform.position.x, yPos));
                    break;

                //地面にくっつく
                case MOVE_DIR.DOWN:
                    yPos = nearBlock.transform.position.y + nearBlock.transform.localScale.y / 2 - 0.005f;

                    iTween.RotateAdd(owner.gameObject, iTween.Hash("z", rotate, "time", 0.5f));
                    MoveTo(owner, new Vector2(nearBlock.transform.position.x, yPos));
                    break;
            }
        }

        void MoveTo(EnemyManager owner, Vector2 To)
        {
            iTween.MoveTo(owner.gameObject, iTween.Hash("x", To.x, "y", To.y, "time", 0.5f,
                "oncomplete", "OncompleteHandler", "oncompletetarget", owner.gameObject));
            isRotate = true;
        }

        GameObject GetNearBlock(RaycastHit2D hit)
        {
            float tmpDis = 0;           //距離用一時変数
            float nearDis = 0;          //最も近いオブジェクトの距離
            int objNo = 0;

            //タグ指定されたオブジェクトを配列で取得する
            for (int i = 0; i < hit.transform.childCount; i++)
            {
                //自身と取得したオブジェクトの距離を取得
                tmpDis = Vector3.Distance(hit.transform.GetChild(i).gameObject.transform.position, hit.point);

                //オブジェクトの距離が近いか、距離0であればオブジェクト名を取得
                //一時変数に距離を格納
                if (nearDis == 0 || nearDis > tmpDis)
                {
                    nearDis = tmpDis;
                    objNo = i;
                }
            }
            //一番近いオブジェクトを返す
            return hit.transform.GetChild(objNo).gameObject;
        }
    }
}
