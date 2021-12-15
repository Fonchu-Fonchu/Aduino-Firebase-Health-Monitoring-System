
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "health-monitoring-system-b5586-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "XawobPnM2TpJIlw83GBF5dsJHJ2YRdRIyXOfX9FD"
#define WIFI_SSID "Think123"
#define WIFI_PASSWORD "think1234"

float res = 3.3/1024;

void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

int n = 0;

void loop() {
  // set value
  float temp = (analogRead(A0)*res)*100;
  Firebase.setFloat("Temp", temp);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(10000);
  
  // update Temperature
  
  temp = (analogRead(A0)*res)*100;
  Firebase.setFloat("/info/Temp", temp);
  
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  // get value 
  Serial.print("Temp: ");
  Serial.println(Firebase.getFloat("Temp"));
  delay(1000);

  // remove value
  Firebase.remove("Temp");
  delay(1000);

  // set string value
  Firebase.setString("message", "Your Body Temperature");
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
  // set bool value
  Firebase.setBool("truth", false);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /truth failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  // append a new value to /logs
  String name = Firebase.pushInt("logs", n++);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /logs/");
  Serial.println(name);
  delay(1000);
}
