using System;
using System.IO;
using System.Collections.Generic;
using UnityEngine;

public class LevelParser : MonoBehaviour
{
    public string pathToLevel;
    public int lengthPerGameObject = 28;

    public List<String> objectStats;
    public List<GameObject> gameObjectList;

    //Gameobject
    GameObject createdObject = null;
    int createdObjectType = 0;

    public void CreateScene()
    {
        foreach (GameObject go in gameObjectList)
        {
            DestroyImmediate(go);
        }

        gameObjectList.Clear();
        objectStats.Clear();

        Debug.Log("Create Scene");
        ParseFile();
        LoadLevel();


    }

    private void LoadLevel()
    {
        int index = 0;
       

        for (int i = 0; i < objectStats.Count; i++)
        {
            //Debug.Log("i: " + i + "  index: " + index + " object Stat: " + objectStats[i]);
            switch (index)
            {
                case 3:
                    CreateGameObject(int.Parse(objectStats[i]));
                    break;
                case 5:
                    SetXPosition(float.Parse(objectStats[i]));
                    break;
                case 6:
                    SetYPosition(float.Parse(objectStats[i]));
                    break;
                case 7:
                    SetZPosition(float.Parse(objectStats[i]));
                    break;
                case 9:
                    SetXRotation(float.Parse(objectStats[i]));
                    break;
                case 10:
                    SetYRotation(float.Parse(objectStats[i]));
                    break;
                case 11:
                    SetZRotation(float.Parse(objectStats[i]));
                    break;
                case 13:
                    SetXScale(float.Parse(objectStats[i]));
                    break;
                case 14:
                    SetYScale(float.Parse(objectStats[i]));
                    break;
                case 15:
                    SetZScale(float.Parse(objectStats[i]));
                    break;
                case 17:
                    EnablegameObject(int.Parse(objectStats[i]));
                    break;
                case 19:
                    AddPhysics(int.Parse(objectStats[i]));
                    break;
                case 23:
                    EnableRigidbody(int.Parse(objectStats[i]));
                    break;
                case 25:
                    EnableGravity(int.Parse(objectStats[i]));
                    break;
                case 27:
                    SetMass(float.Parse(objectStats[i]));
                    break;


            }

            index++;
            if (index > lengthPerGameObject - 1)
            {
                //Debug.Log("INDEX RESET");
                //Debug.Log("length: " + lengthPerGameObject + "  index: " + index);
                index = 0;
            }
        }
    }

    private void SetMass(float mass)
    {
        Rigidbody rb = createdObject.GetComponent<Rigidbody>();
        if (rb)
        {
            rb.mass = mass;
        }
      
    }

    private void EnableGravity(int value)
    {
        Rigidbody rb = createdObject.GetComponent<Rigidbody>();
        if (rb)
        {
            if (value == 0)
            {
                rb.useGravity = false;
            }
            else if (value == 1)
            {
                rb.useGravity = true;
            }
        }
        
    }

    private void EnableRigidbody(int value)
    {
        Rigidbody rb = createdObject.GetComponent<Rigidbody>();
        if (rb)
        {
            if (value == 0)
            {
                rb.isKinematic = false;
            }
            else if (value == 1)
            {
                rb.isKinematic = true;
            }
        }
       
    }

    private void AddPhysics(int value)
    {
        if (value == 1)
        {
            if (createdObjectType == 1)
            {
                createdObject.AddComponent<Rigidbody>();
            }
            else if (createdObjectType == 2)
            {
                createdObject.GetComponent<MeshCollider>().convex = true;
                createdObject.AddComponent<Rigidbody>();
            }
            
        }
    }

    private void CreateGameObject(int type)
    {
        if (type == 1)
        {
            createdObject = GameObject.CreatePrimitive(PrimitiveType.Cube);
            gameObjectList.Add(createdObject);

            createdObjectType = 1;
        }
        else if (type == 2)
        {
            createdObject = GameObject.CreatePrimitive(PrimitiveType.Plane);
            gameObjectList.Add(createdObject);

            createdObjectType = 2;
        }
    }

    private void SetXPosition(float newPos)
    {
        Vector3 pos = createdObject.transform.position;
        pos.x = newPos;

        createdObject.transform.position = pos;
    }

    private void SetYPosition(float newPos)
    {
        Vector3 pos = createdObject.transform.position;
        pos.y = newPos;

        createdObject.transform.position = pos;
    }
    private void SetZPosition(float newPos)
    {
        Vector3 pos = createdObject.transform.position;
        pos.z = newPos;

        createdObject.transform.position = pos;
    }

    private void SetXRotation(float newRot)
    {
        Vector3 rot = createdObject.transform.rotation.eulerAngles;
        rot.x = Mathf.Rad2Deg * newRot;

        createdObject.transform.rotation = Quaternion.Euler(rot.x, rot.y, rot.z);
    }

    private void SetYRotation(float newRot)
    {
        Vector3 rot = createdObject.transform.rotation.eulerAngles;
        rot.y = Mathf.Rad2Deg * newRot;

        createdObject.transform.rotation = Quaternion.Euler(rot.x, rot.y, rot.z);
    }

    private void SetZRotation(float newRot)
    {
        Vector3 rot = createdObject.transform.rotation.eulerAngles;
        rot.z = Mathf.Rad2Deg * newRot;

        createdObject.transform.rotation = Quaternion.Euler(rot.x, rot.y, rot.z);
    }

    private void SetXScale(float newScale)
    {
        Vector3 scale = createdObject.transform.localScale;

        if (createdObjectType == 1)
        {
            scale.x = newScale;
        }
        else if (createdObjectType == 2)
        {
            scale.x = newScale / 10;
        }

        createdObject.transform.localScale = scale;

    }

    private void SetYScale(float newScale)
    {
        Vector3 scale = createdObject.transform.localScale;
        if (createdObjectType == 1)
        {
            scale.y = newScale;
        }
        else if (createdObjectType == 2)
        {
            scale.y = newScale / 10;
        }

        createdObject.transform.localScale = scale;
    }

    private void SetZScale(float newScale)
    {
        Vector3 scale = createdObject.transform.localScale;
        if (createdObjectType == 1)
        {
            scale.z = newScale;
        }
        else if (createdObjectType == 2)
        {
            scale.z = newScale / 10;
        }

        createdObject.transform.localScale = scale;
    }


    private void EnablegameObject(int value)
    {
        if (value == 0)
        {
            createdObject.SetActive(false);
        }
        else if (value == 1)
        {
            createdObject.SetActive(true);
        }
    }

    private void ParseFile()
    {
        string fileContents = File.ReadAllText(pathToLevel);
        string[] words = ParseText(fileContents);

        foreach (string word in words)
        {
            //Debug.Log(word);
            objectStats.Add(word);
        }

    }

    private string[] ParseText(string input)
    {
        char[] delimiters = new char[] { ' ', '\n', '\t', '\r' }; // Include new line and tab characters
        return input.Split(delimiters, StringSplitOptions.RemoveEmptyEntries);
    }
}
