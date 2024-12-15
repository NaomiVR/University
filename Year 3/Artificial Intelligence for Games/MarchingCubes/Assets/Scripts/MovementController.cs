using UnityEngine;

public class MovementController : MonoBehaviour
{
    public float speed = 10f;
    public float sensitivity = 100f;
    
    private float _verticalRotation;
    
    public Canvas pauseMenu;

    void Update()
    {
        float horizontalInput = 0f;
        float verticalInput = 0f;
        float forwardInput = 0f;

        if (pauseMenu.enabled != true)
        {
            if (Input.GetKey(KeyCode.D))
            {
                horizontalInput = 1f;
            }
            else if (Input.GetKey(KeyCode.A))
            {
                horizontalInput = -1f;
            }

            if (Input.GetKey(KeyCode.W))
            {
                forwardInput = 1f;
            }
            else if (Input.GetKey(KeyCode.S))
            {
                forwardInput = -1f;
            }

            if (Input.GetKey(KeyCode.Space))
            {
                verticalInput = 1f;
            }
            else if (Input.GetKey(KeyCode.LeftControl))
            {
                verticalInput = -1f;
            }
            
            Vector3 movementDirection = new Vector3(horizontalInput, verticalInput, forwardInput).normalized;

            transform.Translate(movementDirection * (speed * Time.deltaTime));
            
            float mouseX = Input.GetAxis("Mouse X") * sensitivity * Time.deltaTime;
            float mouseY = Input.GetAxis("Mouse Y") * sensitivity * Time.deltaTime;

            _verticalRotation -= mouseY;
            _verticalRotation = Mathf.Clamp(_verticalRotation, -90f, 90f);

            transform.localRotation = Quaternion.Euler(_verticalRotation, transform.localRotation.eulerAngles.y + mouseX, 0f);
        }

        if (Input.GetKeyDown(KeyCode.Escape))
        {
            pauseMenu.enabled = !pauseMenu.enabled;
            Cursor.lockState = pauseMenu ? CursorLockMode.Confined : CursorLockMode.Locked;
            Cursor.visible = !Cursor.visible;
        }
    }
}