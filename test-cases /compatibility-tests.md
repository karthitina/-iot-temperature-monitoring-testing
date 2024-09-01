# Compatibility Test Cases - IoT Temperature Monitoring System
## Test Case 1: Verify Cloud Service Compatibility
- **Objective:** Test the system's compatibility with multiple cloud
platforms (e.g., AWS IoT, Azure IoT).
- **Steps:**
 1. Connect the IoT device to AWS IoT.
 2. Record and analyze data transmission.
 3. Repeat steps for Azure IoT.
- **Expected Result:** The system should transmit data correctly to both
platforms.
## Test Case 2: Verify Compatibility with Different Network Protocols
- **Objective:** Test the system's compatibility with various network communication protocols (e.g., MQTT, HTTP, CoAP).
- **Steps:**
1. Connect the IoT device to the network using the MQTT protocol.
2. Transmit temperature data and monitor the system for successful data transfer and reception.
3. Repeat the process using the HTTP protocol.
4. Repeat the process using the CoAP protocol.
5. Compare the data transmission performance and accuracy across all protocols.
- **Expected Result:** 
1. The system should transmit data correctly and consistently across all tested protocols.
2. There should be no significant data loss, delays, or errors regardless of the protocol used.
3. The system should maintain the same level of accuracy and performance with each protocol.








