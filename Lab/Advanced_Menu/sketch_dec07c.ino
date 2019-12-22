#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include<Servo.h>

#define TEMP_PIN 7
#define SERVO_PIN 52
#define HUM_PIN 2
#define RELAY_PIN1 50

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns

String PASSWORD = "1";

char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte colPins[COLS] = {37, 35, 33, 31}; //connect to the row pinouts of the keypad
byte rowPins[ROWS] = {45, 43, 41, 39}; //connect to the column pinouts of the keypad
bool flag = true;

int tempr = 0;
int hum = 0;
int turndeg = 0;
int new_turndeg=0;
int temp_treshhold = 40;
bool logged_in = 0;
bool hum_enable =0;
int update_counter=0;
Servo myservo;


Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
byte ledPin = 13;

enum stateSTR
{
  menu_login,
  menu_display,
  menu_temp,
  menu_hum,
  menu_servo
};
enum stateSTR state = menu_login;
void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);    // sets the digital pin as output
  digitalWrite(ledPin, HIGH); // sets the LED on
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad


  pinMode(SERVO_PIN,OUTPUT);
  myservo.attach(SERVO_PIN);
  pinMode(TEMP_PIN,INPUT);
  pinMode(HUM_PIN, INPUT);
  pinMode(RELAY_PIN1, OUTPUT);

}

void loop()
{
  char key = keypad.getKey();
  if (flag)
  {
    lcd.clear();
    if (state == menu_login)
    {

      lcd.print("Enter password:");
      lcd.setCursor(0, 1);

      char input = keypad.waitForKey();
      int char_num = 0;
      String input_string = "";

      while (input != '#')
      {
        input_string.concat(input);
        lcd.print("*");
        char_num++;
        input = keypad.waitForKey();
      }

      if (input_string.compareTo(PASSWORD) == 0)
      {
        logged_in = 1;
        state = menu_display;
        flag = true;
      }
      else
      {
        lcd.print("wrong password");
        flag = true;
        delay(2000);
      }
    }
    else if (state == menu_display)
    {
      lcd.print("temperature: ");
      lcd.print(tempr);
      lcd.setCursor(0, 1);
      lcd.print("hum:");
      if (hum)
        lcd.print("high ");
      else
      {
        lcd.print("low  ");
      }

      lcd.print("deg:");
      lcd.print(new_turndeg);
    }
    else if (state == menu_temp)
    {
      lcd.print("Enter temperature");
      String input = getInput();
      int new_temp = input.toInt();
      temp_treshhold = new_temp;
      state = menu_display;
      flag = true;
    }
    else if (state == menu_hum)
    {
      lcd.print("Enter humidity");
      lcd.setCursor(0,1);
      lcd.print("0: disable, 1:enable");
      char input_char=keypad.waitForKey();
      if(input_char=='1')
        hum_enable=1;
      else if(input_char=='0')
        hum_enable=0;
      state = menu_display;
      flag = true;
    }
    else if(state==menu_servo){
      lcd.print("Enter servo degree");
      String input = getInput();
      int new_turn = input.toInt();
      new_turndeg = new_turn;
      state = menu_display;
      flag = true;
    }


    //    else if(state==menu_A){
    //      lcd.print("this is menu A");
    //    }
    //    else if(state==menu_B){
    //      lcd.print("this is menu B");
    //    }
    //    else if(state==menu_C){
    //      lcd.print("this is menu C");
    //    }
    //    else if(state==menu_D){
    //      lcd.print("this is menu D");
    //    }
    flag = false;
  }
  else{
    //temp input from sensor
    int temp_input=analogRead(TEMP_PIN);
    tempr=(temp_input*500)/1023;
    Serial.print(update_counter);

    if (tempr > temp_treshhold) {

        digitalWrite(RELAY_PIN1,HIGH);
        Serial.print("True");

    } else
    {
        Serial.print("false");
        digitalWrite(RELAY_PIN1,LOW);
    }
    

    //hummmmmmmmmmmmmm

    hum = digitalRead(HUM_PIN);

    //setting servo
    myservo.write(new_turndeg);

    update_counter++;
    if (update_counter>=100)
    {
      update_counter=0;
      flag=true;
    }


  
    
    

  }

  delay(10);
}

//take care of some special events
void keypadEvent(KeypadEvent key)
{
  switch (keypad.getState())
  {
  case PRESSED:

    break;
  case RELEASED:
    flag = true;
    if (logged_in)
    {
      switch (key)
      {

      case 'A':
        state = menu_temp;
        break;
      case 'B':
        state = menu_hum;

        break;
      case 'C':
        state = menu_servo;

        break;
      case 'D':
        //state=menu_;

        break;
      }
    }
    break;
  case HOLD:
    switch (key)
    {
    }
    break;
  }
}

String getInput()
{
  lcd.setCursor(0, 1);

  char input = keypad.waitForKey();
  int char_num = 0;
  String input_string = "";

  while (input != '#')
  {
    input_string.concat(input);
    lcd.print(input);
    char_num++;
    input = keypad.waitForKey();
  }
  return input_string;
}