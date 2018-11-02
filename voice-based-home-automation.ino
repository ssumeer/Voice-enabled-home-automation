#Author = sumeer@unixindia.com

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define Relay1            12  //D6
#define Relay2            14  //D5
#define Relay3            4   //D2
#define Relay4            5   //D1

#define WLAN_SSID       "kavitha"             // Your SSID
#define WLAN_PASS       "powrnaMi05"        // Your password

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   
#define AIO_USERNAME    "sumeer"            // Replace it with your username
#define AIO_KEY         "012bb203dd7e49d3aa4e28891555a7d0"   // Replace with your Project Auth Key
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe Radio = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Relay1"); // FeedName //Light1 == Radio in adafruit
Adafruit_MQTT_Subscribe WashingMachine = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Relay2");
Adafruit_MQTT_Subscribe TV = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Relay3");
Adafruit_MQTT_Subscribe Fan = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Relay4");

void setup() {
  Serial.begin(115200);

  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);
  
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.mode(WIFI_STA);//newone
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
 

  // Setup MQTT subscription for onoff feed.
    mqtt.subscribe(&Radio);
    Serial.println("subcribed1");
    mqtt.subscribe(&WashingMachine);
    Serial.println("subcribed2");
    mqtt.subscribe(&TV);
    Serial.println("subcribed3");
    mqtt.subscribe(&Fan);
    Serial.println("subcribed4");
}



void loop() {
 
  mqtt.connect();
  

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
      if (subscription == &Radio) {
        Serial.print(F("Got: "));
        Serial.println((char *)Radio.lastread);
        uint16_t Radio_State = atoi((char *)Radio.lastread);
        digitalWrite(Relay1, Radio_State);
      
    }
      if (subscription == &WashingMachine) {
        Serial.print(F("Got: "));
        Serial.println((char *)WashingMachine.lastread);
        uint16_t WashingMachine_State = atoi((char *)WashingMachine.lastread);
        digitalWrite(Relay2, WashingMachine_State);
    }
      if (subscription == &TV) {
        Serial.print(F("Got: "));
        Serial.println((char *)TV.lastread);
        uint16_t TV_State = atoi((char *)TV.lastread);
        digitalWrite(Relay3, TV_State);
    }
      if (subscription == &Fan) {
        Serial.print(F("Got: "));
        Serial.println((char *)Fan.lastread);
        uint16_t Fan_State = atoi((char *)Fan.lastread);
        digitalWrite(Relay4, Fan_State);
      
    }
  }

  
}
