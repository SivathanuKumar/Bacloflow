#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(128, 32, &Wire, OLED_RESET);

const int Charge = A2;
const int Discharge = A0;
float internal_cap = 250; //uF
int voltage;
float unknwn_cap; //uF
void setup() {
  Serial.begin(9600);
  pinMode(Discharge,OUTPUT);
  pinMode(Charge,OUTPUT);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.display();
  delay(1000); 
  display.clearDisplay();
  display.display();
  delay(1000);
    display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print(F("Version 2.0          "));
  display.display();
  delay(200);
  //display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  //display.setCursor(0,1);
  display.print(F("Bacloflow"));
  display.display();
  delay(2000);
  display.clearDisplay();

}

void loop() {
      int value;
      static float maxi = 0;
      static float mini = 70;


//Finding the capacitance:
      Capacitance:
      pinMode (Discharge, INPUT);
      digitalWrite (Charge, HIGH);
      voltage = analogRead(Discharge);
      digitalWrite(Charge, LOW);
      pinMode (Discharge, OUTPUT);
      delay (100);
        if (voltage<1024){
          unknwn_cap = ((internal_cap * voltage)/(1024.0-voltage));
          maxi = (unknwn_cap>maxi) ? unknwn_cap:maxi;
          mini = (unknwn_cap<mini) ? unknwn_cap:mini;
          float step = (maxi-mini)*0.1;
          maxi -= step;
          mini += step;
          //Serial.print(maxi);
          //Serial.print("\t");
          //Serial.print(mini);
          //Serial.print("\t");
          Serial.print(unknwn_cap);
          Serial.print("\t");
          float threshold = maxi*0.8 + mini*0.2;
          Serial.println(threshold);
          //Serial.print("\t");
          //Serial.print("\n");
          delay (100);
            if (threshold<74){
              //Serial.println("flow detected");
              display.setTextSize(0.8);
              display.setTextColor(SSD1306_WHITE);
              display.setCursor(0,0);
                            display.print(threshold);
              display.println(F("uF            ")); 

              display.display();
              delay(200);
              display.setTextSize(2.5);
              display.setTextColor(SSD1306_WHITE);
              display.print(F("Flow        "));
              display.display();
              delay(200);
              display.clearDisplay();
            }

            else{
              //Serial.println(" No flow");
              display.setTextSize(0.8);
              display.setTextColor(SSD1306_WHITE);
              display.setCursor(0,0);
              display.print(threshold);
              display.println(F("uF            "));
              //display.println(F("\n"));                            
              display.display();
              delay(200);
              display.setTextSize(2.5);
              display.setTextColor(SSD1306_WHITE);
              display.print(F("No Flow   ")); 
              display.display();
              delay(200);
              display.clearDisplay();
            }          
            //if (unknwn_cap>20.0){
                 // Serial.print("  Flow  \n ");
                 // Serial.print(unknwn_cap,2);
                  //Serial.print("pF");
                 // }                  
             // else {
                //Serial.print("  No Catheter ");
               // delay(200);
               // goto Capacitance;
         // }
        }
        else{
          //Serial.print("No Catheter");
          }
       delay (1000);        
      
    }

