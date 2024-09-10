#include <WiFi.h>
#include <coap-simple.h>
#include <DHT.h>

// Wi-Fi credentials
const char* ssid = "HomeNetwork";
const char* password = "SuperSecret123";

// CoAP server address (example with port)
const char* coap_server = "coap://coap.my-iot-cloud.com:5683/temperature";
const char* coap_alert_server = "coap://coap.my-iot-cloud.com:5683/alerts";

// Pre-shared key (PSK) for CoAP authentication (real-like value)
const char* psk_key = "JskD9lLm90LpPskYrxxxT4562qVqB8a";

// Initialize DHT sensor
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Define thresholds for temperature alerts
const float MAX_TEMP_THRESHOLD = 40.0;  // Maximum temperature threshold in Celsius
const float MIN_TEMP_THRESHOLD = 2.0; // Minimum temperature threshold in Celsius

// Create CoAP client object
WiFiUDP udp;
Coap coap(udp);

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

// Function to send temperature data via CoAP with Pre-Shared Key (PSK)
void sendTemperatureData(float temperature, float humidity) {
  String payload = "{\"temperature\": " + String(temperature, 2) + ", \"humidity\": " + String(humidity, 2) + "}";

  Serial.print("Sending data to CoAP server: ");
  Serial.println(payload);

  // Add PSK to the payload for authentication
  String authenticatedPayload = "{\"psk\": \"" + String(psk_key) + "\", \"data\": " + payload + "}";

  coap.put(coap_server, authenticatedPayload.c_str());
}

// Function to send alerts via CoAP
void sendAlert(String message) {
  String alertPayload = "{\"psk\": \"" + String(psk_key) + "\", \"alert\": \"" + message + "\"}";

  Serial.print("Sending alert to CoAP server: ");
  Serial.println(alertPayload);

  coap.put(coap_alert_server, alertPayload.c_str());
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  setup_wifi();

  coap.start();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Check temperature thresholds and send alerts if necessary
  if (temperature > MAX_TEMP_THRESHOLD) {
    sendAlert("Temperature exceeds maximum threshold: " + String(temperature) + "°C");
  } else if (temperature < MIN_TEMP_THRESHOLD) {
    sendAlert("Temperature below minimum threshold: " + String(temperature) + "°C");
  }

  // Send temperature and humidity data
  sendTemperatureData(temperature, humidity);
  delay(60000);  // Send data every 60 seconds
}
