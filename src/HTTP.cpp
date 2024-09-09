#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// Wi-Fi credentials
const char* ssid = "HomeNetwork";
const char* password = "SuperSecret123";

// AWS IoT HTTP endpoint (Use a real endpoint)
const char* serverName = "https://iot.us-east-1.amazonaws.com/temperature";

// HTTP Bearer Token (real-like token)
const char* bearer_token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c";

// Initialize DHT sensor
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

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

// Function to send data to the cloud using HTTP POST with Bearer Token Authentication
void sendTemperatureData(float temperature, float humidity) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);  // AWS IoT HTTP endpoint

    // Add headers
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "Bearer " + String(bearer_token));  // Bearer Token Authentication

    // Create JSON payload
    String httpRequestData = "{\"temperature\": " + String(temperature, 2) + ", \"humidity\": " + String(humidity, 2) + "}";

    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0) {
      String response = http.getString();  // Get the response to the request
      Serial.println("HTTP Response code: " + String(httpResponseCode));
      Serial.println("Response: " + response);
    } else {
      Serial.println("Error on sending POST: " + String(httpResponseCode));
    }

    // Free resources
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  setup_wifi();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  sendTemperatureData(temperature, humidity);
  delay(60000);  // Send data every 60 seconds
}



