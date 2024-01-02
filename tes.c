#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 20, 4);  // Change 0x27 to the I2C address of your LCD


const int reedSwitchPin = D3; // Digital pin 13
volatile int tipCount10 = 0;    // Counter for tip events
volatile int tipCount24 = 0;    // Counter for tip events
volatile float conversionFactor = 0.2;
float rain10=0;
float rain24=0;
unsigned long lastResetTime10 = 0; // Variable to store the last reset time
unsigned long lastResetTime24 = 0; // Variable to store the last reset time
// const unsigned long resetInterval = 86400000; // 1 minute in milliseconds


void IRAM_ATTR reedSwitchISR() {
  tipCount10++; // Increment the tip count when the reed switch is triggered
  rain10 = tipCount10 * conversionFactor;
  tipCount24++; // Increment the tip count when the reed switch is triggered
  rain24 = tipCount24 * conversionFactor;
  
}


void setup () {
  Serial.begin(9600);
  lcd.begin();
  lcd.clear();
 
  pinMode(reedSwitchPin, INPUT_PULLUP); // Enable internal pull-up resistor
  attachInterrupt(digitalPinToInterrupt(reedSwitchPin), reedSwitchISR, FALLING); // Attach ISR to the falling edge of the reed switch signal
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);    // Set the cursor to the second line
  lcd.print("Memulai");   // Display a label
  lcd.setCursor(0, 1);    // Set the cursor to the second line
  lcd.print("Sistem");   // Display a label
  delay(1000); 
  Serial.println("mulai");
}

void loop () {

  lcd.clear();
  lcd.setCursor(0, 0);    // Set the cursor to the second line
  lcd.print("CH10: ");   // Display a label
  lcd.print(rain10); 
  lcd.setCursor(0, 1);    // Set the cursor to the second line
  
}