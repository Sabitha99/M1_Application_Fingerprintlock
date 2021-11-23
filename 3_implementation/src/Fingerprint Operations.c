#include "dht.h"
#define dht_apin 2 // Analog Pin sensor is connected to
dht DHT;
#include<LiquidCrystal.h>
LiquidCrystal lcd(13,12,6,7,9,8);
#include <SoftwareSerial.h>
SoftwareSerial fingerPrint(10, 11);
#include<Servo.h>
Servo myServo;
 
#include <Adafruit_Fingerprint.h>
uint8_t id;
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&amp;fingerPrint);
#define rabin A8
#define enroll A0
#define del A1
#define up A2
#define down A3
#define openLight 3
#define closeLight 4
#define servoPin 5
 
void setup() 
{
    delay(1000);
    myServo.attach(servoPin);
    myServo.write(180);
    pinMode(enroll, INPUT_PULLUP);
    pinMode(up, INPUT_PULLUP); 
    pinMode(down, INPUT_PULLUP); 
    pinMode(del, INPUT_PULLUP); 
    pinMode(rabin, INPUT_PULLUP); 
    pinMode(openLight, OUTPUT);
    pinMode(closeLight, OUTPUT);
    lcd.begin(16,2);
    DHT.read11(dht_apin);
     
    lcd.setCursor(0,0);
    lcd.print("    MANMOHAN ");
   lcd.setCursor(0,1);
   lcd.print("POLYTECHNIC COLLAGE");
    lcd.scrollDisplayLeft();
    delay(1000);
    lcd.scrollDisplayLeft();
    delay(1000);
    lcd.scrollDisplayLeft();
    delay(1000);
    lcd.scrollDisplayLeft();
    delay(5000);
    lcd.clear();
    finger.begin(57600);
    Serial.begin(9600);
    lcd.clear();
    lcd.print(" Finding Module ");
    lcd.setCursor(0,1);
    delay(2000);
  
 
void loop() 
{
  lcd.setCursor(0,0);
    lcd.print("HUMI    =");
   lcd.print(DHT.humidity);
   lcd.print("%  ");
   lcd.setCursor(0,1);
   lcd.print("TEMP    =");
    lcd.print(   DHT.temperature); 
   lcd.println("'C  ");
   delay(5000);
   lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("  Press Match       ");
 lcd.setCursor(0,1);
 lcd.print("To Start System");
 digitalWrite(closeLight, HIGH);

 checkKeys();
 delay(2000);
 
 
 
void checkKeys()
{
   if(digitalRead(enroll) == 0)
   {
    lcd.clear();
    lcd.print("Please Wait");
    delay(2000);
    while(digitalRead(enroll) == 0);
    Enroll();
   }
 
   else if(digitalRead(del) == 0)
   {
    lcd.clear();
    lcd.print("Please Wait");
    delay(2000);
    delet();
   }  
}
 
void Enroll()
{
   int count=0;
   lcd.clear();
   lcd.print("Enroll Finger    ");
   lcd.setCursor(0,1);
   lcd.print("Location:");
   while(1)
   {
     lcd.setCursor(9,1);
     lcd.print(count);
     if(digitalRead(up) == 0)
     {
       count++;
       if(count>25)
       count=0;
       delay(500);
     }
 
     else if(digitalRead(down) == 0)
     {
       count--;
       if(count<0) count=25; delay(500); } else if(digitalRead(del) == 0) { id=count; getFingerprintEnroll(); return; } else if(digitalRead(enroll) == 0) { return; } } } void delet() { int count=0; lcd.clear(); lcd.print("Delete Finger "); lcd.setCursor(0,1); lcd.print("Location:"); while(1) { lcd.setCursor(9,1); lcd.print(count); if(digitalRead(up) == 0) { count++; if(count>25)
       count=0;
       delay(500);
     }
 
     else if(digitalRead(down) == 0)
     {
       count--;
       if(count<0)
       count=25;
       delay(500);
     }
     else if(digitalRead(del) == 0)
     {
          id=count;
          deleteFingerprint(id);
          return;
     }
 
       else if(digitalRead(enroll) == 0)
     {        
          return;
     }
 }
}
 
 
  
void unlockdoor()
{
delay(900);
 
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(1,0);
lcd.print("Access Granted");
lcd.setCursor(4,1);
lcd.println("WELCOME!!");
lcd.setCursor(15,1);
lcd.println(" ");
lcd.setCursor(16,1);
lcd.println(" ");
lcd.setCursor(14,1);
lcd.println(" ");
lcd.setCursor(13,1);
lcd.println(" ");
unlockbuzz();
 
for(pos = 180; pos>=0; pos-=5) // goes from 180 degrees to 0 degrees
{
myservo.write(pos); // tell servo to go to position in variable 'pos'
delay(5); // waits 15ms for the servo to reach the position
}
delay(2000);
 
 
 
delay(1000);
counterbeep();
 
delay(1000);
 
for(pos = 0; pos <= 180; pos +=5) // goes from 0 degrees to 180 degrees
{ // in steps of 1 degree
myservo.write(pos); // tell servo to go to position in variable 'pos'
delay(15);
 
 
int currentposition=0;
 
lcd.clear();
displayscreen();
 
}
}
 
//**********************************WRONG CODE FUNCTION*************************************************//
 
void incorrect()
{
delay(500);
lcd.clear();
lcd.setCursor(1,0);
lcd.print("CODE");
lcd.setCursor(6,0);
lcd.print("INCORRECT");
lcd.setCursor(15,1);
lcd.println(" ");
lcd.setCursor(4,1);
lcd.println("GET AWAY!!!");
 
lcd.setCursor(13,1);
lcd.println(" ");
Serial.println("CODE INCORRECT YOU ARE UNAUTHORIZED");
digitalWrite(redled, HIGH);
digitalWrite(buzz, HIGH);
delay(3000);
lcd.clear();
digitalWrite(redled, LOW);
digitalWrite(buzz,LOW);
displayscreen();
}
//****************************** CLEAR THE SCREEN!!!**********************//
void clearscreen()
{
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(0,1);
lcd.println(" ");
lcd.setCursor(0,2);
lcd.println(" ");
lcd.setCursor(0,3);
lcd.println(" ");
}
//******************************KEYPRESS***********************************//
void keypress()
{
 
 
 
digitalWrite(buzz, HIGH);
delay(50);
digitalWrite(buzz, LOW);
}
//********************************DISPALAY FUNCTION!!!***********************************************************//
void displayscreen()
{
 
lcd.setCursor(0,0);
lcd.println("*ENTER THE CODE*");
lcd.setCursor(1 ,1);
 
lcd.println("TO _/_ (OPEN)!!");
}
//*************************** ARM SERVO****************************************************************************//
void armservo()
{
 
for (pos=180;pos<=180;pos+=50)
{
myservo.write(pos);
delay(5);
}
delay(5000);
 
for(pos=180;pos>=0;pos-=50)
{
myservo.write(pos);
}
 
}

