#include <Servo.h>


#ifndef _DOOR_H
#define _DOOR_H


class Door {

  int _doorPin;
  int _gl1Pin;
  int _gl2Pin; 
  int _yl1Pin; 
  int _yl2Pin;
  
  
  int ylOn = 0;
  Servo myservo;
  int pos = 0;
  Timer timer;
  Timer timerLight;
  
  enum State {
    OPEN,
    CLOSED,
  };

  State _currentState = CLOSED;
  State _targetState = CLOSED;

public:
  Door(int doorPin, int gl1Pin, int gl2Pin, int yl1Pin, int yl2Pin){
    myservo.attach(doorPin);
    myservo.write(0);

    _gl1Pin = gl1Pin;
    _gl2Pin = gl2Pin;
    _yl1Pin = yl1Pin;
    _yl2Pin = yl2Pin;

    pinMode(_gl1Pin, OUTPUT);
    pinMode(_gl2Pin, OUTPUT);
    pinMode(_yl1Pin, OUTPUT);
    pinMode(_yl2Pin, OUTPUT);


    digitalWrite(_gl1Pin, HIGH);
    digitalWrite(_gl2Pin, HIGH);
    digitalWrite(_yl1Pin, HIGH);
    digitalWrite(_yl2Pin, HIGH);
    delay(1000);
    digitalWrite(_gl1Pin, LOW);
    digitalWrite(_gl2Pin, LOW);
    digitalWrite(_yl1Pin, LOW);
    digitalWrite(_yl2Pin, LOW);

    
  }

  bool doorIsClosed(){
    if (_currentState = CLOSED){
      return true;
    } else {
      return false;
    }
  }

  void open() {
    _targetState = OPEN;
  }

  void close() {
    _targetState = CLOSED;
  }



  void loop(){
    if (_targetState == OPEN) {
      openDoor();
    } else {
      closeDoor();
    }
  }

private:
  void openDoor(){

    if (timer.isTimerReady() && pos <= 180 && _currentState != OPEN){
      myservo.write(pos);
      pos +=1;
      timer.startTimer(15);

      if (timerLight.isTimerReady()){
        yellowLight();
        timerLight.startTimer(300);
      }
    }

    if (myservo.read() == 180){
      pos = 180;
      digitalWrite(_yl1Pin, LOW);
      digitalWrite(_yl2Pin, LOW);
      
      _currentState = OPEN;
      
    }
    
    greenLight();
    
  }

  void closeDoor(){

    if (timer.isTimerReady() && pos >= 0 && _currentState != CLOSED){
      myservo.write(pos);
      pos -=1;
      timer.startTimer(15);

      if (timerLight.isTimerReady()){
        yellowLight();
        timerLight.startTimer(300);
      }
    }

    if (myservo.read() == 0){
      pos = 0;
      digitalWrite(_yl1Pin, LOW);
      digitalWrite(_yl2Pin, LOW);
      
      _currentState = OPEN;
    }
    
    greenLight();
    
    
  }


  void greenLight(){
    if (_currentState = OPEN){
      digitalWrite(_gl1Pin, HIGH);
      digitalWrite(_gl2Pin, HIGH);
    } else {
      digitalWrite(_gl1Pin, LOW);
      digitalWrite(_gl2Pin, LOW);
    }
    
  }
  
  void yellowLight(){
    if (ylOn = 0){
      digitalWrite(_yl1Pin, HIGH);
      digitalWrite(_yl2Pin, HIGH);
      ylOn = 1;
    } else {
      digitalWrite(_yl1Pin, LOW);
      digitalWrite(_yl2Pin, LOW);
      ylOn = 0;
    }
  }

};

#endif // _DOOR_H
