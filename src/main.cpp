#include <WiFi.h>
#include <HttpClient.h>

// Replace with your WiFi credentials
const char* ssid = "iPhone";
const char* password = "pablo2003";

// AWS server settings
const char* server = "18.223.170.211";  // Your EC2 public IP
int port = 5000;                        // Flask default port
const char* path = "/?var=10";          // Endpoint path

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.print("Connecting to WiFi: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    // Wait until connected
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWiFi connected successfully.");
    Serial.print("Local IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    WiFiClient wifi;
    HttpClient client(wifi);  // Use the 1-argument constructor

    Serial.println("\n--- Start of Loop ---");

    // Make GET request
    int err = client.get(server, port, path);

    if (err == 0) {
        int statusCode = client.responseStatusCode();
        Serial.print("Response status: ");
        Serial.println(statusCode);

        Serial.print("HTTP Response Body: ");
        while (client.available()) {
            char c = client.read();
            Serial.print(c);
        }
        Serial.println();
    } else {
        Serial.print("Connection failed. Error: ");
        Serial.println(err);
    }

    client.stop();
    delay(5000); // Wait 5 seconds
}
