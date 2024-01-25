#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTPIN 4 

const char* ssid = "Spottaa kissa";
const char* password = "ripuli123";
const char* serverURL = "http://www.hh3dlab.fi/farmdata/receive.php"; // URL to your PHP file
#define DHTTYPE DHT11   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("DHTxx test!");

    dht.begin();
}

void loop() {
    float temperature = readTemperature(); // Replace with your temperature reading logic
    String deviceName = "Vessatiimi"; // Replace with your team name
    String postData = "temperature=" + String(temperature) + "&device=" + deviceName;



    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int httpResponseCode = http.POST(postData);
    if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println(response);
    } else {
        Serial.println("Error sending request");
    }

    http.end();
    delay(10000); // Send data every tem seconds (adjust as needed)
}

float readTemperature() {
      float t = dht.readTemperature();
    // Implement your temperature sensor reading code here
    // Replace this with your sensor library or logic
    return t; // Dummy value
}
