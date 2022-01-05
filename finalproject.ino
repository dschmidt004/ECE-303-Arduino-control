#define echoPin 42 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 44 //attach pin D3 Arduino to pin Trig of HC-SR04
#include <MFRC522.h>
#include <require_cpp11.h>
#include <SPI.h>
#define SS_PIN 53
#define RST_PIN 4
#include <DHT.h>
#define DHTPIN 12    
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#include <LiquidCrystal.h>
#define SIGNAL_PIN 13
LiquidCrystal lcd(2,3,8,9,10,11);

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
#include <IRremote.h>

int value = 0;

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
const int forward=5;
const int backward = 7;
int val = 0;
int out=0;
char temp;
float t = 0;
const byte IR_RECEIVE_PIN = 49;
String instr = "distance ";
String outstr=", Output speed: ";
String rotation ="water level";

int led1 = 24;
int led2 = 26;
int led3 = 28;
int b = 0;
const int buzzer = 6;
int light = 0;
int move1 = 100;
int tlight = 0;
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  pinMode(forward,OUTPUT);
  pinMode(26,OUTPUT);
  pinMode(buzzer, OUTPUT);
  analogWrite(26,120);
  lcd.begin(16,2);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  int b = 0;
  dht.begin(); // initialize the sensor
  
  
}
void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  while(b != 1)
  {
  
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    b = 0;
    lcd.setCursor(0,1);
    
    lcd.print("ID card?");
    return;
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    b = 0;
    
  }
  
  //Show UID on serial monitor
  
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  
  content.toUpperCase();
  if (content.substring(1) == "33 89 D3 18") //change here the UID of the card/cards that you want to give access
  {
    
    
    b = 1;
    noTone(buzzer);
    delay(500);
  }
  else   {
    
    b = 0;
    tone(buzzer,1000);
    delay(500);
  }
  }
  if (IrReceiver.decode())
   {
      
      light = IrReceiver.decodedIRData.command;
      
      
      IrReceiver.resume();
   }
  
  delayMicroseconds(2);

  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
  
    val=Serial.parseInt();
    temp = Serial.read();
    
    if(light == 12){
      
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      tlight = 0;
      
    }
    else if(light == 24){
      analogWrite(led1,255);
      analogWrite(led2,255);
      analogWrite(led3,255);
      tlight = 1;
      
    }
    else if(light ==94){
      analogWrite(led1,135);
      analogWrite(led2,135);
      analogWrite(led3,135);
      tlight = 2;
      
    }
    else if(light ==70){
      if(move1 <=224)
      {
        move1 = move1+(255*0.10);
        analogWrite(forward,move1);
        light = 0;
      }
      
      
    }
    else if(light ==21){
      
      if(move1 >= 25)
      {
        move1 = move1-(255*0.10);
        analogWrite(forward,move1);
        light = 0;
      }
    }
    
  t = dht.readTemperature();
  t = 33;
  float move2 = move1;
  move2 = 100*move2/255;
  value = analogRead(SIGNAL_PIN); // read the analog value from sensor
  Serial.println(String(distance)+" "+String(tlight)+" "+String(move2)+" "+String(value)+" "+String(t));
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(String(move2)+"%");
  lcd.setCursor(0,1);
  lcd.print(String(t)+"C");
  if(t > 50){
    b = 0;
    lcd.print("System too hot, shutting down");
    analogWrite(forward,0);
    delay(2000);
  }
  
  

}
