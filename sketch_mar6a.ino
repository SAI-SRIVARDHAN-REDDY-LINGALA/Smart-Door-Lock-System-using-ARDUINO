// SMART LOCK SYSTEM USING ARDUINO, BUZZER, SERVO MOTOR

// LIBRARIES
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Keypad.h>

// PINS
#define buzzer_pin 11      // BUZZER
#define servo_pin 10       // SERVO
#define MAX_LENGTH 4       // PASS LENGTH

// VARIABLES
Servo servo;                          // SERVO OBJ
LiquidCrystal_I2C lcd(0x27, 16, 2);   // LCD OBJ (I2C:0x27, 16x2)

// PASSWORDS
const char* passwords[] = {"0123", "1111", "2025"};  // PASS LIST
const int numPasswords = sizeof(passwords) / sizeof(passwords[0]);
char entered_pass[MAX_LENGTH + 1];    // ENTERED PASS

bool isLocked = true;   // INIT LOCKED
bool Reenter = true;    // FLAG RE-ENTER
byte digits = 0;        // DIGIT COUNT

// KEYPAD
const byte ROWS = 4;  
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte row_Pins[ROWS] = {9, 8, 7, 6};   // ROW PINS
byte col_Pins[COLS] = {5, 4, 3, 2};   // COL PINS
Keypad keypad(makeKeymap(keys), row_Pins, col_Pins, ROWS, COLS);  // KEYPAD OBJ

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(9600);             // SERIAL
  pinMode(buzzer_pin, OUTPUT);    // BUZZER PIN

  servo.attach(servo_pin);        // ATTACH SERVO
  lockDoor();                      // LOCKED POS

  lcd.init();                     // LCD INIT
  lcd.backlight();                // LCD BACKLIGHT
  lcd.print("DOOR LOCK SYSTEM");  // START MSG
  delay(2000);
  lcd.clear();
}

// ---------------- LOOP ----------------
void loop() {
  if (Reenter) {                  // ASK FOR PASS
    lcd.setCursor(0, 0);
    lcd.print("ENTER PASSWORD");
    Reenter = false;
  }

  char key = keypad.getKey();     // GET KEY
  if (key) {
    process_key(key);             // PROCESS INPUT
  }
}

// ---------------- PROCESS KEYS ----------------
void process_key(char key) {
  if (key == 'C') {               // RESET
    reset_Password();
  }
  else if (digits < MAX_LENGTH) { // STORE KEY
    entered_pass[digits++] = key;
    lcd.setCursor(digits + 4, 1);
    lcd.print("*");             // MASK

    if (digits == MAX_LENGTH) {   // CHECK PASS
      checkPassword();
    }
  }
}

// ---------------- CHECK PASSWORD ----------------
void checkPassword() {
  entered_pass[digits] = '\0';    // END STRING
  lcd.clear();

  bool isValid = false;           // MATCH FLAG
  for (int i = 0; i < numPasswords; i++) {
    if (strcmp(entered_pass, passwords[i]) == 0) {
      isValid = true;
      break;
    }
  }

  if (isValid) {                  // CORRECT PASS
    isLocked = !isLocked;         // TOGGLE
    servo.write(isLocked ? 50 : 110); // SERVO MOVE
    buzz(1);                      // 1 BUZZ

    lcd.setCursor(0, 0);
    lcd.print("ACCESS GRANTED");  // MSG
    lcd.setCursor(0, 1);
    lcd.print(isLocked ? "DOOR LOCKED" : "DOOR UNLOCKED");
  }
  else {                          // WRONG PASS
    buzz(3);                      // 3 BUZZ
    lcd.setCursor(0, 0);
    lcd.print("ACCESS DENIED");   // MSG
    lcd.setCursor(0, 1);
    lcd.print("WRONG PASSWORD");
  }

  delay(1500);
  reset_Password();               // RESET
}

// ---------------- RESET PASSWORD ----------------
void reset_Password() {
  digits = 0;
  
  lcd.clear();                    // CLEAR LCD
  lcd.setCursor(0, 0);
  lcd.print("RESETTING...");      // SHOW RESET MSG
  delay(800);                     // SHORT DELAY TO SHOW MESSAGE
  
  memset(entered_pass, 0, sizeof(entered_pass));  // CLEAR BUF
  Reenter = true;                 // READY AGAIN
  lcd.clear();                    // CLEAR LCD AFTER RESET
}

// ---------------- BUZZER ----------------
void buzz(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(buzzer_pin, HIGH);
    delay(100);
    digitalWrite(buzzer_pin, LOW);
    delay(100);
  }
}


void lockDoor(){                      // Lock initially  
  servo.write(50);  
  lcd.clear();  
  lcd.print("LOCKED");  
}