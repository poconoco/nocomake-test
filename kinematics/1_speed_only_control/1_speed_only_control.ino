#include <Servo.h>

class ServoController {
  public:
    ServoController(int pin, float speed, float startPos)
      : _speed(speed)  // degrees per second
      , _currentPos(startPos)
      , _lastTick(0) {

        _servo.attach(pin);
        _servo.write(startPos);
    }
    
    void write(int targetPos) {
      _targetPos = targetPos;
    }

    int getCurrentPos() {
      return _currentPos;
    }

    void tick() {
      unsigned long now = millis();
      if (_lastTick == 0) {
        _lastTick = now;
        return;
      }

      float deltaTarget = _targetPos - _currentPos;

      if (deltaTarget != 0) {
        float deltaT = (float)(now - _lastTick) / 1000;
        float deltaD = _speed * deltaT;

        if (abs(deltaTarget) < deltaD)
          _currentPos = _targetPos;
        else if (deltaTarget > 0) 
          _currentPos += deltaD;
        else
          _currentPos -= deltaD;

        _servo.write(_currentPos);
      }

      _lastTick = now;
    }

  private: 
    Servo _servo;
    float _speed;
    float _currentPos;
    float _targetPos;
    unsigned long _lastTick;
};


void setup() {

  // To prevent noise causing other servos random movement
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  ServoController servo(
    9,  // pin
    30, // speed, degrees per second
    0); // start pos, degrees

  int target = 180;
  
  while (true) {
    servo.write(target);
    while (servo.getCurrentPos() != target) {
      servo.tick();
      delay(50);
    }

    if (target == 180)
      target = 0;
    else
      target = 180;
  }
}


void loop() {

}
