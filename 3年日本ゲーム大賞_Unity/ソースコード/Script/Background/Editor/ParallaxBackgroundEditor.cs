using UnityEditor;
using UnityEngine;

[CustomEditor(typeof(ParallaxBackground))]
public class ParallaxBackgroundEditor : Editor
{
    ParallaxBackground parallaxBackground;

    public override void OnInspectorGUI()
    {
        base.OnInspectorGUI();

        if (parallaxBackground == null)
            parallaxBackground = target as ParallaxBackground;


        if (GUILayout.Button("Create"))
        {
            parallaxBackground.CreateParallaxBackground();
        }
    }
}