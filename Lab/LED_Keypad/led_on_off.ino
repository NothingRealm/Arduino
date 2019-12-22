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

enum stateSTR{state_on,state_off};
enum stateSTR state=state_on;
void setup(){
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
  digitalWrite(ledPin, HIGH);   // sets the LED on
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
  state=state_on;

  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  
}

void loop(){
  char key = keypad.getKey();
  if (flag){
    lcd.clear();
   if(state==state_on){
      lcd.print("on");
   }
   else{
     lcd.print("off");
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
            state=state_on;

        break;
        case 'B':
            state=state_off;

        break;

        case '1':
        if(state==state_on)
          digitalWrite(2,HIGH);
        else 
         digitalWrite(2,LOW);
         break;


         case '2':
        if(state==state_on)
          digitalWrite(3,HIGH);
        else 
         digitalWrite(3,LOW);
         break;
         case '3':
        if(state==state_on)
          digitalWrite(4,HIGH);
        else 
         digitalWrite(4,LOW);
         break;
         case '4':
        if(state==state_on)
          digitalWrite(5,HIGH);
        else 
         digitalWrite(5,LOW);
         break;


    
      }
    break;
    case HOLD:
      switch (key){
      }
    break;
  }
}
