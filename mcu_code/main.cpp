#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80); // Web server on port 80

const int pwm_signal = D4;
const int yellow = D8;
const int red = D3;
const int green = D1;

const char* ssid = "PWM Fan Controller";
const char* password = "12345678";

void setup() {
  WiFi.softAP(ssid, password);
  Serial.begin(9600);
  analogWriteFreq(25000); // 25kHz typical for PWM fans
  analogWriteRange(255); // 8-bit resolution

  analogWrite(pwm_signal, 5);
  analogWrite(yellow, 0);
  analogWrite(red, 0);
  analogWrite(green, 0);

  // 5 pulse
  server.on("/5", HTTP_GET, []() {
    server.send(200, "text/html", getHTML());
    analogWrite(pwm_signal, 5);
    analogWrite(green, 50);
    analogWrite(yellow, 0);
    analogWrite(red, 0);
    Serial.println("1_pulse");
  });

  // 140 pulse
  server.on("/140", HTTP_GET, []() {
    server.send(200, "text/html", getHTML());
    analogWrite(pwm_signal, 140);
    analogWrite(green, 0);
    analogWrite(yellow, 200);
    analogWrite(red, 0);
    Serial.println("25_pulse");
  });

  // 245 pulse
  server.on("/245", HTTP_GET, []() {
    server.send(200, "text/html", getHTML());
    analogWrite(pwm_signal, 245);
    analogWrite(yellow, 0);
    analogWrite(green, 0);
    analogWrite(red, 200);
    Serial.println("50_pulse");
  });
  
  // Start the server
  server.begin();
}

String getHTML() {
  String ptr = "<!DOCTYPE html> <html>\n";
  return ptr;
}

void loop() {
    server.handleClient();
}
