# Test Environment Setup
## Hardware Setup
- **Sensor:** DHT11 Temperature Sensor
- **Microcontroller:** ESP32
- **Other:** Wi-Fi Router, Laptop, Power Supply
## Software Setup
- **Firmware:** Custom firmware developed for the ESP32 to transmit data
over Wi-Fi.
- **Cloud:** AWS IoT configured to receive data from the ESP32.
- **Tools:** Serial Monitor for logs, cloud dashboard for data
visualization.
## Steps to Recreate Environment
1. Connect the DHT11 sensor to the ESP32 as per the wiring diagram.
2. Flash the firmware onto the ESP32.
3. Connect the ESP32 to Wi-Fi and verify cloud connectivity.

   To integrate AWS IoT with Grafana for visualizing temperature data, follow these steps:
1. Configure an AWS IoT Rule
a. Create an AWS IoT Rule:
•	Go to AWS IoT Core Console: Open the AWS Management Console and navigate to AWS IoT Core.
•	Select ‘Rules’: In the navigation pane, click on "Act" and then "Rules."
•	Create a Rule: Click on “Create a rule” to start defining a new rule.
•	Define Rule Query: Enter a SQL-like query to filter incoming messages. For example:
sql
Copy code
SELECT * FROM 'your/topic'
•	Add Action: Choose the action that will process the incoming data. You can send data to various AWS services:
o	DynamoDB: Store the data in a DynamoDB table. Choose “Insert a message into a DynamoDB table” and specify the table and attributes.
o	S3: Store the data in an S3 bucket. Choose “Send a message to an Amazon S3 bucket” and specify the bucket and file format.
b. Set Permissions:
•	Ensure that the AWS IoT Rule has the necessary permissions to interact with the chosen AWS services. Attach an appropriate IAM role with policies that allow access to DynamoDB or S3.
c. Test the Rule:
•	Publish test messages to the topic and verify that data is being sent to DynamoDB or S3 as expected.
2. Set Up Grafana with AWS as a Data Source
a. Install Grafana:
•	Download and Install: Follow the installation instructions for your operating system from the Grafana website.
b. Configure AWS Data Source in Grafana:
•	Open Grafana: Access Grafana through your web browser (usually at http://localhost:3000 by default).
•	Add Data Source: Go to the configuration (gear icon) and select “Data Sources.”
•	Select AWS CloudWatch: Grafana can use AWS CloudWatch as a data source, which is helpful for integrating with AWS services.
•	Configure Data Source: Enter the required details:
o	Name: Give a name for the data source.
o	Default: Set this as default if you want it to be the primary data source.
o	Access: Choose "Server" or "Browser" access mode based on your setup.
o	Authentication: Set up authentication using AWS credentials or IAM roles. You can use AWS access keys or assume a role with the required permissions.
o	Default Region: Specify the AWS region where your resources (DynamoDB, S3) are located.
c. Add DynamoDB or S3 Data Source (Optional):
•	For direct integration with DynamoDB or S3, you may need plugins or custom solutions. The AWS CloudWatch integration is commonly used because it can be configured to aggregate and visualize data from other AWS services.
3. Visualize Data in Grafana
a. Create a Dashboard:
•	New Dashboard: Click on the “+” icon in the sidebar and select “Dashboard.”
•	Add a Panel: Click “Add new panel” to create a new visualization.
b. Query Data:
•	Select Data Source: Choose the AWS CloudWatch data source (or any other configured source).
•	Build Query: Write a query to fetch the temperature data from your data source. For example, if using CloudWatch, you might query a custom metric that logs temperature readings.
c. Customize Visualization:
•	Choose Visualization Type: Select the type of visualization (e.g., graph, gauge, table).
•	Configure Panel: Adjust settings such as time range, refresh interval, and visualization options to suit your needs.
d. Save and Share:
•	Save Dashboard: Save the dashboard with a meaningful name.
•	Share: Share the dashboard with others or embed it in other applications.
Summary
1.	Configure AWS IoT Rule: Set up a rule to direct data to DynamoDB or S3.
2.	Set Up Grafana: Integrate AWS CloudWatch with Grafana or use plugins to connect directly with DynamoDB/S3.
3.	Visualize Data: Create dashboards in Grafana to visualize and analyze the temperature data.
By following these steps, you'll be able to collect, store, and visualize IoT data effectively using AWS and Grafana.

