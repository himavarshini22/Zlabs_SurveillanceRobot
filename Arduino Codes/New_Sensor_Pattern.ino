int DIR1 = 4; // left motor
int PWM1 = 5;
int DIR2 = 7; // right motor
int PWM2 = 6;
int Speed = 30; // speed for forward
int Align_Speed = 50; // speed for alignment
int Turn_Speed = 100; // speed for sharp turns

int center_time = 1000; // time taken for the cars center to come to the center of rotation position
int count = 0;

//ultrasonic 
//pins for front sensors
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
  pinMode(A0, INPUT); // atmost left
  pinMode(A1, INPUT); // left
  pinMode(A2, INPUT); // front 
  pinMode(A3, INPUT); // back
  pinMode(A4, INPUT); // right
  pinMode(A5, INPUT); // atmost right

  //ultrasonic
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
  // ultrasonic function to calculate the distances
  ultrasonic();

  int LSO = digitalRead(A0);
  int LSI = digitalRead(A1);
  int FS = digitalRead(A2);
  int BS = digitalRead(A3);
  int RSI = digitalRead(A4);
  int RSO = digitalRead(A5);

  // move forward
  if (LSO == 0 && LSI == 0 &&  FS == 1 && BS == 1 && RSI == 0 && RSO == 0){
    Forward();
  }
  // left align
    if (LSO == 0 && LSI == 1 &&  FS == 1 && BS == 1 && RSI == 0 && RSO == 0){
    Left_Align();
  }
  // right align
  if (LSO == 0 && LSI == 0 &&  FS == 1 && BS == 1 && RSI == 1 && RSO == 0){
    Right_Align();
  }
  // sharp left condition 
  if (LSO == 1 && LSI == 1 &&  FS == 1 && BS == 1 && RSO == 0){
    Forward();
  }
  if (LSO == 1 && LSI == 1 &&  FS == 0 && BS == 1 && RSO == 0){
    Sharp_Left();
  }
  if (LSO == 0 && LSI == 1 &&  FS == 1 && BS == 1 && RSO == 0){
    Sharp_Left();
  }
  // sharp right condition 
  if (LSO == 0 &&  FS == 1 && BS == 1 && RSI == 1 && RSO ==1){
    Forward();
  }
  if (LSO == 0 &&  FS == 0 && BS == 1 && RSI == 1 && RSO == 1){
    Sharp_Right();
  }
  if (LSO == 0  && FS == 1 && BS == 1 && RSI == 1 && RSO == 0){
    Sharp_Right();
  }
  //uturn
  if (LSO == 0 && FS == 0 && BS == 1 && RSO == 0){
    U_Turn();
  }
  // T section coming from bottom of the T and Y intersection using the count 
  if (LSO == 1 && LSI == 1 &&  FS == 1 && BS == 1 && RSI == 1 && RSO == 1){
    Forward();
  }
  if (LSO == 1 && LSI == 1 &&  FS == 0 && BS == 1 && RSI == 1 && RSO == 1){
    count += 1;
    if (count == 1){
      T_Intersection();
    }
    if (count == 2){
      Y_Pattern();
    }
  }
  // deadend condition
  if (LSO == 1 && LSI == 0 &&  FS == 0 && BS == 0 && RSI == 0 && RSO == 1){
    Dead_End();
  }
  // after the 2nd Uturn, going back
  // LS) == 1 is kept so that we can solve the problem here but we need to add a small black sticker in the path of LSO
  if (LSO == 1 && LSI == 0 &&  FS == 1 && BS == 1 && RSI == 1 && RSO == 0){
    Forward();
  }
  if (LSO == 1 && LSI == 0 &&  FS == 1 && BS == 1 && RSI == 1 && RSO == 1){
    Forward();
  }
  if (LSO == 1 && LSI == 0 &&  FS == 1 && BS == 1 && RSI == 0 && RSO == 1){
    Forward();
  }
}

void Forward(){
  // move forward in a straight line
  digitalWrite(DIR1, LOW);
  digitalWrite(DIR2, LOW);
  analogWrite(PWM1, Speed);
  analogWrite(PWM2, Speed);
}

void Left_Align(){
  // act like a line follower and take left turn 
  digitalWrite(DIR1, HIGH);
  digitalWrite(DIR2, LOW);
  analogWrite(PWM1, Align_Speed);
  analogWrite(PWM2, Align_Speed);
}

void Right_Align(){
  // act like a line follower and take right turn 
  digitalWrite(DIR1, LOW);
  digitalWrite(DIR2, HIGH);
  analogWrite(PWM1, Align_Speed);
  analogWrite(PWM2, Align_Speed);
}

void Sharp_Left(){
  // come up with a config to take sharp left turn 
  digitalWrite(DIR1, HIGH);
  digitalWrite(DIR2, LOW);
  analogWrite(PWM1, Turn_Speed);
  analogWrite(PWM2, Turn_Speed);
}

void Sharp_Right(){
  // come up with a config to take sharp right turn 
  digitalWrite(DIR1, LOW);
  digitalWrite(DIR2, HIGH);
  analogWrite(PWM1, Turn_Speed);
  analogWrite(PWM2, Turn_Speed);
}

void Cross_Section(){
  // according to the layout plan the action at the cross intersection 
  Forward();
}

void Y_Pattern(){
  // At Y conditions that we've in the layout plan the action
  Forward();
  delay(center_time);
  while (true){
    int FS = digitalRead(A2);
    Sharp_Left();
    if(FS==1){
      break;
    }
  }
}

void T_Intersection(){
  // At T conditions that we've in the layout plan the action
  Forward();
  delay(center_time);
  while (true){
    int FS = digitalRead(A2);
    Sharp_Right();
    if(FS==1){
      break;
    }
  }
}

void Reverse_T_Intersection(){
  // At reverse T conditions that we've in the layout plan the action
}

void Right_T(){

}

void Left_T(){

}

void Dead_End(){
  // digitalWrite(DIR1, LOW);
  // digitalWrite(DIR2, HIGH);
  analogWrite(PWM1, 0);
  analogWrite(PWM2, 0);
}

void U_Turn(){
  Forward();
  delay(center_time);
  while (true){
    int FS = digitalRead(A2);
    Sharp_Right();
    if(FS==1){
      break;
    }
  }
} 

void ultrasonic(){
  //ultrasonic
  digitalWrite(trigPin_f1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_f1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_f1, LOW);
  duration_f1 = pulseIn(echoPin_f1, HIGH);
  distance_f1 = duration_f1 * 0.034 / 2;

  digitalWrite(trigPin_b1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_b1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_b1, LOW);
  duration_b1 = pulseIn(echoPin_b1, HIGH);
  distance_b1 = duration_b1 * 0.034 / 2;

  digitalWrite(trigPin_f2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_f2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_f2, LOW);
  duration_f2 = pulseIn(echoPin_f2, HIGH);
  distance_f2 = duration_f2 * 0.034 / 2;

  digitalWrite(trigPin_b2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_b2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_b2, LOW);
  duration_b2 = pulseIn(echoPin_b2, HIGH);
  distance_b2 = duration_b2 * 0.034 / 2;
}
