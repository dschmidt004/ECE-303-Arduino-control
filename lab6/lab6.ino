const int forward=5;
const int backward = 7;
int val = 0;
int outval=0;
char temp;
String instr = "Input Value: ";
String outstr=", Output Value: ";
String rotation ="";
void setup() {
  pinMode(forward,OUTPUT);
  pinMode(backward,OUTPUT);
  Serial.begin(9600);
  

}

void loop() {
  if(Serial.available()>0){
    val=Serial.parseInt();
    temp = Serial.read();
    outval=map(val,0,1023,-255,255);
    if(outval>0){
      rotation=", Going Foward";
      analogWrite(backward,0);
      analogWrite(forward,outval);
      
    }
    if(outval==0){
      rotation=", stopped";
      analogWrite(forward,0);
      analogWrite(backward,0);
      
    }
    if(outval<0){
      rotation=", Going backward";
      analogWrite(forward,0);
      analogWrite(backward,-outval);
      
    }
    Serial.println(instr+val+outstr+outval+rotation);
    
  }

}
