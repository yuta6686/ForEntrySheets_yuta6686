using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ToExit : MonoBehaviour
{
    GameObject sceneControllerCam;

    GameObject player;



    [SerializeField] float TransitionTime = 4.0f;
    [SerializeField] float xPos = -7.5f;
    [SerializeField] float EmissionNormalize = 3.0f;

    private Animator animator;
    private MeshRenderer renderer;
    private SpriteRenderer childRenderer;
    private float FirstEmission;
    

    // Start is called before the first frame update
    void Start()
    {
        sceneControllerCam = Camera.main.gameObject;
        player = GameObject.Find("Player");           
        animator = GetComponent<Animator>();
        renderer = GetComponent<MeshRenderer>();
        childRenderer = GetComponentInChildren<SpriteRenderer>();
        FirstEmission = renderer.material.GetFloat("_Emission");
    }

    // Update is called once per frame
    void Update()
    {
        ExitRange();
    }

    private void ExitRange()
    {
        float diff = Mathf.Abs(player.transform.position.x - xPos) / EmissionNormalize;
        

        if (player.transform.position.x > xPos)
        {            
            
            renderer.material.SetFloat("_Emission", diff);
            renderer.material.SetFloat("_BlinkMinAlphaValue", 0.75f);
            childRenderer.material.SetFloat("_Emission", diff);
            childRenderer.material.SetFloat("_BlinkMinAlphaValue", 0.75f);

            animator.SetBool("blScale", true);
        }
        else
        {
            //renderer.material.SetColor("_MainColor", new Color(1, 1, 1, 1));
            renderer.material.SetFloat("_Emission", FirstEmission);
            renderer.material.SetFloat("_BlinkMinAlphaValue", 0.25f);
            childRenderer.material.SetFloat("_Emission", FirstEmission);
            childRenderer.material.SetFloat("_BlinkMinAlphaValue", 0.25f);

            animator.SetBool("blScale", false);
        }
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.transform.tag == "Player")
        {
            GetComponent<BoxCollider2D>().isTrigger = true;
            animator.SetBool("blMove", true);
            Invoke("Quit", TransitionTime);
        }
    }
    private void OnCollisionStay2D(Collision2D collision)
    {
        Invoke("AnimatorSetBoolFalse", 1.0f);
    }

    void AnimatorSetBoolFalse()
    {
        animator.SetBool("blMove", false);
    }



    void Quit()
    {
#if UNITY_EDITOR
        UnityEditor.EditorApplication.isPlaying = false;
#elif UNITY_STANDALONE
      UnityEngine.Application.Quit();
#endif
    }
}
