#include <WiFi.h>

class WifiCode {
  private:


  public:
//      char WIFI_SSID[]     ="VERO - Casa" ;
//    char WIFI_PASSWORD[] = ;

    void connectWifi() {
      Serial.print("Connecting to : ");
      Serial.println("VERO - Casa");

      WiFi.begin("VERO - Casa", "Eng3nh@r1@");

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



};
WifiCode Wf;
// =================================== WIFI =====================================
