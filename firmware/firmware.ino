#include "config.h"
#include "RCOutlet.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServerSecure.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>

RCOutlet rco(13);
BearSSL::ESP8266WebServerSecure server(443);
//ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  if(!LittleFS.begin()) {
    Serial.println("[ERR] Could not initialize file system");
  }

  
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PSK);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.printf("\nConnected, IP: ");
  Serial.println(WiFi.localIP());


  server.getServer().setRSACert(
    new BearSSL::X509List(SERVER_CERT),
    new BearSSL::PrivateKey(SERVER_KEY)
  );
  server.enableCORS(true);

  server.on("/", []() {
    server.send(200, "text/plain", "Hello World!");
  });

  server.on("/switch/a/on", []() {
    if (server.method() != HTTP_POST) {
      // Method Not Allowed
      server.send(405, "text/plain",
        ESP8266WebServerSecure::responseCodeToString(405));
    }

    rco.switchA(true);
    server.send(200, "text/plain", "ON");
  });

  server.on("/switch/a/off", []() {
    if (server.method() != HTTP_POST) {
      // Method Not Allowed
      server.send(405, "text/plain",
        ESP8266WebServerSecure::responseCodeToString(405));
    }

    rco.switchA(false);
    server.send(200, "text/plain", "OFF");
  });

  server.serveStatic("/static", LittleFS, "/", NULL);

  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}
