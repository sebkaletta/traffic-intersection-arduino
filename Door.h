
#ifndef _DOOR_H
#define _DOOR_H

#include <Servo.h>

class Door {

  int _doorPin;
  Servo myservo;
  
  enum State {
    OPEN,
    CLOSED,
  };

  State _currentState = CLOSED;
  State _targetState = CLOSED;

public:
  Door(int doorPin){
    myservo.attach(doorPin);
    myservo.write(0);
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

    myservo.write(90);
    _currentState = OPEN;
    
  }

  void closeDoor(){

    myservo.write(0);
    _currentState = CLOSED;
  }


};

#endif // _DOOR_H
