#include<LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 13); 
 

const int pingPin = 7; 
const int echoPin = 6;
const int relayPin = 9; 
const int sumpPin = 8; 
const int voltagePin = A0; 
long int Htime;              //integer for storing high time
long int Ltime;                //integer for storing low time
float Ttime;            // integer for storing total time of a cycle
float frequency;
int sumppin =0;



void setup() {
   pinMode(relayPin, OUTPUT);
   pinMode(pingPin, OUTPUT);
   pinMode(sumpPin, INPUT);
   pinMode(voltagePin, INPUT);
   pinMode(echoPin, INPUT);
   pinMode(2,INPUT);
   Serial.begin(9600);
   lcd.begin(16, 2);  
   lcd.setCursor(3,0);       
   lcd.print("AUTOMATIC");
   delay(500);
   lcd.setCursor(2,1); 
   lcd.print("WATER LEVEL");
   delay(500);
   lcd.clear();
   lcd.setCursor(3,0); 
   lcd.print("CONTROLLER");
   delay(1000);
   lcd.clear();
}

void loop() {
   long duration, inches, cm;
   int tanklevel = 0; 
   float inputvoltage;
     lcd.clear();
     
   lcd.setCursor(0,0);
   lcd.print("sump level");
   Htime=pulseIn(2,HIGH);      //read high time
   Ltime=pulseIn(2,LOW);        //read low time
   Ttime = Htime+Ltime;
   frequency=1000000/Ttime;    //getting frequency with Ttime is in Micro seconds
   lcd.setCursor(0,1);
   if(frequency<50)
   {sumppin=0;
   }
   else
   {
    sumppin=1;
   }
    
   lcd.print(sumppin);
 
   delay(1000);
   lcd.clear();  
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   duration = pulseIn(echoPin, HIGH);
   cm = microsecondsToCentimeters(duration);
   lcd.setCursor(0,0);           
   lcd.print("Tank Empty"); 

   if(cm > 1000) {
      lcd.clear();
      lcd.setCursor(0,0);         
      lcd.print("Tank Empty"); 
      if(sumppin== 1)
      {
          inputvoltage = ReadVoltage();
          if(inputvoltage < 3.75)
          {
             digitalWrite(relayPin, LOW);
             lcd.setCursor(0,1);           
             lcd.print("V < 200 PUMP OFF"); 
          }
          else if(inputvoltage > 4.75)
          {
             digitalWrite(relayPin, LOW);
             lcd.setCursor(0,1);          
             lcd.print("V > 250 PUMP OFF");
          }
          else {
            digitalWrite(relayPin, HIGH);
            lcd.setCursor(0,1);           
            lcd.print("PUMP RUNNING"); 
          }
      }
      else {     
            lcd.setCursor(0,1);           
            lcd.print("SUMP TANK EMPTY"); 
      }
   }
   else if(cm < 10) {
      digitalWrite(relayPin, LOW);
      lcd.clear();
      lcd.setCursor(0,0);           
      lcd.print("Tank Full"); 
      lcd.setCursor(0,1);           
      lcd.print("PUMP OFF"); 
   }
   else {
      tanklevel = 100-(cm*100/990);
      lcd.clear();
      lcd.setCursor(0,0);           
      lcd.print("Tank Level");
      lcd.setCursor(2,1);           
      lcd.print(tanklevel);
      lcd.print(" %");
   }
   
 delay(1000);
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

float ReadVoltage() {
  int adcval;
  float voltage;
  adcval = analogRead(voltagePin);
  voltage =  adcval * (5.0 / 1023.0);
  return voltage;
}
