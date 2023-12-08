using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

[CustomEditor(typeof(LevelParser))]
public class l2uParser : Editor
{
    public override void OnInspectorGUI()
    {
        DrawDefaultInspector();
        LevelParser parser = (LevelParser)target;

        if (GUILayout.Button("Create Level"))
        {
            parser.CreateScene();
        }

    }

}
