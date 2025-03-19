#include <WiFi.h>
#include <HttpClient.h>

// Configura tu WiFi
const char* ssid = "BLVD63";
const char* password = "sdBLVD63";

// Configuración de la API
const char kHostname[] = "worldtimeapi.org";
const char kPath[] = "/api/timezone/Europe/London.txt";

void setup() {
    Serial.begin(115200);
    delay(1000);

    // Conectar a WiFi
    Serial.print("Conectando a ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWiFi conectado");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    WiFiClient client;
    HttpClient http(client);

    Serial.println("Haciendo solicitud HTTP...");
    int err = http.get(kHostname, kPath);
    
    if (err == 0) {
        Serial.println("Solicitud iniciada con éxito");

        int statusCode = http.responseStatusCode();
        Serial.print("Código de estado: ");
        Serial.println(statusCode);

        if (statusCode == 200) {
            Serial.println("Respuesta recibida:");
            while (http.available()) {
                char c = http.read();
                Serial.print(c);
            }
        }
    } else {
        Serial.print("Error en la solicitud: ");
        Serial.println(err);
    }

    http.stop();
    delay(10000);  // Espera 10 segundos antes de la próxima solicitud
}
