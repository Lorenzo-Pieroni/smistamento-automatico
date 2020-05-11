#include "Motor.h"
#include<ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "SSID";
const char* password = "Password";
const char* host = "192.168.1.25";
String api_key = "Dhksgj98RhjsR342Hdr65dsgh6";

int id = 0;
int courier = 0;
String cap = "00000";
int peso = 0;
int lastId = -1;

#define motorPinA1 0
#define motorPinB1 2
#define motorPinC1 4
#define motorPinD1 5
#define motorPinA2 12
#define motorPinA3 13
#define motorPinA4 14

oneWayMotor motor1 = oneWayMotor(motorPinA2, HIGH, LOW);
oneWayMotor motor2 = oneWayMotor(motorPinA3, HIGH, LOW);
oneWayMotor motor3 = oneWayMotor(motorPinA4, HIGH, LOW);
Motor motor4 = Motor(motorPinA1, motorPinB1, motorPinC1, motorPinD1, HIGH, LOW);
void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting..");
  }

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  request();
  lastId = id;
  motor4.Stop();
  motor1.Off();
  motor2.Off();
  motor3.Off();
}

void submit(int id) {
  Serial.print("connecting to ");
  Serial.println(host); // Use WiFiClient class to create TCP connections
  WiFiClient client;
  int httpPort = 83;
  if (!client.connect(host, httpPort))
  {
    Serial.println("connection failed");
    return;
  }
  Serial.print("Requesting URL: ");
  String postData = "api_key=" + api_key + "&id=" + String(id);
  String address = "http://" + (String)host + ":83/insert.php";
  Serial.println(address);
  HTTPClient http;
  http.begin(address);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  auto httpCode = http.POST(postData);
  //Serial.println(httpCode); //Print HTTP return code
  //String payload = http.getString();
  //Serial.println(payload); //Print request response payload
  http.end(); //Close connection
  Serial.println("closing connection");
  delay(1000);
}
void request() {
  Serial.print("connecting to ");
  Serial.println(host); // Use WiFiClient class to create TCP connections
  WiFiClient client;
  int httpPort = 83;
  if (!client.connect(host, httpPort))
  {
    Serial.println("connection failed");
    return;
  }
  Serial.print("Requesting URL: ");
  String postData = "api_key=" + api_key;
  String address = "http://" + (String)host + ":83/request.php";
  Serial.println(address);
  HTTPClient http;
  http.begin(address);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  auto httpCode = http.POST(postData);
  //Serial.println(httpCode); //Print HTTP return code
  String dataPackage = http.getString();
  Serial.println(dataPackage); //Print request response payload
  http.end(); //Close connection
  Serial.println("closing connection");
  int ind1 = dataPackage.indexOf('-');
  id = dataPackage.substring(0, ind1).toInt();
  int ind2 = dataPackage.indexOf('-', ind1 + 1 );
  courier = dataPackage.substring(ind1 + 1, ind2).toInt();
  int ind3 = dataPackage.indexOf('-', ind2 + 1 );
  cap = dataPackage.substring(ind2 + 1, ind3);
  peso = dataPackage.substring(ind3 + 1).toInt();
  Serial.println("CAP:" + cap + "ID:" + id + "CORRIERE:" + courier + "PESO:" + peso);
  delay(1000);
}

void move() {
  if (id != lastId) {
    lastId = id;
    switch (courier) {
      case 1:
        motor1.On();
        delay(5000);
        motor1.Off();
        delay(1000);
        motor4.Right();
        delay(5000);
        motor4.Stop();
        motor2.On();
        delay(5000);
        motor2.Off();
        break;
      case 2:
        motor1.On();
        delay(5000);
        motor1.Off();
        delay(1000);
        motor4.Left();
        delay(5000);
        motor4.Stop();
        motor3.On();
        delay(5000);
        motor3.Off();
        break;
    }
  }
  submit(id);
}

void loop() {
  request();
  move();
}
