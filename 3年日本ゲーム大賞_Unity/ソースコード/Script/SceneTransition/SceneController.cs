using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Threading.Tasks;
using UnityEngine.SceneManagement;

public class SceneController : MonoBehaviour
{
    // Start is called before the first frame update

    public GameObject fade;

    private GameObject fadeCanvas;

    private int fadeTime = 1500;

    void Start()
    {
        if (!FadeManager.isFadeInstance)
        {
            Instantiate(fade);
        }

        Invoke("findFadeObject", 0.02f);
    }

    void findFadeObject()
    {
        fadeCanvas = GameObject.FindGameObjectWithTag("Fade");
        fadeCanvas.GetComponent<FadeManager>().fadeIn();
    }

    public async void sceneChange(string sceneName)
    {
        fadeCanvas.GetComponent<FadeManager>().fadeOut();
        await Task.Delay(fadeTime);
        SceneManager.LoadScene(sceneName);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
