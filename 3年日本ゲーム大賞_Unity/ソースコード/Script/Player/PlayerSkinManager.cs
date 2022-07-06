using UnityEngine;

public class PlayerSkinManager : MonoBehaviour
{
    Rigidbody2D rigidbody2D;
    SpriteRenderer renderer;
    float movementSpeed;

    private void Start()
    {
        rigidbody2D = GetComponent<Rigidbody2D>();
        renderer = GetComponent<SpriteRenderer>();
    }

    void Update()
    {
        movementSpeed = rigidbody2D.velocity.magnitude;

        ChangeRedColor((byte)(movementSpeed * 8));

        //Debug.Log(movementSpeed);
    }

    void ChangeRedColor(byte rColor)
    {
        renderer.color = new Color32(255, (byte)(255 - rColor), (byte)(255 - rColor), 255);
    }
}