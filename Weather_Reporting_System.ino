#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

WiFiClient client;

//HTML webpage in form of h file
#include "index.h" 

// DHT Sensor Setup
#include "DHTesp.h"
#define DHTpin 02
DHTesp dht;

// RainDrop Sensor Setup

const int raindropPin = A0;

//wifi ssid and password
const char* ssid = "Xiaomi_73AD";
const char* password = "Aswaljc26c";

ESP8266WebServer server(80); //server on port 80

void handleRoot(){
  String s = MAIN_page; //reads HTML Contents
  server.send(200,"text/html",s); //send web page
}

void handleADC(){
  //DHT SENSOR CODE

  int rain = analogRead(A0);
  float humidity = dht.getHumidity();
  float temp = dht.getTemperature();

  String data = "{\"Rain\":\""+String(rain)+"\", \"Temperature\":\""+ String(temp) +"\", \"Humidity\":\""+ String(humidity) +"\"}";
  server.send(200, "text/plane", data);
  Serial.println("Humidity: ");
  Serial.print(humidity);

  Serial.println("  Temperature: ");
  Serial.print(temp);
  Serial.print("'C");

  Serial.println("  Rain: ");
  Serial.print(rain);
  Serial.print("%");
}


void setup() {
 Serial.begin(9600);
 Serial.println();

 dht.setup(DHTpin, DHTesp::DHT11); 

  
WiFi.begin(ssid, password); //Connect to your WiFi router
Serial.println("");
 
// Wait for connection
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
 
//If connection successful show IP address in serial monitor
Serial.println("");
Serial.print("Connected to ");
Serial.println(ssid);
Serial.print("IP address: ");
Serial.println(WiFi.localIP()); //IP address assigned to your ESP

server.on("/", handleRoot); //Which routine to handle at root location. This is display page
server.on("/readADC", handleADC); //This page is called by java Script AJAX
 
server.begin(); //Start server
Serial.println("HTTP server started");
}

void loop(){
  server.handleClient(); //Handle client requests
}
