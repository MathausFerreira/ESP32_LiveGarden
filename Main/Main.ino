#include <WiFi.h>

//2. Include Firebase ESP32 library (this library)
#include "FirebaseESP32.h"

#define FIREBASE_HOST "livegarden-514ff.firebaseio.com"  //Do not include https: in FIREBASE_HOST
#define FIREBASE_AUTH "7TtblK1IRMb5WlcZDGv0YchzqIp99BoZQrreZygM"

//3. Declare the Firebase Data object in the global scope
FirebaseData firebaseData;

char WIFI_SSID[]     = "VERO - Casa";
char WIFI_PASSWORD[] = "Eng3nh@r1@";

String dbPath   = "/livegarden-514ff";
String userID = "7aE2fDGsy3hLgb7QsEULSJKmLyp1";
String plantID = "1";
String plantPath = "/users/" + userID + "/Plant/" + plantID + "/";

const int saida1 = 19;
const int saida2 = 18;

bool swState = false;

//WiFiServer server(80);

// Current color values
int redValue   = 0;
int greenValue = 0;
int blueValue  = 0;

struct preset_time_t
{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int duration;
  int state;
  int pump_index;
  int active;
  int inactive;
};

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
  Serial.println();
}

void connectFirebase(char HOST[], char AUTH[], FirebaseData &data)
{
  // Conectando ao Firebase
  Firebase.begin(HOST, AUTH);
  Firebase.reconnectWiFi(true);
  
  if (!Firebase.beginStream(data, dbPath + plantPath))
  {
    Serial.println(" Não foi possível Comunicar !");
    Serial.println("MOTIVO:  " + data.errorReason());
    Serial.println();
  }
  Firebase.set(data, dbPath + plantPath, "idle");
  //Firebase.setStreamCallback(firebaseData1, streamCallback, streamTimeoutCallback);
//  server.begin();
  Serial.println(" SERVER STARTED");
  Serial.println( );
}

void streamCallback(StreamData data)
{
  if (data.dataType() == "boolean") {
    if (data.boolData())
      Serial.println("Set " + dbPath + plantPath + " to High");
    else
      Serial.println("Set " + dbPath + plantPath + " to Low");
//    digitalWrite(ledPin, data.boolData());
  }
}

void streamTimeoutCallback(bool timeout)
{
  if (timeout)
  {
    Serial.println();
    Serial.println("Stream timeout, resume streaming...");
    Serial.println();
  }
}

void setup() {
  //Inicializa o monitor Serial
  Serial.begin(115200);

  //Estabelece a comunicação WiFi do ESP32
  connectWifi(WIFI_SSID, WIFI_PASSWORD);

  // Conectando ao Firebase
 connectFirebase(FIREBASE_HOST,  FIREBASE_AUTH, firebaseData);
  // Conectando ao Firebase
//  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
//  Firebase.reconnectWiFi(true);
//  
//  if (!Firebase.beginStream(firebaseData, dbPath + plantPath))
//  {
//    Serial.println(" Não foi possível Comunicar !");
//    Serial.println("MOTIVO:  " + firebaseData.errorReason());
//    Serial.println();
//  }
//  Firebase.set(firebaseData, dbPath + plantPath, "idle");
//  //Firebase.setStreamCallback(firebaseData1, streamCallback, streamTimeoutCallback);
////  server.begin();
//  Serial.println(" SERVER STARTED");
//  Serial.println( );
//
//  if (Firebase.pathExist(firebaseData, dbPath + plantPath))
//  {
//    Serial.println("Path Encontrado no Firebase");
//    Serial.println();
//  }
  // DELETE SOME NODE
  // Firebase.deleteNode(firebaseData, "/green");
}


void loop() {
  if (Firebase.getInt(firebaseData, plantPath+"TimeToRotate"))
  {
    if (firebaseData.dataType() == "int")
    {
      Serial.println(firebaseData.intData());
    }
  } else
  {
    Serial.println(firebaseData.errorReason());
    Serial.println(dbPath + plantPath+"TimeToRotate");
  }
}
