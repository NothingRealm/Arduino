#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
 

char hexaKeys[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

byte rowPins[4] = {36,34,32,30}; //connect to the row pinouts of the keypad
byte colPins[4] = {28,26,24,22}; //connect to the column pinouts of the keypad

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

Keypad keypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, 4, 4 );


void setup()
{
  lcd.init();                      // initialize the lcd 
  
  
  lcd.backlight();
  delay(500);

}
 
void loop()
{
  char customKey = keypad.waitForKey();
  lcd.print(customKey);
}
