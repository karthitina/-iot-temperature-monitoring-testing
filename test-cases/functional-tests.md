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
## Test Case 3: Test Battery Life Under Continuous Operation
- **Objective:** Verify the battery life of the IoT device under continuous operation.
- **Preconditions:**  Device fully charged, continuous data logging and transmission enabled.
- **Steps:**
1. Fully charge the device and start continuous temperature monitoring.
2. Let the device operate continuously until it powers off.
3. Record the total operating time.
- **Expected Result:**  The device should operate continuously for at least 24 hours before needing a recharge.
## Test Case 4: Validate Alert System for High Temperature
- **Objective:** Ensure the system correctly triggers an alert when the temperature exceeds a predefined threshold.
- **Preconditions:** Alert threshold set to 50°C, notification system configured.
- **Steps:**
1. Gradually increase the temperature around the sensor.
2. Monitor the system for alert generation.
3. Record the temperature at which the alert is triggered.
- **Expected Result:** The system should generate an alert when the temperature reaches 50°C, and the alert should be correctly transmitted to the configured notification endpoint (e.g., mobile app, email).
