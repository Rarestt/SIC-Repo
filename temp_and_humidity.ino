#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// Constants
#define DEBUG_ESP_HTTP_CLIENT
#define DHTPIN 13     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);

// WiFi credentials
const char* ssid = "Router 3";
const char* password = "Dita01792";
const char* serverName = "http://192.168.1.62:5000/data";

// Variables
float hum;  // Stores humidity value
float temp; // Stores temperature value

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
  dht.begin();
}

void loop() {
  delay(2000);
  
  // Read data and store it to variables hum and temp
  hum = dht.readHumidity();
  temp = dht.readTemperature();

  // Print temp and humidity values to serial monitor
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print(" %, Temp: ");
  Serial.print(temp);
  Serial.println(" Celsius");

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    String httpRequestData = "{\"temperature\":" + String(temp) + ", \"humidity\":" + String(hum) + "}";
    int httpResponseCode = http.POST(httpRequestData);
    
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
  
  delay(10000); // Delay 10 sec.
}
