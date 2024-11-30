
float sqr(float value) {
  return value*value;
}

struct Point2D {
  float x;
  float y;
  bool invalid;
};


class IK3DOF {
  public: 
    IK3DOF(
      int pinTurn, 
      int pinArm1,
      int pinArm2,
      float arm1HOffset,
      float arm1VOffset,
      float tipHOffset,
      float tipVOffset,
      float arm1Length,
      float arm2Length,
      float turnZeroAngle, // Angle to write to servo so turn is at zero degrees to X axis (looks straignt to the right)
      float arm1ZeroAngle, // Angle to write to servo so the arm1 is parallel to table
      float arm2ZeroAngle, // Angle to write to servo so the arm2 is parallel to table or arm1 if (arm2RelativeToArm1)
      bool turnInverted,
      bool arm1Inverted,
      bool arm2Inverted,
      bool arm2RelativeToArm1
    ) : _arm1HOffset(arm1HOffset)
      , _arm1VOffset(arm1VOffset)
      , _tipHOffset(tipHOffset)
      , _tipVOffset(tipVOffset)
      , _arm1Length(arm1Length)
      , _arm2Length(arm2Length)
      , _turnZeroAngle(turnZeroAngle)
      , _arm1ZeroAngle(arm1ZeroAngle)
      , _arm2ZeroAngle(arm2ZeroAngle)
      , _turnInverted(turnInverted)
      , _arm1Inverted(arm1Inverted)
      , _arm2Inverted(arm2Inverted)
      , _arm2RelativeToArm1(arm2RelativeToArm1) {

      _servoTurn.attach(pinTurn);
      _servoArm1.attach(pinArm1);
      _servoArm2.attach(pinArm2);
    }

    void write(float x, float y, float z) {
      float turnAngle = _turnZeroAngle + (_turnInverted ? -1.0 : 1.0) * (atan2(y, x) * 180 / PI);
      float x2 = sqrt(sqr(x)+sqr(y));
      float y2 = z;

      // shift arm1 start to 0,0:
      x2 -= _arm1HOffset;
      y2 -= _arm1VOffset;

      // shift tip to account parallel part of grip
      x2 -= _tipHOffset;
      y2 -= _tipVOffset;

      // Get coordinates of the arm1-arm2 joint
      Point2D joint = circleIntersection(x2, y2, _arm1Length, _arm2Length);
      if (joint.invalid)
        return;
  
      // Get arm angles
      float arm1AbsAngle = atan2(joint.y, joint.x) * 180 / PI;
      float arm2AbsAngle = atan2(y2 - joint.y, x2 - joint.x) * 180 / PI;
      float arm1Angle = _arm1ZeroAngle + (_arm1Inverted ? -1.0 : 1.0) * arm1AbsAngle;
      float arm2Angle = _arm2ZeroAngle + (_arm2Inverted ? -1.0 : 1.0) *
        (_arm2RelativeToArm1 
           ? (180 - arm1AbsAngle + arm2AbsAngle)
           : arm2AbsAngle);

      _servoTurn.write(turnAngle);
      _servoArm1.write(arm1Angle);
      _servoArm2.write(arm2Angle);
    }

  private:
    Servo _servoTurn;
    Servo _servoArm1;
    Servo _servoArm2;

    float _arm1HOffset;
    float _arm1VOffset;
    float _tipHOffset;
    float _tipVOffset;
    float _arm1Length;
    float _arm2Length;
    float _turnZeroAngle;
    float _arm1ZeroAngle;
    float _arm2ZeroAngle;
    bool _turnInverted;
    bool _arm1Inverted;
    bool _arm2Inverted;
    bool _arm2RelativeToArm1;

    Point2D circleIntersection(float x2, float y2, float r1, float r2) {  // x1,y1 assumed to be 0,0
      float d = sqrt(x2 * x2 + y2 * y2); // distance between circle centers

      Point2D result;

      // No solution
      if (d == 0) {
        result.invalid = true;
        return result;
      }

      float a = (r1 * r1 - r2 * r2 + d * d) / (2 * d);

      // Circles don't intersect
      if (r1 < a) {
        result.invalid = true;
        return result;
      }

      float h = sqrt(r1 * r1 - a * a);

      float xt = a * (x2 / d);
      float yt = a * (y2 / d);

      // Two solutions
      float jointXa = xt + h * (y2 / d);
      float jointYa = yt - h * (x2 / d);
      float jointXb = xt - h * (y2 / d);
      float jointYb = yt + h * (x2 / d);

      // Pick the one that has higher joint
      if (jointYa > jointYb) {
        result.x = jointXa;
        result.y = jointYa;
      } else {
        result.x = jointXb;
        result.y = jointYb;
      }
      
      result.invalid = false;

      return result;
    }

};
