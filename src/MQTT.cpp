#include <WiFi.h>                // Library for Wi-Fi
#include <PubSubClient.h>        // Library for MQTT
#include <DHT.h>                 // Library for DHT sensor

// Wi-Fi credentials
const char* ssid = "HomeNetwork";           // Your network SSID (name)
const char* password = "SuperSecret123";    // Your network password

// AWS IoT endpoint and MQTT configuration
const char* mqtt_server = "a3k7odshaiiot-ats.iot.us-east-1.amazonaws.com";   // AWS IoT endpoint (sample endpoint for US East region)
const char* mqtt_topic = "temperature/data";                                 // MQTT topic to publish data
const char* mqtt_alert_topic = "temperature/alerts";                         // MQTT topic to publish alerts
const int mqtt_port = 8883;                                                  // MQTT port (AWS IoT uses port 8883)

// Device certificate and key (Use your device's specific certificate and private key)
const char* aws_cert_ca = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEArQw...sfgSDFGSFGTGFSD\n" \
"-----END CERTIFICATE-----";  // AWS IoT Root CA (sample certificate)

const char* aws_cert_crt = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDWTCCAkGgAwIBAgIUfAFQLobGWye35...gEHASDFSDFWERWETYWQREYQWYERYQ\n" \
"-----END CERTIFICATE-----";  // Device Certificate (sample certificate)

const char* aws_cert_private = \
"-----BEGIN PRIVATE KEY-----\n" \
"MIIEvwIBADANBgkqhkiG9w0BAQEFAASCBKYwggSiAgEAAoIBAQ...EFHASDFHDFHSDFHSDHFSDF\n" \
"-----END PRIVATE KEY-----";  // Private Key (sample private key)

// Initialize DHT sensor
#define DHTPIN 4          // GPIO Pin where the DHT11 is connected
#define DHTTYPE DHT11     // DHT11 sensor type
DHT dht(DHTPIN, DHTTYPE);

// Initialize Wi-Fi and MQTT client
WiFiClientSecure espClient; 
PubSubClient client(espClient);

// Define thresholds for temperature alerts
const float MAX_TEMP_THRESHOLD = 40.0;  // Maximum temperature threshold in Celsius
const float MIN_TEMP_THRESHOLD = 2.0; // Minimum temperature threshold in Celsius

// Function to connect to Wi-Fi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// Function to reconnect to AWS IoT if the connection is lost
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// Function to publish temperature data to AWS IoT
void publishData(float temperature, float humidity) {
  String payload = "{\"temperature\": " + String(temperature, 2) + ", \"humidity\": " + String(humidity, 2) + "}";
  Serial.print("Publishing data: ");
  Serial.println(payload);

  if (!client.publish(mqtt_topic, (char*) payload.c_str())) {
    Serial.println("Publish failed");
  } else {
    Serial.println("Publish succeeded");
  }
}

// Function to publish an alert when temperature is out of bounds
void publishAlert(String message) {
  Serial.print("Publishing alert: ");
  Serial.println(message);

  if (!client.publish(mqtt_alert_topic, (char*) message.c_str())) {
    Serial.println("Alert publish failed");
  } else {
    Serial.println("Alert publish succeeded");
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  setup_wifi();

  // Configure MQTT server and certificate
  espClient.setCACert(aws_cert_ca);
  espClient.setCertificate(aws_cert_crt);
  espClient.setPrivateKey(aws_cert_private);
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Read temperature and humidity from DHT11 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if any reads failed
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("Â°C, Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  // Publish data
  publishData(temperature, humidity);

  // Check for temperature thresholds and send alerts
  if (temperature > MAX_TEMP_THRESHOLD) {
    publishAlert("Alert! Temperature exceeded maximum threshold.");
  } else if (temperature < MIN_TEMP_THRESHOLD) {
    publishAlert("Alert! Temperature dropped below minimum threshold.");
  }

  delay(10000); // Delay between readings
}
