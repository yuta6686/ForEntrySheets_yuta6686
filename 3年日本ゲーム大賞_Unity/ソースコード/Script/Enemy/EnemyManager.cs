using UnityEngine;
using UnityEngine.SceneManagement;
using Spine.Unity;
using System.Collections;

public partial class EnemyManager : MonoBehaviour
{
    enum ENEMY_TYPE
    {
        Bee,
        Worm,
    }
    enum DIR
    {
        RIGHT,
        LEFT,
    }

    [SerializeField] ENEMY_TYPE enemyType;
    [Header("初期移動方向 (現状ハリネズミのみ)")]
    [SerializeField] DIR dir;
    [Header("")]
    [SerializeField] GameObject player;
    [SerializeField] GameObject explosion;
    new Rigidbody2D rigidbody2D;

    SkeletonAnimation skeletonAnimation;
    Spine.AnimationState enemyAnimeState;

    private bool isEnterScreen = false;

    private EnemyStateBase stateIdol;
    private EnemyStateBase stateHoming;
    private EnemyStateBase stateAttack;
    private EnemyStateBase stateWaiting;

    //ハチアニメーション名
    private string idolAnimationName = "taiki";
    private string moveAnimationName = "idou";
    private string attackAnimationName = "kougeki";

    EnemyStateBase currentState;

    private void Start()
    {
        rigidbody2D = GetComponent<Rigidbody2D>();

        switch(enemyType)
        {
            case ENEMY_TYPE.Bee:
                stateIdol = new BeeStateIdol();
                stateHoming = new BeeStateHoming();
                stateAttack = new BeeStateAttack();
                stateWaiting = new BeeStateWaiting();

                skeletonAnimation = GetComponent<SkeletonAnimation>();
                enemyAnimeState = skeletonAnimation.AnimationState;
                break;

            case ENEMY_TYPE.Worm:
                stateIdol = new WormStateIdol();
                stateAttack = new WormStateAttack();
                skeletonAnimation = GetComponent<SkeletonAnimation>();
                enemyAnimeState = skeletonAnimation.AnimationState;
                rigidbody2D.gravityScale = 0;
                break;
        }
        currentState = stateIdol;

        currentState.OnEnter(this);
    }
    private void Update()
    {
        currentState.OnUpdate(this);
    }

    //ステートを遷移させる関数
    private void StateTransition(EnemyStateBase nextState)
    {
        currentState.OnExit(this);
        nextState.OnEnter(this);
        currentState = nextState;
        //Debug.Log("遷移" + nextState);
    }

    private void StateTransition(EnemyStateBase nextState,float delayTime)
    {
        currentState = new EnemyStateNull();
        StartCoroutine(DelayMethod(delayTime, nextState));
    }

    private Spine.TrackEntry SetAnimation(string animationName)
    {
        return enemyAnimeState.SetAnimation(0, animationName, true);
    }

    IEnumerator DelayMethod(float delay, EnemyStateBase nextState)
    {
        yield return new WaitForSeconds(delay);

        StateTransition(nextState);
    }

    private void Destroy()
    {
        Destroy(this.gameObject);
        Instantiate(explosion, transform.position, new Quaternion());
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "Player")
        {
            currentState.OnCollision(this);
        }
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Player")
        {
            currentState.OnCollision(this);
        }
    }

    private void OnBecameVisible()
    {
        isEnterScreen = true;
    }

    private void OnBecameInvisible()
    {
        isEnterScreen = false;
    }
    void OncompleteHandler()
    {
        WormStateIdol.isRotate = false;
        //Debug.Log("isRotate  " + WormStateIdol.isRotate);

        iTween.Stop(gameObject);
    }

    public int GetEnemyState()
    {
        if (currentState == stateIdol)
        {
            return 0;
        }
        else if (currentState == stateAttack)
        {
            return 1;
        }
        else if (currentState == stateWaiting)
        {
            return 2;
        }
        else
        {
            return -1;
        }
    }
}
