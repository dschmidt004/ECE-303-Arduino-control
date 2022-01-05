int y=0;
int led1 = 5;
float x;
float i = 0.01;
float r = 1000;
float vled;
float vled1;
float vled2;
float vled3;
float vled4;
float rled = 6286.396;
float rfinal = r/(r+rled);//This is the value we use to find the voltage of led resistor
// the setup routine runs once when you press reset:
void setup() {


TCCR3A = 0b10000010;
TCCR3B = 0b00011100;
ICR3=200;

OCR3A = 0.01*ICR3;
TCNT1=0;

Serial.begin(9600);
pinMode(led1, OUTPUT);

}
void loop() {
x = analogRead(A0);
vled = analogRead(A0);
vled1 = analogRead(A0);
vled2 = analogRead(A0);
vled3 = analogRead(A0);
vled4 = analogRead(A0);
x = (x/1024)*5;
//Serial.println("The PWM% is");
Serial.print(i);
Serial.print(" ");
//Serial.println("The voltage across Photo resistor");
//Serial.println(5-x);
float evol = i * 5 * rfinal; // we use this to average the pwm voltage
vled = (vled+vled1+vled2+vled3+vled4)/5;
vled = ((vled/1024)*5);

//Serial.println("The voltage across LED resistor");
String b = " " + String(vled)+ " " + String(vled1) +" " + String(vled2) + " " + String(vled3)+ " " + String(vled4);
Serial.println(b);

OCR3A = (ICR3 *0.01)+OCR3A ;
i = i + .01;
if(OCR3A > ICR3){
  delay(1000);
  exit(0);
}


delay(500);
}
