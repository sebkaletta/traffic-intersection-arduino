
#ifndef _TRAFFIC_LIGHT_H
#define _TRAFFIC_LIGHT_H

#include "Timer.h"

class TrafficLight {

  long TIMER_YELLOW = 1000;

  int _greenLED;
  int _yellowLED;
  int _redLED;

  enum State {
    GREEN,
    REDYELLOW,
    YELLOW,
    RED
  };

  State _currentState = GREEN;
  State _targetState = GREEN;
  Timer timer;




public:
  TrafficLight(int redLED, int yellowLED, int greenLED){
    _greenLED = greenLED;
    _yellowLED = yellowLED;
    _redLED = redLED;

    pinMode(_greenLED, OUTPUT);
    pinMode(_yellowLED, OUTPUT);
    pinMode(_redLED, OUTPUT);
  
  }


  bool stopped(){
    if (_currentState == RED){
      return true; 
    } else {
      return false;
    }
  }

  void go() {
    _targetState = GREEN;
  }

  void stop() {
    _targetState = RED;
  }

  void loop() {
    if (_targetState == GREEN) {
      goToGreen();
    } else {
      goToRed();
    }
  }


  

  void initTest(){
    digitalWrite(_greenLED, HIGH);
    digitalWrite(_yellowLED, HIGH);
    digitalWrite(_redLED, HIGH);
    delay(2000);
    digitalWrite(_greenLED, LOW);
    digitalWrite(_yellowLED, LOW);
    digitalWrite(_redLED, LOW);
  }

  void blinkingYellow() {
    if (millis() % 1000 > 500) {
      yellow();
    } else {
      off();
    }
  }

  void green() {
    digitalWrite(_greenLED, HIGH);
    digitalWrite(_yellowLED, LOW);
    digitalWrite(_redLED, LOW);
  }
  
  void red() {
    digitalWrite(_greenLED, LOW);
    digitalWrite(_yellowLED, LOW);
    digitalWrite(_redLED, HIGH);
  }

  void off() {
    digitalWrite(_greenLED, LOW);
    digitalWrite(_yellowLED, LOW);
    digitalWrite(_redLED, LOW);
  }

  
private:

  void goToGreen() {
    // red
    // redyellow
    // green     
    switch (_currentState) {
      case RED:
        _currentState = REDYELLOW;
        timer.startTimer(TIMER_YELLOW);
        break;

      case YELLOW:
        yellow();
        if (timer.isTimerReady()) {
          _currentState = GREEN;
        }
        break;

      case REDYELLOW:
        redYellow();
        if (timer.isTimerReady()) {
          _currentState = GREEN;
        }
        break;

      case GREEN:
        green();
        break;
    }
  }


  void goToRed() {
    // green
    // yellow
    // red
    switch (_currentState) {
      case GREEN:
        _currentState = YELLOW;
        timer.startTimer(TIMER_YELLOW);
        break;
        
      case REDYELLOW:
        redYellow();
        if (timer.isTimerReady()) {
          _currentState = RED;
        }
        break;
        
      case YELLOW:
        yellow();
        if (timer.isTimerReady()) {
          _currentState = RED;
        }
        break;
        
      case RED:
        red();
        break;
    }
  }
  

  void yellow() {
    digitalWrite(_greenLED, LOW);
    digitalWrite(_yellowLED, HIGH);
    digitalWrite(_redLED, LOW);
  }

  void redYellow() {
    digitalWrite(_greenLED, LOW);
    digitalWrite(_yellowLED, HIGH);
    digitalWrite(_redLED, HIGH);
  }
 
};

#endif // _TRAFFIC_LIGHT_H
