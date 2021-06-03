#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define POT_1_PIN 0
#define SERVO_1_PIN 9
#define POT_2_PIN 1
#define SERVO_2_PIN 10
#define POT_3_PIN 2
#define SERVO_3_PIN 11
#define MIN_CHANGES 3
#define DEGREE_DIF 3

// global variables
int inputVal1 = 0;  // variable to store the value coming from the potentiometer
int servoVal1 = 0;  // variable to store value of servo motor in degrees
int inputVal2 = 0;  // variable to store the value coming from the potentiometer
int servoVal2 = 0;  // variable to store value of servo motor in degrees
int inputVal3 = 0;  // variable to store the value coming from the potentiometer
int servoVal3 = 0;  // variable to store value of servo motor in degrees
int lastVal1 = 0, changes1 = 0;  // variables used for error dampning
int lastVal2 = 0, changes2 = 0;  // variables used for error dampning
int lastVal3 = 0, changes3 = 0;  // variables used for error dampning
Servo servo1;  // servo object
Servo servo2;  // servo object
Servo servo3;  // servo object
LiquidCrystal_I2C lcd(0x27, 16, 2);  // lcd object

void setup() {
  Serial.begin(9600);  // setup serial connection
  servo1.attach(SERVO_1_PIN);  // attach pin to servo
  servo2.attach(SERVO_2_PIN);  // attach pin to servo
  servo3.attach(SERVO_3_PIN);  // attach pin to servo
  lcd.init();  // initialize the lcd 
  lcd.backlight();  // enable lcd backlight
  // print message on lcd
  lcd.setCursor(0,0);
  lcd.print("   Tremurici!");

  // set initial position
  inputVal1 = analogRead(POT_1_PIN);
  inputVal2 = analogRead(POT_2_PIN);
  inputVal3 = analogRead(POT_3_PIN);
  servoVal1 = map(inputVal1, 0, 1023, 0, 180);
  servoVal2 = map(inputVal2, 0, 1023, 0, 180);
  servoVal3 = map(inputVal3, 0, 1023, 0, 180);
  servo1.write(servoVal1);
  delay(15); // wait for servo to reach position
  servo2.write(servoVal2);
  delay(15); // wait for servo to reach position
  servo3.write(servoVal3);
  delay(15); // wait for servo to reach position
}

void loop() {
  // read value from potentiometer
  inputVal1 = analogRead(POT_1_PIN);
  inputVal2 = analogRead(POT_2_PIN);
  inputVal3 = analogRead(POT_3_PIN);

  // debug
//  Serial.print("Pot values: ");
//  Serial.print(inputVal1);
//  Serial.print(" | ");
//  Serial.print(inputVal2);
//  Serial.print(" | ");
//  Serial.print(inputVal3);
//  Serial.print(" ---|||--- ");

  // map value to degrees
  servoVal1 = map(inputVal1, 0, 1023, 0, 180);
  servoVal2 = map(inputVal2, 0, 1023, 0, 180);
  servoVal3 = map(inputVal3, 0, 1023, 0, 180);

  // check if input is not changed by an error
  if (abs(servoVal1 - lastVal1) >= DEGREE_DIF) {
    changes1++;
  } else {
    changes1 = 0;
  }
  if (abs(servoVal2 - lastVal2) >= DEGREE_DIF) {
    changes2++;
  } else {
    changes2 = 0;
  }
  if (abs(servoVal3 - lastVal3) >= DEGREE_DIF) {
    changes3++;
  } else {
    changes3 = 0;
  }

  if (changes1 >= MIN_CHANGES) {
    servo1.write(servoVal1);
    delay(15); // wait for servo to reach position 
    lastVal1 = servoVal1;
    changes1 = 0;
  } 
  if (changes2 >= MIN_CHANGES) {
    servo2.write(servoVal2);
    delay(15); // wait for servo to reach position 
    lastVal2 = servoVal2;
    changes2 = 0;
  }
  if (changes3 >= MIN_CHANGES) {
    servo3.write(servoVal3);
    delay(15); // wait for servo to reach position 
    lastVal3 = servoVal3;
    changes3 = 0;
  }

//  Serial.print("Deg values: ");
//  Serial.print(lastVal1);
//  Serial.print(" | ");
//  Serial.print(lastVal2);
//  Serial.print(" | ");
//  Serial.println(lastVal3);

  // clear lcd second line
  lcd.setCursor(0,1);
  lcd.print("                ");
  // write angles to lcd
  lcd.setCursor(0, 1);
  lcd.print(lastVal1);
  lcd.setCursor(6, 1);
  lcd.print(lastVal2);
  lcd.setCursor(12, 1);
  lcd.print(lastVal3);
}
