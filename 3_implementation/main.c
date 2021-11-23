include <Adafruit_Fingerprint.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); //Serial Communications

//Created instances
LiquidCrystal_I2C lcd(0x27, 16, 2); 
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

int relayPin = 9;

void setup()
{
 pinMode(relayPin, OUTPUT);
 digitalWrite(relayPin, LOW);
 Serial.begin(9600);
 while (!Serial); 
 delay(100);

 lcd.begin();
 lcd.setCursor(0, 0);
 lcd.printf("Fingerprint Door");
 lcd.setCursor(0, 1);
 lcd.printf("lock by prateek");
 delay(3000);
 lcd.clear();

 // set the data rate for the sensor serial port
 finger.begin(57600);

 if (finger.verifyPassword()) {
   lcd.setCursor(0, 0);
   lcd.printf("  FingerPrint ");
   lcd.setCursor(0, 1);
   lcd.printf("Sensor Connected");
 }

 else  {
   lcd.setCursor(0, 0);
   lcd.printf("Unable to found");
   lcd.setCursor(0, 1);
   lcd.printf("Sensor");
   delay(3000);
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.printf("Check Connections");

   while (1) {
     delay(1);
   }
 }
 lcd.clear();
}

void loop()                     // run over and over again
{
 getFingerprintIDez();
 delay(50);            //don't need to run this at full speed.
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
 uint8_t p = finger.getImage();
 if (p != FINGERPRINT_OK)  {
   lcd.setCursor(0, 0);
   lcd.printf("  Waiting For");
   lcd.setCursor(0, 1);
   lcd.print("  Valid Finger");
   return -1;
 }

 p = finger.image2Tz();
 if (p != FINGERPRINT_OK)  {
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("  Messy Image");
   lcd.setCursor(0, 1);
   lcd.printf("  Try Again");
   delay(3000);
   lcd.clear();
   return -1;
 }

 p = finger.fingerFastSearch();
 if (p != FINGERPRINT_OK)  {
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.printf("Not Valid Finger");
   delay(3000);
   lcd.clear();
   return -1;
 }

 // found a match!
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.printf("  Door Unlocked");
 lcd.setCursor(0, 1);
 lcd.print("    Welcome");
 digitalWrite(relayPin, HIGH);
 delay(3000);
 digitalWrite(relayPin, LOW);
 lcd.clear();
 return finger.fingerID;
}
