using System.Security.Policy;
using UnityEngine;

public class coldScript : MonoBehaviour
{
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {

    }

    public bool cold = false;

    private void OnTriggerEnter(Collider other)
    {
        if (!cold)
        {
            cold = true;
            print("cold on!");
        }

    }

    private void OnTriggerExit(Collider other)
    {

        if (cold)
        {
            cold = false;
            print("cold off!");
        }

    }
}
