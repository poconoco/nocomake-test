#include <Servo.h>

float sqr(float value) {
  return value*value;
}

float sign(float value) {
  if (value < 0)
    return -1;
  
  if (value > 0)
    return 1;

  return 0;
}

float nearZero(float value) {
  return value > -0.001 && value < 0.001;
}

class ServoController {
  public:
    ServoController(int pin, float maxSpeed, float startAcceleration, float brakeAcceleration, float startPos)
      : _maxSpeed(maxSpeed)  // degrees per second
      , _startAcceleration(startAcceleration)
      , _brakeAcceleration(brakeAcceleration)  // Expect positive value, will transform into negative acceleration internally
      , _currentPos(startPos)
      , _currentSpeed(0)
      , _lastNow(0) {

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
      if (_lastNow == 0) {
        _lastNow = now;
        return;
      }

      const float deltaT = (float)(now - _lastNow) / 1000;
      const float targetDistance = _targetPos - _currentPos;
      const float absTargetDistance = abs(targetDistance);

      _lastNow = now;


      if (nearZero(targetDistance)) {
        _currentSpeed = 0;
      } else if (sign(_currentSpeed) != sign(targetDistance)) {
        // Moving in opposite direction, brake
        _currentSpeed = applyAcceleraton(_currentSpeed, -_brakeAcceleration, deltaT);
      } else {
        const float absSpeed = abs(_currentSpeed);
        const float brakingDistance = sqr(_currentSpeed) / (2 * _brakeAcceleration);

        if (absTargetDistance > brakingDistance) {
          if (nearZero(absSpeed - _maxSpeed)) {
            // Cruising at max speed, do nothing
          } else if (absSpeed < _maxSpeed) {
            // Slow, we can accelerate
            _currentSpeed = applyAcceleraton(_currentSpeed, _startAcceleration, deltaT);
          } else if (absSpeed > _maxSpeed) {
            // Too fast, we must brake
            _currentSpeed = applyAcceleraton(_currentSpeed, -_brakeAcceleration, deltaT);
          }
        } else {  // absTargetDistance <= brakingDistance
          // We need to brake, but we need to calculate the new braking acceleration, 
          // for the case if default braking would not stop where needed
          const float requiredBrakingAccel = sqr(_currentSpeed) / (2 * absTargetDistance);
          _currentSpeed = applyAcceleraton(_currentSpeed, -requiredBrakingAccel, deltaT);
        }    
      }

      const float deltaDistance = _currentSpeed * deltaT;
      _currentPos += deltaDistance;
      if (nearZero(_currentPos - _targetPos))
        _currentPos = _targetPos;

      _servo.write(_currentPos);

    }

  private: 
    Servo _servo;
    float _maxSpeed;
    float _startAcceleration;
    float _brakeAcceleration;
    float _currentPos;
    float _currentSpeed;
    float _targetPos;
    unsigned long _lastNow;

    float applyAcceleraton(float speed, float accel, float deltaT) {
      float deltaA = accel * deltaT;

      if (speed > 0)
        return min(speed + deltaA, _maxSpeed);
      else
        return max(speed - deltaA, -_maxSpeed);
    }
};


void setup() {

  // To prevent noise causing other servos random movement
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  ServoController servo(
    9,  // pin
    360, // max speed, degrees per second
    400,  // acceleration
    200,  // braking acceleration
    0); // start pos, degrees

  int target = 180;
  
  while (true) {
    servo.write(target);
    while (servo.getCurrentPos() != target) {
      servo.tick();
      delay(10);
    }

    if (target == 180)
      target = 0;
    else
      target = 180;
  }
}


void loop() {

}
