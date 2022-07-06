using UnityEngine;
using UnityEngine.InputSystem;

public class PlayerJustJump : MonoBehaviour
{
    new Rigidbody2D rigidbody2D;
    PlayerActionInput input;

    [SerializeField] float jumpPower;
    [SerializeField] int JUST_TIME;
    int remainingJustTime;

    private void Start()
    {
        rigidbody2D = GetComponent<Rigidbody2D>();
        input = new PlayerActionInput();
        input.Player.JustJump.performed += context => OnJustJump();
        input.Enable();
    }

    private void Update()
    {
        remainingJustTime--;
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
       if( collision.gameObject.tag == "Ground")
        {
            if(remainingJustTime >0)
            {
                rigidbody2D.AddForce(new Vector2(0, jumpPower));
            }
        }
    }

    public void OnJustJump()
    {
        remainingJustTime = JUST_TIME;
    }
}
