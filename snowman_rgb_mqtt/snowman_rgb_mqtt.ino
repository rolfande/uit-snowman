#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "snowman_secrets.h"

int pinRed = 12;
int pinGreen = 4;
int pinBlue = 13;

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

char mqtt_user[] = SECRET_MQTT_USER;
char mqtt_pass[] = SECRET_MQTT_PASS;

const char* mqttServer = SECRET_SERVER_URL;
const int mqttPort = 1883;
WiFiClient  wifiClient;
PubSubClient client(wifiClient);

void setup() {
  
  Serial.begin(115200);
  delay(10);
  Serial.println("Starting Snowman RGB MQTT");
  pinMode(pinRed,OUTPUT);
  pinMode(pinGreen,OUTPUT);
  pinMode(pinBlue,OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);

  // Connect to WiFi
  connectWifi();
  // Connect to MQTT
  connectMqtt();
}

void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  String message;
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    message += (char)payload[i];
  }
  Serial.println();
  Serial.println("-----------------------");

  setColor(message);
 
}

// List of CheerLights color names
String colorName[] = {"off","red","green","blue","cyan","white","magenta","yellow"};

// Map of RGB values for each of the Cheerlight color names
int colorRGB[][3] = {     0,  0,  0,  // "off"
                          1,  0,  0,  // "red"
                          0,  1,  0,  // "green"
                          0,  0,  1,  // "blue"
                          0,  1,  1,  // "cyan",
                          1,  1,  1,  // "white",
                          1,  0,  1,  // "magenta",
                          1,  1,  0}; // "yellow",

void setColor(String color)
{
  // Look through the list of colors to find the one that was requested
  for(int iColor = 0; iColor <= 7; iColor++)
  {
    if(color == colorName[iColor])
    {
      // When it matches, look up the RGB values for that color in the table,
      // and write the red, green, and blue values.

      digitalWrite(pinRed,colorRGB[iColor][0]);
      digitalWrite(pinGreen,colorRGB[iColor][1]);
      digitalWrite(pinBlue,colorRGB[iColor][2]);

      return;
    }
  }
}


void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost. Reconnecting...");
    connectWifi();
  }
  if (!client.connected()) {
    digitalWrite(LED_BUILTIN, HIGH);
    connectMqtt();
    digitalWrite(LED_BUILTIN, LOW);
  }

  // Check for incoming messages from MQTT server regularly
  client.loop();
  
  // Wait 5 seconds before next check
  delay(5000);
}

void connectWifi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(2000);
    Serial.println("Connecting to WiFi...");
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }
  Serial.println();
  Serial.print("Connected to SSID: ");
  Serial.print(ssid);
  Serial.print(". IP-address: ");
  Serial.print(WiFi.localIP());
  Serial.print(" / MAC-address: ");
  Serial.println(WiFi.macAddress());
}

void connectMqtt() {
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
  
    if (client.connect("snowman", mqtt_user, mqtt_pass)) {
  
      Serial.print("Listening to MQTT-server ");
      Serial.println(mqttServer);
  
    } else {
      Serial.print("failed with state ");
      Serial.println(client.state());
      delay(2000);
    }
  }
  client.subscribe("snowmancolor");
}
