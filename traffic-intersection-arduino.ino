
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
int A4Y = 12;
int A4G = 13;

int PIN_BUTTON = 11;
int PIN_DOOR = 10;


TrafficLight trafficLight1(A1R, A1Y, A1G);
TrafficLight trafficLight2(A2R, A2Y, A2G);
TrafficLight trafficLight3(A3R, A3Y, A3G);
TrafficLight trafficLight4(A4R, A4Y, A4G);

Button button(PIN_BUTTON);

Door door(PIN_DOOR);

Timer timer;
Timer cycleTimer;

int i=1;

long TIMER_EMERGENCY = 30000;
long TIMER_NORMALCYCLE = 10000;
  

void setup() {
  trafficLight1.initTest();
  trafficLight2.initTest();
  trafficLight3.initTest();
  trafficLight4.initTest();
}

void loop() {
  if (button.isPressed()) {
    trafficLight1.stop();
    trafficLight2.stop();
    trafficLight3.stop();
    trafficLight4.go();
    door.open();
    timer.startTimer(TIMER_EMERGENCY);
  } else {
      if (timer.isTimerReady() && cycleTimer.isTimerReady()) {
        door.close();
        stopLights();
        if (door.doorIsClosed() && trafficLight1.stopped() && trafficLight2.stopped() && trafficLight3.stopped() && trafficLight4.stopped()){
          normalCycle(i);
          cycleTimer.startTimer(TIMER_NORMALCYCLE);
          if (i==4){
            i=1;
          } else {
            i++;
          }
        }
      }
  }

  trafficLight1.loop();
  trafficLight2.loop();
  trafficLight3.loop();
  trafficLight4.loop();
  door.loop();
  
}

void stopLights(){
  trafficLight1.stop();
  trafficLight2.stop();
  trafficLight3.stop();
  trafficLight4.stop();
}

void normalCycle(int iter){
  switch (iter){
    case 1:
      trafficLight1.go();
      break;
    case 2:
      trafficLight2.go();
      break;
    case 3:
      trafficLight3.go();
      break;
    case 4:
      trafficLight4.go(); 
      break; 
  }
}
