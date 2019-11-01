

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 4, d5 = 5, d6 =6, d7 = 7 , btn1=8 ,btn2=9;
int btn1State=0;
int btn2State=0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Hello World");

  pinMode(btn1,INPUT_PULLUP);
  pinMode(btn2,INPUT_PULLUP);
  delay(1000);
}

void loop() {
  btn1State=digitalRead(btn1);
  btn2State=digitalRead(btn2);

  if(btn1State==LOW){
    lcd.scrollDisplayLeft();
  }else if(btn2State==LOW){
    lcd.scrollDisplayRight();
  }

  delay(300);
}

