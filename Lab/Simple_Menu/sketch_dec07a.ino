#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
        {'1','2','3','A'},
        {'4','5','6','B'},
        {'7','8','9','C'},
        {'*','0','#','D'}
        };
byte colPins[COLS] = {37, 35, 33, 31}; //connect to the row pinouts of the keypad
byte rowPins[ROWS] = {45,43, 41, 39}; //connect to the column pinouts of the keypad
bool flag = true;
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
byte ledPin = 13;

enum stateSTR{main_menu,menu_A,menu_B,menu_C,menu_D};
enum stateSTR state=main_menu;
void setup(){
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
  digitalWrite(ledPin, HIGH);   // sets the LED on
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
  state=main_menu;
}

void loop(){
  char key = keypad.getKey();
  if (flag){
    lcd.clear();
    if(state==main_menu){
      lcd.print("A:menuA B:menuB");
      lcd.setCursor(0,1);
      lcd.print("C:menuC D:menuD");
    }
    else if(state==menu_A){
      lcd.print("this is menu A");
    }
    else if(state==menu_B){
      lcd.print("this is menu B");
    }
    else if(state==menu_C){
      lcd.print("this is menu C");
    }
    else if(state==menu_D){
      lcd.print("this is menu D");
    }
  flag = false;
  }
  //delay(150);
  
}

//take care of some special events
void keypadEvent(KeypadEvent key){
  switch (keypad.getState()){
    case PRESSED:

    break;
    case RELEASED:
    flag = true;
      switch (key){
        case 'A':
            state=menu_A;

        break;
        case 'B':
            state=menu_B;

        break;
        case 'C':
            state=menu_C;

        break;
        case 'D':
            state=menu_D;

        break;
        case '#':
            state=main_menu;

        break;
        
      }
    break;
    case HOLD:
      switch (key){
      }
    break;
  }
}
