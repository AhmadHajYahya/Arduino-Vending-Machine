#include <LiquidCrystal_I2C.h>

#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4;
const byte COLS = 3;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {8, 7, 6};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

Servo myservo1;
Servo myservo2;
Servo myservo3;

Servo myservoR;
int pos = 0;
char customKey;

#define step_pin 23    // Define pin 3 as the steps pin
#define dir_pin 22    // Define pin 2 as the direction pin
#define MS1 25     // Define pin 5 as "MS1"
#define MS2 24       // Define pin 4 as "MS2"

#define MOTOR_SPEED 1500
#define MOTOR_ROTATE_LOOP 500
int lookup [8] = { B01000, B01100, B00110, B00110, B00010, B00011, B00001, B01001};
void setup()
{

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("CHOOSE A DRINK!");
  myservo1.attach(A1);
  myservo1.write(90);
  myservo2.attach(A2);
  myservo2.write(90);
  myservo3.attach(A3);
  myservo3.write(90);

  myservoR.attach(A4);
  myservoR.write(0);

  Serial.begin(9600);


  pinMode(MS1, OUTPUT);     // Configures "MS1" as output
  pinMode(MS2, OUTPUT);     // Configures "MS2" as output
  pinMode(dir_pin, OUTPUT);    // Configures "dir_pin" as output
  pinMode(step_pin, OUTPUT);    // Configures "step_pin" as output
  digitalWrite(MS1, LOW);      // Configures the steps division (see above)
  digitalWrite(MS2, LOW);    // Configures the steps division (see above)
  digitalWrite(dir_pin, LOW);   // Sense (HIGH = anti-clockwise / LOW = clockwise) - It can be also changed

}

void loop()
{
  lcd.setCursor(0, 0);
  lcd.print("CHOOSE A DRINK!");
  customKey = customKeypad.getKey();
  Serial.println(customKey);
  if (customKey == '1')
  {
    lcd.setCursor(0, 0);
    lcd.print("YOU'VE CHOSED   ");
    lcd.setCursor(1, 5);
    lcd.print("COLA");
    Serial.println(customKey);


    moveRight(1100);
    myservo1.write(10);

    delay(3000);
   
    myservo1.write(90);
    delay(1000);
    
    moveLeft(1100);

    swepClock();
    delay(3000);
    
    swepAntiClock();
    lcd.clear();

  }


  if (customKey == '2')
  {
    lcd.setCursor(0, 0);
    lcd.print("YOU'VE CHOSED  ");
    lcd.setCursor(1, 4);
    lcd.print("ORANGE");
    Serial.println(customKey);

    moveRight(3200);
    myservo2.write(10);

    delay(3000);
    
    myservo2.write(90);
    delay(1000);
    
    moveLeft(3200);
    
    swepClock();
    delay(3000);
    
    swepAntiClock();

    lcd.clear();
  }

  if (customKey == '3')
  {
    lcd.setCursor(0, 0);
    lcd.print("YOU'VE CHOSED  ");
    lcd.setCursor(1, 4);
    lcd.print("FANTA");
    Serial.println(customKey);

    moveRight(5500);
 
    myservo3.write(10);
    delay(3000);
    
    myservo3.write(90);
    delay(1000);
    
    moveLeft(5500);
    
    swepClock();
    delay(3000);
    
    swepAntiClock();

    lcd.clear();

  }

  customKey = '5';


}

//==================

void moveRight(int loopsNum)
{
  digitalWrite(dir_pin, HIGH); // move in the LOW direction
  startmotor(loopsNum);
}

//==================

void moveLeft(int loopsNum)
{
  digitalWrite(dir_pin, LOW); // move in the LOW direction
  startmotor(loopsNum);
}

//==================

void startmotor(int loopsNum) {
  for (int j = 0 ; j < loopsNum; ++j)
  {
    digitalWrite(step_pin, LOW);
    delay(1);
    digitalWrite(step_pin, HIGH);
    delay(1);

  }
}

//==================

void swepClock() {
  for (pos = 0; pos <= 90; pos += 1) // goes from 0 degrees to 180 degrees
  { // in steps of 1 degree
    myservoR.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15ms for the servo to reach the position
  }
}
//==================

void swepAntiClock() {
  for (pos = 90; pos >= 0; pos -= 1) // goes from 0 degrees to 180 degrees
  { // in steps of 1 degree
    myservoR.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15ms for the servo to reach the position
  }
}









