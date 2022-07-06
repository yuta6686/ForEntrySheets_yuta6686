using UnityEngine;

public class Explosion001 : MonoBehaviour
{
    public void OnCompleteAnimation()
    {
        Destroy(this.gameObject);
    }
}
