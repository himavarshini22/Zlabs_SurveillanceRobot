int DIR1 = 4; //right motor
int PWM1 = 5;
int DIR2 = 7; // left motor
int PWM2 = 6;
int Speed = 200;

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




