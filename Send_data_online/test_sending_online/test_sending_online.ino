#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTPIN 4 

const char* ssid = "OnePlus 8T";
const char* password = "w9vfcqrm";
const char* serverURL = "http://www.hh3dlab.fi/dataduelist/iotwrite.php"; // URL to your PHP file
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
    String deviceName = "DATA DUELIST"; // Replace with your team name
    //String postData = "temperature=" + String(temperature) + "&device=" + deviceName;
    String postData = "MOIKKULIIIIIIIII";



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
