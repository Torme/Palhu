using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour {

    public float speed = 10;
    private Rigidbody rb;
    private double x;
    private double z;

    private void Start()
    {
        rb = GetComponent<Rigidbody>();
        x = Input.acceleration.x;
        z = Input.acceleration.z;

    }

    private void FixedUpdate()
    {
        double x = (Input.acceleration.x - this.x);
        double z = (Input.acceleration.z - this.z);

        x = x > 0.3 ? 0.3 : (x < -0.3 ? -0.3 : x);
        z = z > 0.6 ? 0.6 : (z < -0.6 ? -0.6 : z);
        rb.AddForce(new Vector3((float)x, 0.0f, -(float)z) * speed);
    }

    void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.CompareTag("Pick Up"))
            other.gameObject.SetActive(false);
    }
}