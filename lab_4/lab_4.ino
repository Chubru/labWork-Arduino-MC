#include <avr/wdt.h>

int number1;
int number2;
bool flag = 1;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50);
  Serial.println();
  Serial.println("Начинаем суммировать:");
}

void loop() {
  if (flag) {
    if (Serial.available() > 0) {
      wdt_enable(WDTO_2S);
      number1 = Serial.parseInt(); 
      Serial.print(number1);
      Serial.print(" + ");
      flag = false;
    }
  }
  if (!flag) {
    if (Serial.available() > 0) {
      wdt_reset();
      number2 = Serial.parseInt(); 
      Serial.print(number2);
      Serial.print(" = "); 
      number1 += number2;
      Serial.println(number1);
      Serial.print(number1);
      Serial.print(" + ");
    }
  }

}
