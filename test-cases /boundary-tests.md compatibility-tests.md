# Boundary Test Cases - IoT Temperature Monitoring System
## Test Case 1: Test Maximum Temperature
- **Objective:** Test the system's performance at the maximum supported
temperature.
- **Preconditions:** Sensor connected and system operational.
- **Steps:**
 1. Expose the sensor to its maximum rated temperature (e.g., 100°C).
 2. Monitor the sensor and cloud for data updates.
 3. - **Expected Result:** Sensor should provide valid data until reaching
maximum threshold.
## Test Case 2: Test Minimum Temperature
- **Objective:** Test the system at the minimum temperature.
- **Preconditions:** Sensor and system operational.
- **Steps:**
 1. Expose the sensor to its minimum rated temperature (e.g., -20°C).
 2. Monitor the sensor and cloud for data updates.
- **Expected Result:** Sensor should provide valid data at the lowest
threshold.
## Test Case 3: Test Temperature Just Above Maximum Threshold
- **Objective:**  Verify system behavior when the temperature slightly exceeds the maximum supported temperature.
- **Preconditions:** Sensor connected and system operational.
- **Steps:**
1. Gradually increase the temperature to just above the sensor's maximum rated threshold (e.g., if the maximum is 100°C, increase it to 101°C).
2. Monitor the sensor and cloud for data updates.
3. Observe system logs or alerts for any error messages or warnings.
- **Expected Result:** 
1. The sensor may either provide an error or stop transmitting valid data.
2. The system should trigger an alert indicating that the temperature has exceeded the supported threshold.
3. The system should log the event for further analysis.







