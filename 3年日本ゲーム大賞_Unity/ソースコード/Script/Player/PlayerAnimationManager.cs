//#define MYDEBUG
/*
 #if MYDEBUG
 #endif
 */
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerAnimationManager : MonoBehaviour
{
    [SerializeField]
    float VEL = 5f;
    new Rigidbody2D rigidbody2D;
    Animator animator;
    int contactStayFrameCount;
    bool jumpTriger;

    enum COLLISIONDIRECTION{
        UP,
        DOWN,
        RIGHT,
        LEFT = RIGHT
    }
    // Start is called before the first frame update
    void Start()
    {
        contactStayFrameCount = 0;
        rigidbody2D = GetComponent<Rigidbody2D>();
        animator = GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
        MovingDirectionHor();
        animator.SetFloat("Speed", 1 + (rigidbody2D.velocity.magnitude * 0.3f));
#if MYDEBUG
        Debug.Log(animator.GetBool("IsGround"));
        Debug.Log(contactStayFrameCount);
#endif
        
        if (animator.GetBool("IsGround"))
        { 
            if (!jumpTriger && contactStayFrameCount > 10)
                animator.SetInteger("trans", -1);
        }
        else
            contactStayFrameCount = 0;
        jumpTriger = false;
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
#if MYDEBUG
        //Debug.Log("バウンドした！");
        //Debug.Log(rigidbody2D.velocity.magnitude);
        
#endif
        //foreach (ContactPoint2D point in collision.contacts)
        //{
            //if(rigidbody2D.velocity.magnitude > 2)
            //{
                if (collision.contacts[0].normal == Vector2.left)
                {
#if MYDEBUG
                    Debug.Log("Right");
#endif
                    animator.SetInteger("trans", (int)COLLISIONDIRECTION.RIGHT);
                    animator.Play("Bounce_Right_Player", 0, 0);
                }
                else if(collision.contacts[0].normal == Vector2.right)
                {
#if MYDEBUG
                    Debug.Log("Left");
#endif
                    animator.SetInteger("trans", (int)COLLISIONDIRECTION.LEFT);
                    animator.Play("Bounce_Right_Player", 0, 0);
                }
                else if(collision.contacts[0].normal == Vector2.down)
                {
#if MYDEBUG
                    Debug.Log("Up");
#endif
                    animator.SetInteger("trans", (int)COLLISIONDIRECTION.UP);
                    animator.Play("Bounce_Up_Player", 0, 0);
                    jumpTriger = true;
                }
                else
                {
#if MYDEBUG
                    Debug.Log("Down");
#endif
                    animator.SetInteger("trans", (int)COLLISIONDIRECTION.DOWN);
                    animator.Play("Bounce_Down_Player", 0, 0);
                }
            //}
        //}
    }

    private void OnCollisionStay2D(Collision2D collision)
    {
        ++contactStayFrameCount;
        //foreach (ContactPoint2D point in collision.contacts)
        //{
            if (collision.contacts[0].normal == Vector2.up)
            {
                animator.SetBool("IsGround", true);
            }
        //}
    }

    private void OnCollisionExit2D(Collision2D collision)
    {
        animator.SetBool("IsGround", false);
    }

    public void AnimationJump()
{
        animator.SetInteger("trans", (int)COLLISIONDIRECTION.DOWN);
        animator.Play("Bounce_Down_Player", 0, 0);
        jumpTriger = true;
    }

    private void MovingDirectionHor()
    {
        //右向きか左向きか
        if(rigidbody2D.velocity.x > 0.5)
        {
            transform.localScale = new Vector3(Mathf.Abs(transform.localScale.x), transform.localScale.y, transform.localScale.z);
        }
        else if(rigidbody2D.velocity.x < -0.5)
        {
            transform.localScale = new Vector3(-Mathf.Abs(transform.localScale.x), transform.localScale.y, transform.localScale.z);
        }
    }
}
