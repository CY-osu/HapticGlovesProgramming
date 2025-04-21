using System.Security.Policy;
using UnityEngine;

public class heatScript : MonoBehaviour
{
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    public bool heat = false;

    private void OnTriggerEnter(Collider other)
    {
        if (!heat)
        {
            heat = true;
            print("heat on!");
        }

    }

        private void OnTriggerExit(Collider other)
        {

            if (heat)
            {
                heat = false;
            print("heat off!");
            }

        }
}
