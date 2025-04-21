using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;
using System.Threading;
using Unity.VisualScripting;

public class TempMain : MonoBehaviour
{

    private static SerialPort sp;
    [SerializeField] heatScript heatScript;
    [SerializeField] coldScript coldScript;
    bool first = false;
    bool initialized = false;

    private void onDestroy()
    {
        sp.Close();
    }

    private void Start()
    {
        sp = new SerialPort("COM6", 9600);
        while (!sp.IsOpen)
        {
            sp.Open();
        }
        send("0");
        print("Initialized!");
        initialized = true;
    }

    private void Update()
    {
        while (!sp.IsOpen)
        {
            sp.Open();
        }

        if (heatScript.heat)
        {
            //print("heat on!");
            if (!first)
            {
                print("1 sent!");
                send("1");
                first = true;
            }
        }
        else if (!heatScript.heat && !coldScript.cold)
        {
            //print("heat off!");
            if (first)
            {
                print("0 heat sent!");
                send("0");
                first = false;
            }
        }

        if (coldScript.cold)
        {
            if (!first)
            {
                print("2 sent!");
                send("2");
                first = true;
            }
        } else if (!coldScript.cold && !heatScript.heat)
        {
            if (first)
            {
                print("0 cold sent!");
                send("0");
                first = false;
            }
        }

    }

    private void send(string command)
    {
        if (sp.IsOpen)
        {
            sp.WriteLine(command);
        }
    
    }

}