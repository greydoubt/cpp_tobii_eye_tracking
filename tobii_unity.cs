using UnityEngine;
using Tobii.XR;

public class EyeTrackingExample : MonoBehaviour
{
    private void Update()
    {
        // Check if Tobii XR is available and connected
        if (TobiiXR.EyeTrackingData.IsAvailable && TobiiXR.EyeTrackingData.GazeRay.IsValid)
        {
            // Get the gaze ray from Tobii XR
            Ray gazeRay = TobiiXR.EyeTrackingData.GazeRay;

            // Perform actions based on gaze ray
            // For example, move an object with the gaze ray:
            if (Physics.Raycast(gazeRay, out RaycastHit hit))
            {
                transform.position = hit.point;
            }
        }
    }
}
