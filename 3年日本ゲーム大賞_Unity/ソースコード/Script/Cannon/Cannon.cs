using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cannon : MonoBehaviour
{
    // Start is called before the first frame update
    public enum CANNONMODE{
        PLAYER,
        OPTIONAL_ANGLE,
        RIGHT,
        LEFT,
        UP
    }

    public CANNONMODE   cannonMode;
    public float        second;
    public float        optionalAngle;
    public float        bulletSpeed;
    public GameObject   cannonBullet;
    private float       angle;
    private Vector3     dir;

    void Start()
    {
        StartCoroutine(WaitShoot(second));
        switch (cannonMode)
        {
            case CANNONMODE.PLAYER:
                LookAtPlayer();
                break;
            case CANNONMODE.OPTIONAL_ANGLE:
                angle = optionalAngle;
                transform.Rotate(new Vector3(0, 0, angle));
                break;
            case CANNONMODE.UP:
                transform.Rotate(new Vector3(0, 0, 0));
                angle = 0;
                dir = Vector3.up;
                break;
            case CANNONMODE.LEFT:
                transform.rotation = Quaternion.Euler(0, 0, 90);
                angle = 90;
                dir = Vector3.left;
                break;
            case CANNONMODE.RIGHT:
                transform.Rotate(new Vector3(0, 0, 270));
                angle = 270;
                dir = Vector3.right;
                break;
        }
    }

    // Update is called once per frame
    void Update()
    {
        switch (cannonMode)
        {
            case CANNONMODE.PLAYER:
                LookAtPlayer();
                break;
            default:
                break;
        }
    }

    private void LookAtPlayer()
    {
        if (GameObject.Find("ball 1"))
        {
            dir = (GameObject.Find("ball 1").transform.position - transform.position).normalized;
            dir.z = 0;// z軸固定
            transform.rotation = Quaternion.Slerp(transform.rotation, Quaternion.FromToRotation(Vector3.up, dir), 0.015f);
        }
    }

    private void Shoot()
    {
        var clone = Instantiate(cannonBullet, transform.position, transform.rotation);
        clone.GetComponent<Rigidbody2D>().velocity = dir * bulletSpeed;
    }

    private IEnumerator WaitShoot(float second)
    {
        for(; ; )
        {
            yield return new WaitForSeconds(second);
            Shoot();
        }
    }
}
