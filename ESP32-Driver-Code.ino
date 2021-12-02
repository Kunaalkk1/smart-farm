#include <WiFi.h>                                                
#include <IOXhop_FirebaseESP32.h>                                            
#define FIREBASE_HOST "webd-cbf4e-default-rtdb.firebaseio.com/"                        
#define FIREBASE_AUTH "FszOAta7ZM2A8miPEpdCAIs3ZP7C1Ibd2HijKwYY"                  
#define WIFI_SSID "YOUR-SSID"                                          
#define WIFI_PASSWORD "YOUR-PASS"              
#include "DHT.h"
#define DHTPIN  14    
#define DHTTYPE DHT11  
#define trigpin 13
#define echopin 12
#define acw 25 // Input 1: anticlockwise
#define cw 27 // Input 2: clockwise
int state;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(cw, OUTPUT);
  pinMode(acw, OUTPUT);
  digitalWrite(acw,LOW);
  digitalWrite(cw,LOW);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                    
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                                      
  dht.begin();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  state = Firebase.getInt("/in");
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  float duration = pulseIn(echopin, HIGH);
  float distance = (0.017 * duration);
  float l=30-distance;
  Serial.print("Water Level:");
  Serial.println(l);
  float h = dht.readHumidity()/2;
  float t = dht.readTemperature()/2;
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.println(state);
  if(state == 1){
    digitalWrite(cw, LOW);
    digitalWrite(acw, HIGH);
  }
  if(state == 0){
    digitalWrite(cw, HIGH);
    digitalWrite(acw, HIGH);
  }
  if(state == -1){
    digitalWrite(acw, LOW);
      digitalWrite(cw, HIGH);
  }
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.println(f);
  Firebase.setInt("/temp" , t);
  Firebase.setInt("/humid" , h);
  Firebase.setInt("/level", distance);
}
