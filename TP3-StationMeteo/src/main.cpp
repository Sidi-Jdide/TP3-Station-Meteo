

#include <Arduino.h>

//BME
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

//Wifi manager

#include <WiFi.h>
#include <Update.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <WifiManager.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

// LED on GPIO2
int ledPin = 2;

const char* ssid ="Esp32AP";
const char* password ="Lemina24-09-2014";

WiFiManager wm;
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

void setup() {
  Serial.begin(115200);

  pinMode(ledPin , OUTPUT);      // set the LED pin mode
  Serial.begin(9600);
  delay(10);
  lcd.init();
  lcd.backlight();
  lcd.print("Test LCD");
  lcd.setCursor(0, 1);
  lcd.print((char)200);
  wm.resetSettings();  // effacer le profil d'autentification


    //BME

  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

    Serial.println("\n");
    Serial.print("Try to connect to :");
    Serial.println(ssid);
    if (! wm.autoConnect(ssid, password)) {
      Serial.println("non connecte :") ;
    }
   else {
      Serial.print("connecte a:") ;
      Serial.println(ssid) ;
    }
    
}

void loop() {
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println("*C");

  lcd.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println("hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println("m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println("%");

  Serial.println();
  delay(1000);
}