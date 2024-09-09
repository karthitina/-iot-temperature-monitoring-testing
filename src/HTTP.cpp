#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// Wi-Fi credentials
const char* ssid = "HomeNetwork";             // Your Wi-Fi network name
const char* password = "SuperSecret123";      // Your Wi-Fi network password

// AWS IoT HTTP endpoint
// Replace with the actual AWS IoT endpoint for your region. Example format:
// "https://<your-endpoint>.iot.<region>.amazonaws.com"
// You can find this in your AWS IoT Core console under "Settings"
const char* serverName = "https://a3k7odshaiiot-ats.iot.us-east-1.amazonaws.com/temperature";

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

// Function to send data to the cloud using HTTP POST
void sendTemperatureData(float temperature, float humidity) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName); // AWS IoT HTTP endpoint
    
    // Add required headers (if any specific to your AWS IoT setup)
    http.addHeader("Content-Type", "application/json");
    
    // Create JSON payload
    String httpRequestData = "{\"temperature\": " + String(temperature, 2) + ", \"humidity\": " + String(humidity, 2) + "}";
    
    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
    
    if (httpResponseCode > 0) {
      String response = http.getString(); // Get the response to the request
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

void
