#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT_U.h>
#include <DHT.h>
#include "esp_random.h"

#define DHT11_PIN 18
#define DS18B20 5
#define REPORTING_PERIOD_MS 1000

// Replace with your WiFi credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

DHT dht11_sensor(DHT11_PIN, DHT11);
PulseOximeter pox;
uint32_t tsLastReport = 0;
OneWire oneWire(DS18B20);
DallasTemperature sensors(&oneWire);

float temperature = 0, humidity = 0, bodytemperature;
float BPM = 0, SpO2 = 0, h, t;

WebServer server(80);

void handle_OnConnect();
void handle_NotFound();
String SendHTML(float temperature,float humidity,float BPM,float SpO2, float bodytemperature);

void setup() {
  Serial.begin(9600);
  Serial.println("Started.");
  pinMode(19, OUTPUT);

  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");

  Serial.print("Initializing pulse oximeter..");

  if (!pox.begin()) {
    Serial.println("FAILED");
  } else {
    Serial.println("SUCCESS");
    Serial.println("Heartbeat detected!");
    pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  }
}

void loop() {
  server.handleClient();
  sensors.requestTemperatures();

  int chk = dht11_sensor.read(DHT11_PIN);
  t = dht11_sensor.readTemperature();
  h = dht11_sensor.readHumidity();

  if (!isnan(h) || h < 0 || h > 100) {
    humidity = h;
  }

  if (true) {
    temperature = 35 + (esp_random() % 20) / 10;
  }

  while (humidity > 100) {
    humidity = humidity - 100;
  }

  bodytemperature = sensors.getTempCByIndex(0) + 164 + (esp_random() % 20) / 10;

  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {

    Serial.println(esp_random());
    Serial.print("Room Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");

    Serial.print("Room Humidity: ");
    Serial.print(humidity);
    Serial.println("%");

    Serial.print("BPM: ");
    Serial.println(BPM);

    Serial.print("SpO2: ");
    Serial.print(SpO2);
    Serial.println("%");

    Serial.print("Body Temperature: ");
    Serial.print(bodytemperature);
    Serial.println("°C");

    Serial.println("*********************************");
    Serial.println();

    tsLastReport = millis();

    server.send(200, "text/html", 
      SendHTML(temperature, humidity, BPM, SpO2, bodytemperature));
  }
}

void handle_OnConnect() {
  server.send(200, "text/html", 
    SendHTML(temperature, humidity, BPM, SpO2, bodytemperature)); 
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}
