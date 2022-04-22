#include "lib/DHT.h"
#include "lib/LiquidCrystal_I2C.h"

#define DHTPIN 4
#define DHTTYPE DHT22


LiquidCrystal_I2C lcd(0x3F,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
DHT dht(DHTPIN, DHTTYPE);


void setup()
{
  lcd.init();                   
  lcd.backlight();
  Serial.begin(9600);

  
  lcd.setCursor(0,0);
  lcd.print("Ivan Ivan Pupkin");
  lcd.setCursor(0,1);
  lcd.print("5023");
  lcd.setCursor(0,2);
  lcd.print("Temperature:      C");
  lcd.setCursor(0,3);
  lcd.print("Humidity:      %");
}

void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  lcd.setCursor(12,2);
  lcd.print(t);
  lcd.setCursor(9,3);
  lcd.print(h);
  delay(100);
}
