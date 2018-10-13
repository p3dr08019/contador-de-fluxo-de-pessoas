#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h"
#define SENSOR01 6
#define SENSOR02 7
#define RTC 10
LiquidCrystal lcd(2,4,10,11,12,13);
unsigned int contSaida = 0;
unsigned int contEntrada = 0;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

RTC_DS3231 rtc;

void setup() {
  //Serial.begin(115200);
  Serial.begin(9600);
  pinMode(SENSOR01, INPUT);
  pinMode(SENSOR02, INPUT);
  lcd.begin(16,2);
  rtc.begin();
lcd.print("ola mundo !!");

if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}
void loop() {
  DateTime now = rtc.now();
  if (digitalRead(SENSOR02) == LOW) {
    saida();
  }else{
    if (digitalRead(SENSOR01) == LOW) {
      entrada();
    }
  }
}

int saida(){
  DateTime now = rtc.now();
  int auxiliar = 0;
    if(digitalRead(SENSOR02) == LOW){
      Serial.println("Sensor 02 Obstruido");
      while(digitalRead(SENSOR02) == LOW){
        if(digitalRead(SENSOR01) == LOW){
          //Serial.println("Sensor 02 e 01 Obstruido");
          while(digitalRead(SENSOR01) == LOW){
            if(digitalRead(SENSOR02) == HIGH){
              Serial.println("Sensor 02 Desobstruido");
              auxiliar = 1;
              while(auxiliar && digitalRead(SENSOR02)==HIGH){
                if(digitalRead(SENSOR01)==HIGH && digitalRead(SENSOR02)==HIGH){
                  contSaida = contSaida + 1;
                      Serial.println("Saida Confirmada");
                      Serial.println(contEntrada - contSaida);
                      Serial.println();
                      Serial.print(now.year(), DEC);
                      Serial.print('/');
                      Serial.print(now.month(), DEC);
                      Serial.print('/');
                      Serial.print(now.day(), DEC);
                      Serial.print(" (");
                      Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
                      Serial.print(") ");
                      Serial.print(now.hour(), DEC);
                      Serial.print(':');
                      Serial.print(now.minute(), DEC);
                      Serial.print(':');
                      Serial.print(now.second(), DEC);
                      Serial.println();
                      delay (1000);
                      
                      return 1;              
                }
              }
              Serial.println("Sensor 02 Obstruido");
            }
          }
          Serial.println("Sensor 01 Desobstruido");
        }
      }
    Serial.println("Sensor 02 Desobstruido");  
    }
  
  return 0;
}

int entrada(){
  DateTime now = rtc.now();
  int auxiliar = 0;
  if(digitalRead(SENSOR01) == LOW){
       Serial.println("Sensor 01 Obstruido");
         while(digitalRead(SENSOR01) == LOW){
           if(digitalRead(SENSOR02) == LOW){
             Serial.println("Sensor 01 e 02 Obstruido");
               while(digitalRead(SENSOR02) == LOW){
                 if(digitalRead(SENSOR01) == HIGH){
                   Serial.println("Sensor 01 Desobstruido");
                   auxiliar = 1;
                   while(auxiliar && digitalRead(SENSOR01) == HIGH){
                     if(digitalRead(SENSOR02) == HIGH && digitalRead(SENSOR01) == HIGH){
                      contEntrada = contEntrada +1;                      
                      Serial.println("Sensor 01 Desobstruido");
                      Serial.println("Sensor 02 Desobstruido");
                      Serial.println("Entrada Confirmada");
                      Serial.println(contEntrada - contSaida);
                      Serial.println();
                      Serial.print(now.year(), DEC);
                      Serial.print('/');
                      Serial.print(now.month(), DEC);
                      Serial.print('/');
                      Serial.print(now.day(), DEC);
                      Serial.print(" (");
                      Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
                      Serial.print(") ");
                      Serial.print(now.hour(), DEC);
                      Serial.print(':');
                      Serial.print(now.minute(), DEC);
                      Serial.print(':');
                      Serial.print(now.second(), DEC);
                      Serial.println();
                       return 1;   
                     }
                   }
                   Serial.println("Sensor 01 Obstruido");
                 }
               }
               Serial.println("Sensor 02 Desobstruido");
           }
         }
         Serial.println("Sensor 01 Desobstruido");
  }
  return 0;
}
