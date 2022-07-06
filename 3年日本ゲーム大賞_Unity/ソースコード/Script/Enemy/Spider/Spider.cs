using Spine.Unity;
using UnityEngine;

public class Spider : MonoBehaviour
{
    public  GameObject              player;
    public  GameObject              explosion;
    public  GameObject              spiderNetParent;
    public  StateContext<Spider>    m_StateContext      { get; private set; }
    public  Spine.AnimationState    enemyAnimeState     { get; private set; }
    private SkeletonAnimation       skeletonAnimation;
    public string                   IDOL_ANIMATION      { get; private set; }  = "taiki";
    public string                   MOVE_ANIMATION      { get; private set; }  = "idou";
    public string                   ATTACK_ANIMATION    { get; private set; }  = "kougeki";

    public  Vector3                 initialPosition { get; private set; }
    public  Vector3                 previousPosition { get; private set; }
    [SerializeField] 
    private float                   movementSpeed   = 0.25f;
    public  float                   Speed
    {
                get { return movementSpeed; }
        private set {                       }
    }
    [SerializeField]
    private float                   attackInterval  = 2f;
    public  float                   getAttackInterval
    {
                get { return attackInterval; }
    }
    
    float lapseTime     = 0;
    public bool isAttackable { private set; get; } = true;
    [HideInInspector]
    public bool onNet { private set; get; } = true;
    public bool isRight { private set; get; } = true;

    public bool isCollideWithPlayer { private set; get; } = false;
    public Vector2 netRangeMax { private set; get; } = Vector2.zero;
    public Vector2 netRangeMin { private set; get; } = Vector2.zero;
    Rigidbody2D rb;

    private void Awake()
    {
        netRangeMin = netRangeMax = spiderNetParent.transform.GetChild(0).transform.position;
    }

    // Start is called before the first frame update
    void Start()
    {
        initialPosition = transform.position;
        m_StateContext                = new StateContext<Spider>(this);
        m_StateContext.m_CurrentState = new Sleep_SpiderColonel();
        m_StateContext.m_CurrentState.Initialize(this);

        Transform children = spiderNetParent.GetComponentInChildren<Transform>();
        if (children.childCount != 0)
            foreach (Transform nets in children)
            {
                if (netRangeMax.x < nets.transform.position.x)
                    netRangeMax = new Vector2(nets.transform.position.x, netRangeMax.y);
                if (netRangeMax.y < nets.transform.position.y)
                    netRangeMax = new Vector2(netRangeMax.x, nets.transform.position.y);
                if (netRangeMin.x > nets.transform.position.x)
                    netRangeMin = new Vector2(nets.transform.position.x, netRangeMin.y);
                if (netRangeMin.y > nets.transform.position.y)
                    netRangeMin = new Vector2(netRangeMin.x, nets.transform.position.y);
            }
        rb = transform.GetComponent<Rigidbody2D>();

        
        skeletonAnimation   = GetComponent<SkeletonAnimation>();
        enemyAnimeState     = skeletonAnimation.AnimationState;
    }

    private void OnCollisionEnter(Collision collision)
    {
        if(collision.gameObject.name == "Player")
        {
            isCollideWithPlayer = true;
        }
    }

    private void OnCollisionExit2D(Collision2D collision)
    {
        if (collision.gameObject.name == "Player")
        {
            isCollideWithPlayer = false;
        }
    }
    // Update is called once per frame
    void Update()
    {
        if (!isAttackable)
        {
            lapseTime += Time.deltaTime;
        }
        if(lapseTime >= attackInterval)
        {
            isAttackable = true;
            lapseTime = 0;
        }

        m_StateContext.Update();
        //Debug.Log(collisionCount);
        if (spiderNetParent.transform.childCount == 0)
        {
            Destroy();
        }
        if(!IsOnNet(transform.position))
        {
            Destroy();
        }
        if(transform.position.x - player.transform.position.x > 0)
        {
            transform.localScale = new Vector3(Mathf.Abs(transform.localScale.x), transform.localScale.y, transform.localScale.z);
        }
        else if (transform.position.x - player.transform.position.x < 0)
        {
            transform.localScale = new Vector3(-Mathf.Abs(transform.localScale.x), transform.localScale.y, transform.localScale.z);
        }
    }

    public bool IsContact(GameObject a, GameObject b)
    {
        var boxColliderA = a.GetComponent<BoxCollider2D>();
        var boxColliderB = b.GetComponent<BoxCollider2D>();

        if(boxColliderA.bounds.Intersects(boxColliderB.bounds))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    public bool IsOnNet(Vector3 pos)
    {
        if (spiderNetParent.transform.childCount != 0)
        {
            foreach (Transform child in spiderNetParent.transform)
            {
                if (child.GetComponent<Collider2D>().bounds.Contains(pos))
                {
                    return true;
                }
            }
        }
        return false;
    }

    public void Attack()
    {
        player.GetComponent<PlayerLife>().GetDamege(1);
        isAttackable = false;
    }

    public void Destroy()
    {
        Instantiate(explosion, transform.position, new Quaternion());
        Destroy(gameObject);
    }
}
