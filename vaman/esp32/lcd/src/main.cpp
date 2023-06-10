#include <WiFi.h>
#include <ArduinoOTA.h>
#include <LiquidCrystal.h>
#include "credentials.h"
#define MAX_ADC 4095.0    // Maximum value of 12 bit ADC

LiquidCrystal lcd(19, 23, 18, 17, 16, 15);

//R1 is known resistance
//R2 is unknown resistance
float V_out, R1=1000.0, R2; 
void OTAsetup() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) delay(1000);
    ArduinoOTA.begin();
}
void OTAloop() {
    ArduinoOTA.handle();
}
void setup(){
    OTAsetup();
    lcd.begin(16, 2);
}
void loop() {
    OTAloop();
    V_out=analogRead(34);//reading from Pin34 of ESP32
    //V_out is the actual voltage at the junction of R1 and R2
    R2 = R1/((MAX_ADC)/(V_out)-1.0);
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    // Print a message to the LCD.
    lcd.print("Resistance");
    lcd.setCursor(0, 1);
    lcd.print(R2);
    lcd.print(" Ohms");  
}
