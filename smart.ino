#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include<BH1750.h>

// LCD configuration
LiquidCrystal_I2C lcd(0x27, 16, 2);

// DHT11 configuration
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

//PIR configuration
#define PIRPIN 3

#define MQ135PIN A0

BH1750 lightMeter;
//MQ135 configuration

void setup() {

  lcd.init();
  lcd.backlight();

  dht.begin();

 pinMode(PIRPIN, INPUT);

 lightMeter.begin();

  lcd.setCursor(0, 0);
  lcd.print("SMART STUDIO");

  lcd.setCursor(0, 1);
  lcd.print("Starting...");

  delay(2000);
  lcd.clear();
}

void loop() {

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int motion = digitalRead(PIRPIN);
  int airQuality = analogRead(MQ135PIN);
  float lux= lightMeter.readLightLevel();
  // Check sensor readings

  // frame 1
  if (isnan(humidity) || isnan(temperature)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error    ");

    lcd.setCursor(0, 1);
    lcd.print("Check DHT11     ");

    delay(2000);
    
  }
  else{

    lcd.clear();
  // Display temperature
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);
  lcd.print((char)223);
  lcd.print("C   ");

  // Display humidity
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity, 1);
  lcd.print("%   ");

  delay(3000);
  }
 
  motion = digitalRead(PIRPIN);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("MOTION STATUS:");

  lcd.setCursor(0,1);

  if (motion==HIGH){
    lcd.print("Motion Detected");
  }
  else{
    lcd.print("No Motion");
  }
  delay(3000);
   //FRAME 3: Air Quality
   airQuality = analogRead(MQ135PIN);

   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("AIR QUALITY");

   lcd.setCursor(0,1);
   lcd.print("Sensor: ");
   lcd.print(airQuality);

delay(3000);
  //frame 4 gy30
  lux=lightMeter.readLightLevel();

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("LIGHT INTENSITY");

  lcd.setCursor(0,1);

  if(lux<0){
    lcd.print("Sensor Error!!!");
  }
  else{
    lcd.print(lux,1);
    lcd.print(" lux");
  }
  delay(3000);

}
