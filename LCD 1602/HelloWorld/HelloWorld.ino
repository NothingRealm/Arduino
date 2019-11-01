
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

void setup() {
  lcd.begin(16, 2);
  lcd.print("hello, world!");
}

void loop() {
  lcd.noDisplay();
  delay(500);
  lcd.display();
  delay(500);
}
