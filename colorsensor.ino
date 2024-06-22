
int out = 12;
void setup() {
  Serial.begin(9600);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(A5,OUTPUT);
  pinMode(out,INPUT);
  digitalWrite(A2,HIGH);
  digitalWrite(A3,LOW);
}
void loop(){
  digitalWrite(A4,LOW);
  digitalWrite(A5,LOW);
  int r = pulseIn(out,LOW);
  //r = map(r,54,365,255,0);
  Serial.print("r:");Serial.print(r);Serial.print(" ");
  delay(10);
  digitalWrite(A4,LOW);
  digitalWrite(A5,HIGH);
  int b = pulseIn(out,LOW);
  //b = map(b,40,385,255,0);
  Serial.print("b:");Serial.print(b);Serial.print(" ");
  delay(10);
  digitalWrite(A4,HIGH);
  digitalWrite(A5,HIGH);
  int g = pulseIn(out,LOW);
  //g = map(g,70,480,255,0);
  Serial.print("g:");Serial.print(g);Serial.println(" ");
  delay(1000);
  // int colors[14][3] = {{0,0,0},{255,255,255},{0,255,255},{169,169,169},{128,128,128},{0,255,0},{211,211,211},{255,0,255},{255,165,0},{255,192,203},{255,0,0},{0,0,255},{255,255,0},{0,100,0}};
  // int min = 10000;
  // int color = 0;
  // for (int n = 0; n <14 ; n++)
  // {
  //   int d = (r-colors[n][0])*(r-colors[n][0])+(b-colors[n][1])*(b-colors[n][2])+(g-colors[n][0])*(g-colors[n][0]);
  //   if (d<min){
  //     min = d;
  //     color = n;
  //   }
  // }
  // Serial.println(color);
}

  
//rgb values

//  black		(0,0,0)
// white		(255,255,255)
// cyan		(0,255,255)
// darkgray	(169,169,169)
// gray		(128,128,128)
// green		(0,255,0)
// lightgray	(211,211,211)
// magenta 	(255,0,255)
// orange 		(255,165,0)
// pink		(255,192,203)
// red		(255,0,0)
// blue		(0,0,255)
// yellow 		(255,255,0)
// darkgreen	(0,100,0)

