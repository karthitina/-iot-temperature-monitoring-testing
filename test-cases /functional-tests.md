# Functional Test Cases - IoT Temperature Monitoring System
## Test Case 1: Verify Temperature Reading Accuracy
- **Objective:** Ensure the temperature sensor provides accurate readings
within a margin of error.
- **Preconditions:** Sensor calibrated to room temperature (25°C).
- **Steps:**
 1. Record room temperature using a reference thermometer.
 2. Record sensor readings for 5 minutes.
 3. Compare sensor readings to the reference thermometer.
- **Expected Result:** Sensor readings should be within ±1°C of the
reference.
## Test Case 2: Validate Cloud Data Transmission
- **Objective:** Verify that the temperature data is correctly transmitted
to the cloud server.
- **Preconditions:** Sensor connected to Wi-Fi, cloud service set up.
- **Steps:**
 1. Simulate temperature change by heating the sensor.
 2. Check cloud server to verify data transmission.
- **Expected Result:** Data on the cloud should match sensor readings.
