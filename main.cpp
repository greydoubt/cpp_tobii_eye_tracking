//C++ code that uses the Tobii Stream SDK to track eye movements and output the X and Y coordinates:


#include <iostream>
#include <tobii/tobii_streams.h>

// Callback function to handle gaze data
void gazePointCallback(tobii_gaze_point_t const* gaze_point, void* user_data) {
    // Extract the gaze coordinates
    double x = gaze_point->position_xy[0];
    double y = gaze_point->position_xy[1];
    
    // Output the coordinates
    std::cout << "Gaze coordinates: X=" << x << ", Y=" << y << std::endl;
}

int main() {
    // Initialize Tobii Stream engine
    tobii_api_t* api;
    tobii_error_t error = tobii_api_create(&api, nullptr, nullptr);
    if (error != TOBII_ERROR_NO_ERROR) {
        std::cerr << "Failed to initialize the Tobii API." << std::endl;
        return 1;
    }
    
    // Connect to the eye tracker
    tobii_device_t* device;
    error = tobii_device_create(api, nullptr, &device);
    if (error != TOBII_ERROR_NO_ERROR) {
        std::cerr << "Failed to connect to the eye tracker." << std::endl;
        tobii_api_destroy(api);
        return 1;
    }
    
    // Start gaze data stream
    error = tobii_gaze_point_subscribe(device, gazePointCallback, nullptr);
    if (error != TOBII_ERROR_NO_ERROR) {
        std::cerr << "Failed to subscribe to gaze data stream." << std::endl;
        tobii_device_destroy(device);
        tobii_api_destroy(api);
        return 1;
    }
    
    // Main loop (you can replace this with your application's main loop)
    while (true) {
        // Process other tasks or update your application
        
        // Wait for gaze data
        error = tobii_wait_for_callbacks(1, &device);
        if (error != TOBII_ERROR_NO_ERROR) {
            std::cerr << "Error while waiting for gaze data." << std::endl;
            break;
        }
        
        // Process gaze data callbacks
        error = tobii_device_process_callbacks(device);
        if (error != TOBII_ERROR_NO_ERROR) {
            std::cerr << "Error while processing gaze data callbacks." << std::endl;
            break;
        }
    }
    
    // Cleanup and shutdown
    tobii_gaze_point_unsubscribe(device);
    tobii_device_destroy(device);
    tobii_api_destroy(api);
    
    return 0;
}
