
#include "TrafficLight.h"
#include "Button.h"
#include "Door.h"
#include "Timer.h"

int A1R = 0;
int A1Y = 1;
int A1G = 2;
  
int A2R = 3;
int A2Y = 4;
int A2G = 5;
  
int A3R = 6;
int A3Y = 7;
int A3G = 8;
  
int A4R = 9;
int A4Y = 10;
int A4G = 11;

int PIN_BUTTON = 12;
int PIN_DOOR = 13;


TrafficLight trafficLight1(A1R, A1Y, A1G);
TrafficLight trafficLight2(A2R, A2Y, A2G);
TrafficLight trafficLight3(A3R, A3Y, A3G);
TrafficLight trafficLight4(A4R, A4Y, A4G);

Button button(PIN_BUTTON);

Door door(PIN_DOOR);

Timer timer;
  

void setup() {
  trafficLight1.initTest();
  trafficLight2.initTest();
  trafficLight3.initTest();
  trafficLight4.initTest();
}

void loop() {
  if (button.isPressed()) {
    emergency();
    timer.startTimer(1000);
  } else {
    if (timer.isTimerReady()) {
      normalCycle();
    }
  }
}

void normalCycle(){
  trafficLight1.go();
  trafficLight1.loop();
  delay(8000);
  trafficLight1.stop();
  trafficLight1.loop();
  trafficLight2.go();
  trafficLight2.loop();
  delay(8000);
  trafficLight2.stop();
  trafficLight2.loop();
  trafficLight3.go();
  trafficLight3.loop();
  delay(8000);
  trafficLight3.stop();
  trafficLight3.loop();
  trafficLight4.go();
  trafficLight4.loop();
  delay(8000);
  trafficLight4.stop();
  trafficLight4.loop();
}

void emergency(){
  trafficLight1.stop();
  trafficLight1.loop();
  trafficLight2.stop();
  trafficLight2.loop();
  trafficLight3.stop();
  trafficLight3.loop();
  trafficLight4.go();
  trafficLight4.loop();
  door.openDoor();
  delay(20000);
  door.closeDoor();
  trafficLight4.stop();
  trafficLight4.loop();
}
