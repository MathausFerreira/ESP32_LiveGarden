#include "WifiCode.h"
#include "FirebaseCodeM.h"

#include "Thread.h"
#include "ThreadController.h"

Thread threadF1;
Thread threadF2;
ThreadController cpu;

void Function_thread1() {

}

void Function_thread2() {
  Serial.println(Fb.plantName());
}

void ThreadsCodeSetup() {
  threadF1.setInterval(5000);
  threadF1.onRun(Function_thread1);

  threadF2.setInterval(2500);
  threadF2.onRun(Function_thread2);

  cpu.add(&threadF1);
  cpu.add(&threadF2);
}
void HelloMessage() {
  Serial.println("Hello, My name is " + Fb.plantName() + "!");
  Serial.println("I am " + (String)Fb.plantAge() + " years old!");
  Serial.println("My Gender is: " + Fb.avatarGender());
  Serial.println("My Species is: " + Fb.plantSpecies());
  Serial.println("I was programmed to Interact: " + Fb.iteration()+ " with frequency: " + (String)Fb.iterationFrequency());
  Serial.println("I was programmed to Rotate: " + Fb.autoRotate());
  Serial.println("I will Rotate: " + (String)Fb.timeToRotate()+ " times a day. ");
  Serial.println("In my register there is a note: " + Fb.plantNotes());
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
