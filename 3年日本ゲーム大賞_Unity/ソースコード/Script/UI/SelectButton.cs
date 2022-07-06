using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class SelectButton : MonoBehaviour
{
    private Image image;
    private Animator animator;

    /*[Header("選択時スプライト")]
    [SerializeField]
    Sprite selectSprite;

    [Header("非選択時スプライト")]
    [SerializeField]
    Sprite deselectSprite;*/

    [Header("選択時マテリアル")]
    [SerializeField]
    Material selectMaterial;

    [Header("非選択時マテリアル")]
    [SerializeField]
    Material deselectMaterial;

    private void ChangeSprite(Sprite sprite)
    {
        image.sprite = sprite;
    }

    private void ChangeMaterial(Material material)
    {
        image.material = material;
    }


    public void SelectBehavior()
    {
        animator.SetBool("IsSelect", true);
        image.material.SetFloat("_IsBlinking", 0);
        //ChangeSprite(selectSprite);
        ChangeMaterial(selectMaterial);
    }

    public void DeselectBehavior()
    {
        animator.SetBool("IsSelect", false);
        image.material.SetFloat("_IsBlinking", 1);
        //ChangeSprite(deselectSprite);
        ChangeMaterial(deselectMaterial);
    }


    private void Awake()
    {
        image = GetComponent<Image>();
        animator = GetComponent<Animator>();
    }
    // Start is called before the first frame update
    void Start()
    {
        
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    
}
