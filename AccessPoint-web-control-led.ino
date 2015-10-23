#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

/*-- Set SSID, Password and IP --*/
const char *ssid = "test-esp8266"; //config ssid
const char *password = "12345678"; //config password
const byte wifi_ip[4] = {192, 168, 1, 2}; //config ipaddress of access point
const byte wifi_subnet[4] = {255, 255, 255, 0}; //config sumnet mask of access point
const byte wifi_gateway[4] = {192, 168, 1, 1}; //config gateway of access point

/*-- Create server port 80 --*/
ESP8266WebServer server(80);

/*-- http://ip_address/ --*/
void root() {
  server.send(200, "text/html", "<h1>Hello World :)</h1><br/>");
}

/*-- http://ip_address/led --*/
void led(){
  if(server.arg("set")=="1"){
    digitalWrite(BUILTIN_LED, LOW); // LED ON
    server.send(200, "text/html", "<h1>LED: ON</h1><br/>");
  }else if(server.arg("set")=="0"){
    digitalWrite(BUILTIN_LED, HIGH); // LED OFF
    server.send(200, "text/html", "<h1>LED: OFF</h1><br/>");
  }
}

void setup() {
  /*-- Initial pin output --*/
  pinMode(BUILTIN_LED, OUTPUT);
  

  /*-- Config wifi ---*/
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(
    IPAddress(wifi_ip[0], wifi_ip[1], wifi_ip[2], wifi_ip[3]),
    IPAddress(wifi_gateway[0], wifi_gateway[1], wifi_gateway[2], wifi_gateway[3]),
    IPAddress(wifi_subnet[0], wifi_subnet[1], wifi_subnet[2], wifi_subnet[3])
  );

  /*-- Handle url request --*/
  server.on("/", root); // http://ip_address/
  server.on("/led", HTTP_GET, led); // http://ip_address/led

  /*-- Server start --*/
  server.begin();
}

void loop() {
  server.handleClient();
}
