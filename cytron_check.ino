int DIR1 = 4; //right motor
int PWM1 = 5;
int DIR2 = 6; // left motor
int PWM2 = 7;
int Speed = 5;

void setup() {
  pinMode(DIR1,OUTPUT);
  pinMode(PWM1,OUTPUT);
  pinMode(DIR2,OUTPUT);
  pinMode(PWM2,OUTPUT);  

}

void loop() {
  digitalWrite(DIR1,HIGH);
  digitalWrite(DIR2,HIGH);
  analogWrite(PWM1,30);
  analogWrite(PWM2,Speed);
}




