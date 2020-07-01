#include "WifiCode.h"
#include "FirebaseCodeM.h"

#include "Thread.h"
#include "ThreadController.h"

Thread threadF1;
Thread threadF2;
ThreadController cpu;

void Function_thread1() {
  //Thread para os atuadores

  Fb.ONOFF() == 1? Serial.println("LIGADO"):Serial.println("DESLIGADO");
  

}

void Function_thread2() {
  //Thread para os sensores
  
  Serial.println(Fb.plantName());
}

void ThreadsCodeSetup() {
  threadF1.setInterval(1000);
  threadF1.onRun(Function_thread1);

  threadF2.setInterval(10000);
  threadF2.onRun(Function_thread2);

  cpu.add(&threadF1);
  cpu.add(&threadF2);
}
void HelloMessage() {
  Serial.println("Hello, My name is " + Fb.plantName() + "! ");
  Serial.println("\n I am " + (String)Fb.plantAge() + " years old!");
  Serial.println("\n My Gender is: " + Fb.avatarGender());
  Serial.println("\n My Species is: " + Fb.plantSpecies());
  Serial.println("\n I was programmed to Interact: " + Fb.iteration()+ " with a frequency: " + (String)Fb.iterationFrequency());
  Serial.println("\n I was programmed to Rotate: " + Fb.autoRotate());
  Serial.println("\n I will Rotate: " + (String)Fb.timeToRotate()+ " times a day. ");
  Serial.println("\n In my register there is a note that says: " + Fb.plantNotes());
  Serial.println("\n\n ===============================================================================");
}

void setup() {
  //Inicializa o monitor Serial
  Serial.begin(115200);
  Wf.connectWifi();
  Fb.FirebaseCodeSetup();
  HelloMessage();
  delay(1000);
  ThreadsCodeSetup();

}

void loop() {

  cpu.run();

}
