#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// LED GPIO pins
#define LED1 12
#define LED2 13
#define LED3 14
#define LED4 15

// Create web server on port 80
WebServer server(80);

void setup() {

  Serial.begin(115200);

  // Configure LED pins
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  // Turn all LEDs OFF initially
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");

  // Display ESP32 IP address
  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());

  // LED 1 routes
  server.on("/led1/on", []() {
    digitalWrite(LED1, HIGH);
    server.send(200, "text/plain", "LED1 ON");
  });

  server.on("/led1/off", []() {
    digitalWrite(LED1, LOW);
    server.send(200, "text/plain", "LED1 OFF");
  });

  // LED 2 routes
  server.on("/led2/on", []() {
    digitalWrite(LED2, HIGH);
    server.send(200, "text/plain", "LED2 ON");
  });

  server.on("/led2/off", []() {
    digitalWrite(LED2, LOW);
    server.send(200, "text/plain", "LED2 OFF");
  });

  // LED 3 routes
  server.on("/led3/on", []() {
    digitalWrite(LED3, HIGH);
    server.send(200, "text/plain", "LED3 ON");
  });

  server.on("/led3/off", []() {
    digitalWrite(LED3, LOW);
    server.send(200, "text/plain", "LED3 OFF");
  });

  // LED 4 routes
  server.on("/led4/on", []() {
    digitalWrite(LED4, HIGH);
    server.send(200, "text/plain", "LED4 ON");
  });

  server.on("/led4/off", []() {
    digitalWrite(LED4, LOW);
    server.send(200, "text/plain", "LED4 OFF");
  });

  // Start web server
  server.begin();

  Serial.println("Web server started!");
}

void loop() {

  // Handle incoming HTTP requests
  server.handleClient();
}
