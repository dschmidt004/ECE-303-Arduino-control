
#define echoPin 42 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 44 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
const int forward=5;
const int backward = 7;
int val = 0;
int out=0;
char temp;
String instr = "distance ";
String outstr=", Output speed: ";
String rotation ="";

int led1 = 24;
int led2 = 26;
int led3 = 28;
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  pinMode(forward,OUTPUT);
  
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  
  pinMode(backward,OUTPUT);
  Serial.begin(9600);;
}
void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
  
    val=Serial.parseInt();
    temp = Serial.read();
    out=map(distance,0,110,-255,255);
    if(distance>30){
      
      analogWrite(forward,out);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      
    }
    else if(distance>20){
      
      analogWrite(forward,out);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, HIGH);
      
    }
    else if(distance>10){
      
      analogWrite(forward,out);
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
    }
    else{
      
      analogWrite(forward,0);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
    }
  
  
  Serial.println(instr+distance+outstr+distance+rotation);
  

}
