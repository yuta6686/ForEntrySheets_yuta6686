using UnityEngine;
using System.IO;
using UnityEngine.SceneManagement;

public class SaveManager : MonoBehaviour
{
    string path;
    SaveData saveData;

    private void Awake()
    {
        path = Application.persistentDataPath + "/savedata.json";
        saveData = new SaveData();
    }

    public void StageClear()
    {
        string sceneNo = SceneManager.GetActiveScene().name.Remove(0, 9);
        int no = int.Parse(sceneNo);
        saveData.clearStage = no;
    }

    public void Save()
    {
        string json = JsonUtility.ToJson(saveData);
        StreamWriter streamWriter = new StreamWriter(path);
        streamWriter.Write(json);
        streamWriter.Flush();
        streamWriter.Close();
    }

    public void Load()
    {
        if(File.Exists(path))
        {
            StreamReader streamReader;
            streamReader = new StreamReader(path);
            string data = streamReader.ReadToEnd();
            streamReader.Close();
            saveData = JsonUtility.FromJson<SaveData>(data);
        }
    }
}
