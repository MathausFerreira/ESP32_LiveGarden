#include <WiFi.h>
#include "Thread.h"
#include "ThreadController.h"
#include "FirebaseESP32.h" //2. Include Firebase ESP32 library (this library)

// ================================ FIREBASE ==================================
FirebaseData firebaseData; // Declare the Firebase Data object in the global scope

char FIREBASE_HOST[] = "livegarden-514ff.firebaseio.com";  //Do not include https: in FIREBASE_HOST
char FIREBASE_AUTH[] = "7TtblK1IRMb5WlcZDGv0YchzqIp99BoZQrreZygM";

String dbPath    = "/livegarden-514ff";
String userID    = "7aE2fDGsy3hLgb7QsEULSJKmLyp1";
String plantID   = "1";
String plantPath = "/users/" + userID + "/Plant/" + plantID + "/";

// =================================== WIFI =====================================
char WIFI_SSID[]     = "VERO - Casa";
char WIFI_PASSWORD[] = "Eng3nh@r1@";

// ============================== Threads ======================================

void Function_thread1(){
   JSON(firebaseData, plantPath);
}

void Function_thread2(){
    Serial.println(userName(firebaseData, plantPath));
}

ThreadController cpu;

Thread threadF1;
Thread threadF2;

// =====================================================================================
void connectWifi(char ID[], char PASS[]) {
  Serial.print("Connecting to : ");
  Serial.println(ID);

  WiFi.begin(ID, PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(" .");
  }
  Serial.println("");
  Serial.println("Wifi connected");
  Serial.println("IP Adress : ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void connectFirebase(char HOST[], char AUTH[], FirebaseData &data) {
  // Conectando ao Firebase
  Firebase.begin(HOST, AUTH);
  Firebase.reconnectWiFi(true);

  if (!Firebase.beginStream(data, dbPath + plantPath))  {
    Serial.println("Não foi possível Comunicar !");
    Serial.println("MOTIVO:  " + data.errorReason());
    Serial.println();
  }

  Firebase.set(data, dbPath + plantPath, "idle");
  Serial.println(" SERVER STARTED");
  Serial.println( );
}

void setup() {
  threadF1.setInterval(5000);
  threadF1.onRun(Function_thread1);
  
  threadF2.setInterval(2500);
  threadF2.onRun(Function_thread2);

  cpu.add(&threadF1);
  cpu.add(&threadF2);


  
  //Inicializa o monitor Serial
  Serial.begin(115200);

  //Estabelece a comunicação WiFi do ESP32
  connectWifi(WIFI_SSID, WIFI_PASSWORD);

  // Conectando ao Firebase
  connectFirebase(FIREBASE_HOST, FIREBASE_AUTH, firebaseData);
}

void loop() {

  cpu.run();
//  int TimeToRotate = timeToRotate(firebaseData, plantPath);
//  Serial.println(TimeToRotate);


}

void JSON(FirebaseData  &data, String plantPath) {
  if (Firebase.getJSON(data, plantPath)) {
    Serial.println(data.jsonString());
  } else {
    //Failed to get JSON data at defined database path, print out the error reason
    Serial.println(data.errorReason());
  }
}

String userName(FirebaseData &data, String plantPath) {
  if (Firebase.getString(data, plantPath + "Name")) {
    if (data.dataType() == "string") {
      return (data.stringData());
    }
  } else {
    Serial.println(data.errorReason());
  }
}

int timeToRotate(FirebaseData &data, String plantPath) {
  if (Firebase.getInt(data, plantPath + "TimeToRotate"))  {
    if (data.dataType() == "int") {
      return (data.intData());
    }
  } else {
    Serial.println(data.errorReason());
  }
}
