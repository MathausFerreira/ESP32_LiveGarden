//1. Include WiFi.h
#include <WiFi.h>

//2. Include Firebase ESP32 library (this library)
#include "FirebaseESP32.h"

//3. Declare the Firebase Data object in the global scope
FirebaseData firebaseData;

String path = "/livegarden-514ff";
#define FIREBASE_HOST "livegarden-514ff.firebaseio.com" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "7TtblK1IRMb5WlcZDGv0YchzqIp99BoZQrreZygM"

char WIFI_SSID[] = "VERO - Casa";
char WIFI_PASSWORD[] = "Eng3nh@r1@";

WiFiServer server(80);

// Current color values
int redValue = 0;
int greenValue = 0;
int blueValue = 0;

void setup() {
  //Inicializa o monitor Serial
  Serial.begin(115200);

  //Estabelece a comunicação WiFi do ESP32
  connectWifi(WIFI_SSID, WIFI_PASSWORD);

  // Conectando ao Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //  if (!Firebase.beginStream(firebaseData, path + "/control"))
  //    Serial.println(firebaseData.errorReason());
  //
  //  Firebase.set(firebaseData, path + "/control/cmd", "idle");

  //  server.begin();
  //  Serial.println(" SERVER STARTED");

// DELETE SOME NODE
// Firebase.deleteNode(firebaseData, "/green");
}


void loop() {
  if (Firebase.getInt(firebaseData, "/red")) 
  {
    if (firebaseData.dataType() == "int") 
    {
      Serial.println(firebaseData.intData());
    }
  }else
  {
    Serial.println(firebaseData.errorReason());
  }


}


void setLedColor() {
  Serial.print(blueValue);
  Serial.print("  ");
  Serial.print(greenValue);
  Serial.print("  ");
  Serial.print(redValue);
  Serial.println("  ");
}

void connectWifi(char ID[], char PASS[])
{
  Serial.print("Connecting to : ");
  Serial.println(ID);

  WiFi.begin(ID, PASS);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(" .");
  }
  Serial.println("");
  Serial.println("Wifi connected");
  Serial.println("IP Adress : ");
  Serial.println(WiFi.localIP());
}
