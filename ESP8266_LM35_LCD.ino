#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTTYPE DHT11

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);

const int ledPin = D0;
const int lm_pin = A0;

// DHT Sensor
uint8_t DHTPin = D4;
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE); 

float temperature, humidity;

void setup() {
  
  pinMode(DHTPin, INPUT);
  Serial.begin(9600);
  dht.begin();
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);

  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  
}

void loop() {

  
  digitalWrite(ledPin, LOW);
  delay(200);
  digitalWrite(ledPin, HIGH);
  delay(2000);

  // For LM35
  int analogValue = analogRead(lm_pin);
  float millivolts = (analogValue/1024.0) * 3300; //3300 is the voltage provided by the NodeMCU
  float celsius = millivolts/10;
  float fahrenhiet = ((celsius * 9)/5 +32);

  //For DHT11
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  
  Serial.println("From LM35 ---- ");
  Serial.print("in DegreeCelsius: ");
  Serial.println(celsius);
  Serial.print("in Fahrenhiet :");
  Serial.println(fahrenhiet);
  Serial.println();
  Serial.println("From DHT11 ---- ");
  Serial.print("Temperature : ");
  Serial.println(temperature);
  Serial.print("Humidity : ");
  Serial.println(humidity);
  Serial.println("\n");

  lcd.setCursor(0,0);
  lcd.print("HumidDHT: ");
  lcd.setCursor(11,0);
  lcd.print(humidity);
  lcd.setCursor(0,1);
  lcd.print("TempDHT : ");
  lcd.setCursor(7,1);
  lcd.print(temperature);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TempLM35: ");
  lcd.setCursor(11,0);
  lcd.print(celsius);
  delay(2000);

  
}
