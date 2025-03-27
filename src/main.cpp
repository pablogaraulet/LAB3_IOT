#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <WiFi.h>
#include <HttpClient.h>

// WiFi credentials
const char *ssid = "iPhone";
const char *password = "pablo2003";

// Server configuration
const char *server = "18.223.170.211";
int port = 5000;

Adafruit_AHTX0 aht;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  // Initialize I2C on GPIO21 (SDA) and GPIO22 (SCL)
  Wire.begin(21, 22);
  delay(100); // <- short delay may help initialization

  // Explicitly pass the Wire object
  if (!aht.begin(&Wire)) {
    Serial.println("Could not find AHT20/DHT20 sensor. Check wiring!");
    while (1) delay(10);
  }
  Serial.println("Sensor initialized successfully.");
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);  // Get temperature and humidity data

  float t = temp.temperature;
  float h = humidity.relative_humidity;

  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print(" °C  | Humidity: ");
  Serial.print(h);
  Serial.println(" %");

  // Build request path
  String url = "/?temp=" + String(t, 1) + "&hum=" + String(h, 1);
  WiFiClient wifi;
  HttpClient client(wifi);
  int err = client.get(server, port, url.c_str());

  if (err == 0) {
    Serial.print("Response: ");
    while (client.available()) {
      char c = client.read();
      Serial.print(c);
    }
    Serial.println();
  } else {
    Serial.print("Request failed, error: ");
    Serial.println(err);
  }

  client.stop();
  delay(5000);
}
