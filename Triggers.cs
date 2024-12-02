using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;
using System.Threading;

public class Triggers : MonoBehaviour
{

    private static SerialPort sp;

    private void onDestroy()
    {
        sp.Close();
    }

    private void Start()
    {
        sp = new SerialPort("COM4", 115200);
        sp.Open();
        send("0");
    }

    private void send(string command)
    {
        //sp.Close();
        //sp.Open();
        if (sp.IsOpen)
        {
            sp.WriteLine(command);
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("HeatTrigger"))
        {
            print("Heat zone entered!");
            send("1");
        }
        else if (other.CompareTag("ColdTrigger"))
        {
            print("Cold zone entered!");
            send("3");
        }
    }

    private void OnTriggerStay(Collider other)
    {
        if (other.CompareTag("HeatTrigger"))
        {
            print("In heat zone!");

        }
        else if (other.CompareTag("ColdTrigger"))
        {
            //print("In cold zone!");
            if (Input.GetKeyDown(KeyCode.E))
            {
                print("E pressed!");
                send("2");
            }
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.CompareTag("HeatTrigger"))
        {
            print("Heat zone exited!");
            send("0");
        }
        else if (other.CompareTag("ColdTrigger"))
        {
            print("Cold zone exited!");
            send("0");
        }
    }

}