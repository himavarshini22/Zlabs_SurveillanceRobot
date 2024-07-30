int DIR1 = 4; // left motor
int PWM1 = 5;
int DIR2 = 7; // right motor
int PWM2 = 6;
int Speed = 50; // speed for forward
int AlignSpeed = 70;
int TurnSpeed = 100;
int UTurnSpeed = 160; // speed for turning
// LS = A0, RS = A1, MS = A2
const int trigPin_f1 = 9;
const int echoPin_f1 = 8;
const int trigPin_b1 = 11;
const int echoPin_b1 = 10;

long duration_f1;
long duration_b1;
int distance_f1;
int distance_b1;

//pins for back sensors
const int trigPin_f2 = 3;
const int echoPin_f2 = 2;
const int trigPin_b2 = 13;
const int echoPin_b2 = 12;

long duration_f2;
long duration_b2;
int distance_f2;
int distance_b2;

void setup() {
  pinMode(DIR1, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);  
  
  pinMode(trigPin_f1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_f1, INPUT); // Sets the echoPin as an Input

  pinMode(trigPin_b1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_b1, INPUT); 
  
  pinMode(trigPin_f2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_f2, INPUT); // Sets the echoPin as an Input

  pinMode(trigPin_b2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_b2, INPUT);// Sets the echoPin as an Input
}

void loop() {
  int LS = digitalRead(A1);
  int RS = digitalRead(A5);
  int MS = digitalRead(A2);
  int BS = digitalRead(A3);
  int LSO = digitalRead(A0);
  int RSO = digitalRead(A4);

  ultrasonic();

  if(distance_f1 <=50 || distance_b1 <=50 || distance_f2 <=50 || distance_b2 <=50 ){
    stop(); 
  }

  else{
    
    if (LSO==0 && LS == 0 && MS == 1 && RS == 0 && RSO == 0) {
      forward();
    } 
    if (LSO==0 &&LS == 1 && MS == 1 && RS == 1 && RSO == 0) {
      forward();
    }
    if (LSO==0 && LS == 0 && MS == 0 && RS == 1 && RSO == 0) {
      turnright();
    } 
    if (LSO==0 && LS == 0 && MS == 1 && RS == 1 && RSO == 0) {
      turnright();    
    }
    if (LSO==0 && LS == 1 && MS == 0 && RS == 0 && RSO == 0) {
      turnleft();
    } 
    if (LSO==0 && LS == 1 && MS == 1 && RS == 0 && RSO == 0) {
      turnleft();
    } 
    if (LSO==1 && LS == 1 && MS == 0 && RS == 0 && RSO == 0) {
      turnleftt();
    } 
    if (LSO==0 && LS == 0 && MS == 0 && RS == 1 && RSO == 1) {
      turnrightt();
    } 
    // if (LS == 1 && MS == 1 && RS == 1) {
    //   stop();
    //} 
    // if (LSO==0 && LS == 0 && MS == 0 && BS == 1 && RS == 0 && RSO == 0) {
    //   forward();
    // }
    if (LSO==0 && LS == 0 && MS == 0 && BS == 1 && RS == 0 && RSO == 0) {
      Uturn();
    }
    if (LSO==1 && LS == 1 && MS == 1 && BS == 1 && RS == 1 && RSO == 1) {
      T_bottom();
    }
    if (LSO==1 && LS == 1 && MS == 1 && BS == 1 && RS == 0 && RSO == 0) {
      forward();
      delay(200);
    }
  }
}

void forward() {
  digitalWrite(DIR1, LOW);
  digitalWrite(DIR2, LOW);
  analogWrite(PWM1, Speed);
  analogWrite(PWM2, Speed);
}

void turnrightt() {
  digitalWrite(DIR1, LOW);
  digitalWrite(DIR2, HIGH);
  analogWrite(PWM1, TurnSpeed);
  analogWrite(PWM2, TurnSpeed);
}
void turnright() {
  digitalWrite(DIR1, LOW);
  digitalWrite(DIR2, HIGH);
  analogWrite(PWM1, AlignSpeed);
  analogWrite(PWM2, AlignSpeed);
}

void turnleftt() {
  digitalWrite(DIR1, HIGH);
  digitalWrite(DIR2, LOW);
  analogWrite(PWM1, TurnSpeed);
  analogWrite(PWM2, TurnSpeed);
}
void turnleft() {
  digitalWrite(DIR1, HIGH);
  digitalWrite(DIR2, LOW);
  analogWrite(PWM1, AlignSpeed);
  analogWrite(PWM2, AlignSpeed);
}

void Uturn(){
  // digitalWrite(DIR1, HIGH);
  // digitalWrite(DIR2, HIGH);
  // analogWrite(PWM1, Speed);
  // analogWrite(PWM2, Speed);
  // delay(200);
  while(true){
    int MS = digitalRead(A2);
    digitalWrite(DIR1, LOW);
    digitalWrite(DIR2, HIGH);
    analogWrite(PWM1, UTurnSpeed);
    analogWrite(PWM2, UTurnSpeed);
    if(MS==1){
      break;
    }
  }
}

void T_bottom(){
  digitalWrite(DIR1, LOW);
  digitalWrite(DIR2, HIGH);
  analogWrite(PWM1, UTurnSpeed);
  analogWrite(PWM2, UTurnSpeed);
  delay(300);
}

void stop() {
  analogWrite(PWM1, 0);
  analogWrite(PWM2, 0);
}

void ultrasonic(){

  digitalWrite(trigPin_f1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin_f1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_f1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration_f1 = pulseIn(echoPin_f1, HIGH);
  // Calculating the distance
  distance_f1 = duration_f1 * 0.034 / 2;

  digitalWrite(trigPin_b1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin_b1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_b1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration_b1 = pulseIn(echoPin_b1, HIGH);
  // Calculating the distance
  distance_b1 = duration_b1 * 0.034 / 2;

  digitalWrite(trigPin_f2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin_f2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_f2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration_f2 = pulseIn(echoPin_f2, HIGH);
  // Calculating the distance
  distance_f2 = duration_f2 * 0.034 / 2;

  digitalWrite(trigPin_b2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin_b2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_b2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration_b2 = pulseIn(echoPin_b2, HIGH);
  // Calculating the distance
  distance_b2 = duration_b2 * 0.034 / 2;
}
