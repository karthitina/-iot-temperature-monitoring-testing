#include <WiFi.h>
#include <coap-simple.h>
#include <DHT.h>

// Wi-Fi credentials
const char* ssid = "HomeNetwork";
const char* password = "SuperSecret123";

// CoAP server address (use your own)
const char* coap_server = "coap://your-coap-server-address.com";

// Initialize DHT sensor
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

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

// Function to send temperature data via CoAP
void sendTemperatureData(float temperature, float humidity) {
  String payload = "{\"temperature\": " + String(temperature, 2) + ", \"humidity\": " + String(humidity, 2) + "}";
  
  Serial.print("Sending data to CoAP server: ");
  Serial.println(payload);

  coap.put(coap_server, payload.c_str());
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

  sendTemperatureData(temperature, humidity);
  delay(60000); // Send data every 60 seconds
}
