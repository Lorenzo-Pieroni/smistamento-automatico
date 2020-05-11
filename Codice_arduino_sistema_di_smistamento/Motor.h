#ifndef Motor_h
#define Motor_h

class Motor {
  private:
    int pin1 = 0;
    int pin2 = 0;
    int pin3 = 0;
    int pin4 = 0;
    boolean stat1 = 0;
    boolean stat2 = 0;
  public:
    Motor(int, int, int, int, boolean, boolean);
    void Left();
    void Right();
    void Stop();
};

class oneWayMotor {
  private:
    int pin1 = 0;
    boolean stat1 = 0;
    boolean stat2 = 0;
  public:
    oneWayMotor(int, boolean, boolean);
    void On();
    void Off();
};

oneWayMotor::oneWayMotor(int a, boolean d1, boolean d2) {
  pin1 = a;
  stat1 = d1;
  stat2 = d2;
  pinMode(a, OUTPUT);
}

void oneWayMotor::On() {
  Serial.println("ON");
  digitalWrite(pin1, stat1);

}
void oneWayMotor::Off() {
  Serial.println("OFF");
  digitalWrite(pin1, stat2);
}

Motor::Motor(int a, int b, int c, int d, boolean d1, boolean d2) {
  pin1 = a;
  pin2 = b;
  pin3 = c;
  pin4 = d;
  stat1 = d1;
  stat2 = d2;
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
}

void Motor::Left() {
  Serial.println("LEFT");
  digitalWrite(pin1, stat1);
  digitalWrite(pin2, stat1);
  digitalWrite(pin3, stat2);
  digitalWrite(pin4, stat2);
}

void Motor::Right() {
  Serial.println("RIGHT");
  digitalWrite(pin1, stat2);
  digitalWrite(pin2, stat2);
  digitalWrite(pin3, stat1);
  digitalWrite(pin4, stat1);
}

void Motor::Stop() {
  Serial.println("STOP");
  digitalWrite(pin1, stat1);
  digitalWrite(pin2, stat1);
  digitalWrite(pin3, stat1);
  digitalWrite(pin4, stat1);
}

#endif
