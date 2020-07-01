#include "FirebaseESP32.h" //2. Include Firebase ESP32 library (this library)

class FirebaseCodeM {
  private:

  public:
    // ===================================== FIREBASE =======================================
    FirebaseData firebaseData; // Declare the Firebase Data object in the global scope
    //FirebaseJson json;
    //FirebaseJsonData jsonData;

    String FIREBASE_HOST = "livegarden-514ff.firebaseio.com";  //Do not include https: in FIREBASE_HOST
    String FIREBASE_AUTH = "7TtblK1IRMb5WlcZDGv0YchzqIp99BoZQrreZygM";

    String dbPath    = "/livegarden-514ff";
    String userID    = "RzDlCYsuvPUqsi1Tk5i62nyRaZj2";
    String plantID   = "-MAmcIoXh3G8ZtnxaRDi";
    String plantPath = "/users/" + userID + "/Plant/" + plantID + "/";

    // ======================================================================================

    void connectFirebase() {
      // Conectando ao Firebase
      Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
      Firebase.reconnectWiFi(true);

      if (!Firebase.beginStream(firebaseData, dbPath + plantPath))  {
        Serial.println("Não foi possível Comunicar !");
        Serial.println("MOTIVO:  " + firebaseData.errorReason());
        Serial.println();
      }

      Firebase.set(firebaseData, dbPath + plantPath, "idle");
      Serial.println(" SERVER STARTED");
      Serial.println( );
    }

    void JSON() {
      if (Firebase.getJSON(firebaseData, plantPath)) {
        Serial.println(firebaseData.jsonString());
      } else {
        //Failed to get JSON data at defined database path, print out the error reason
        Serial.println(firebaseData.errorReason());
      }
    }

    // =================================== Strings ==============================================
    String plantName() {
      if (Firebase.getString(firebaseData, plantPath + "Name")) {
        if (firebaseData.dataType() == "string") {
          return (firebaseData.stringData());
        }
      } else {
        Serial.println(firebaseData.errorReason());
      }
    }
    String plantNotes() {
      if (Firebase.getString(firebaseData, plantPath + "Notes")) {
        if (firebaseData.dataType() == "string") {
          return (firebaseData.stringData());
        }
      } else {
        Serial.println(firebaseData.errorReason());
      }
    }
    String plantSpecies() {
      if (Firebase.getString(firebaseData, plantPath + "Species")) {
        if (firebaseData.dataType() == "string") {
          return (firebaseData.stringData());
        }
      } else {
        Serial.println(firebaseData.errorReason());
      }
    }
    String avatarGender() {
      if (Firebase.getString(firebaseData, plantPath + "AvatarGender")) {
        if (firebaseData.dataType() == "string") {
          return (firebaseData.stringData());
        }
      } else {
        Serial.println(firebaseData.errorReason());
      }
    }
    String autoRotate() {
      if (Firebase.getBool(firebaseData, plantPath + "AutoRotate"))  {
        if (firebaseData.dataType() == "string") {
          return (firebaseData.stringData());
        }
      } else {
        Serial.println(firebaseData.errorReason());
      }
    }
    String iteration() {
      if (Firebase.getString(firebaseData, plantPath + "Iteration"))  {
        if (firebaseData.dataType() == "string") {
          return (firebaseData.stringData());
        }
      } else {
        Serial.println(firebaseData.errorReason());
      }
    }
    // =================================== Bolean ===============================================

    // =================================== Inteiros =============================================
    
    int ONOFF() {
      if (Firebase.getInt(firebaseData, plantPath + "ONOFF"))  {
        if (firebaseData.dataType() == "int") {
          return (firebaseData.intData());
        }
      } else {
        Serial.println(firebaseData.errorReason());
      }
    }
    
    int timeToRotate() {
      if (Firebase.getInt(firebaseData, plantPath + "TimeToRotate"))  {
        if (firebaseData.dataType() == "int") {
          return (firebaseData.intData());
        }
      } else {
        Serial.println(firebaseData.errorReason());
      }
    }

    int plantAge() {
      if (Firebase.getInt(firebaseData, plantPath + "Age"))  {
        if (firebaseData.dataType() == "int") {
          return (firebaseData.intData());
        }
      } else {
        Serial.println(firebaseData.errorReason());
      }
    }

    int iterationFrequency() {
      if (Firebase.getInt(firebaseData, plantPath + "IterationFrequency"))  {
        if (firebaseData.dataType() == "int") {
          return (firebaseData.intData());
        }
      } else {
        Serial.println(firebaseData.errorReason());
      }
    }
    // ======================================================================================================

    void FirebaseCodeSetup() {
      // Conectando ao Firebase
      connectFirebase();
    }

};

FirebaseCodeM Fb;
