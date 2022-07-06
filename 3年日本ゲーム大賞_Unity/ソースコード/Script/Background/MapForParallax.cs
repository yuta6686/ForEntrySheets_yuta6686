using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class MapForParallax
{
    public static float Map(float value, float fromMin, float fromMax, float toMin, float toMax, bool trimming)
    {
        var val = (value - fromMin) / (fromMax - fromMin) * (toMax - toMin) + toMin;
        return trimming ? System.Math.Max(System.Math.Min(val, toMax), toMin) : val;
    }

    public static float Map(float value, float fromMin, float fromMax, float toMin, float toMax)
    {
        var val = (value - fromMin) / (fromMax - fromMin) * (toMax - toMin) + toMin;
        return System.Math.Max(System.Math.Min(val, toMax), toMin);
    }
}
