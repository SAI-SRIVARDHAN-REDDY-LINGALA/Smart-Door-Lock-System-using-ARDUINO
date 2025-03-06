  //SMART LOCK SYSTEM USING ARDUINO,BUZZER,SERVO MOTOR


  //LIBRARIES 
 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Keypad.h>
  
          // PINS

  // BUZZER 
  #define buzzer_pin 11
  // SERVO MOTOR 
  #define servo_pin   10
  //PASSWORD 
  #define MAX_LENGTH  4

  // for keypad will write later in code 


          //VARIABLES 
  //SERVO OBJECT 
  Servo servo;   // to use servo function(angle,....)

  //LCD  OBJECT 
  LiquidCrystal_I2C lcd( 0x27, 16, 2); // 0x27 is general adrress ,16 columns, 2 rows (ATRIBUTES)

  //PASSWORD 
  const char* password = "0123";// pointer for  constant string 
  char entered_pass[MAX_LENGTH + 1];

  bool isLocked = true;   //intially door was locked 
  bool Reenter = true;   // if specific button pressed ,we can enter from start 
  byte digits = 0;       // no of digits/char entered 


  //KEY PAD 

  const byte ROWS = 4; //NO OF ROWS,COLMNS  
  const byte COLS = 4;

  char keys[ROWS][COLS] = {  
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
  };  //KEYPAD LAYOUT  

  byte row_Pins[ROWS] = {9, 8, 7, 6};   //PINS CONNECTIONS FOR ROWS,COLMNS
  byte col_Pins[COLS] = {5, 4, 3, 2};

  Keypad keypad(makeKeymap(keys), row_Pins, col_Pins, ROWS, COLS);   // KEYPAD OBJECT TO READ INPUT 




         //SETUP (INITIALISATIONS)

void setup(){
      Serial.begin(9600);   // for serial monitor to initialise 

      pinMode(buzzer_pin,OUTPUT);    

      servo.attach(servo_pin);
      servo.write (50);    // LOCKED ---> 50

      lcd.init();             // intialising lcd I2c comm,.......
      lcd.backlight();        // ON BACKLIGHT TO DISPLAY 
      lcd.print("DOOR LOCK SYSTEM");   // GLANCE OF PROJECT FOR 2sec 
      delay(2000);
      lcd.clear();
  }



           //MAIN LOOP 
void loop(){ 

      if(Reenter){     //TAKE INPUT FROM START 
        lcd.setCursor(0 ,0);
        lcd.print("ENTER PASSWORD");
        Reenter = false;   //TO AVOID UNNECCESARY INPUT 
      }

    char key = keypad.getKey();   // THESE KEYBOARD FUNCTION TAKES USER INPUTS
    if (key){     // TRUE IF KEY IS PRESSED 
        process_key(key);
    }

}

void process_key(char key){    // TO CHECK KEY -->PASSWORD/NOT/RESET 
    if(key == 'C'){     //RESET
       reset_Password();
    }

    else if(digits < MAX_LENGTH){  // STORING AND CHECKING  PASSWORD 
      entered_pass[digits++]=key;   
      lcd.setCursor(digits + 4, 1);    
      lcd.print(" * ");    // FOR PRIVACY 

     if(digits == MAX_LENGTH){  // TO CHECK PASSWORD 
       check_Password();
     }

    }

}



void check_Password(){      // CHECKS PASSWORD 
      entered_pass[digits]='\0'; // TO MAKE IT STRING 
      lcd.clear();

      if(strcmp(entered_pass,password)==0){  // IF CORRECT PASSWORD 
            isLocked=!isLocked;
            servo.write(isLocked ? 50 : 110);  //ROTATES 
            buzz(1);  
      }else{
        buzz(3);
        lcd.print(" WRONG PASSWORD ");  
        
      }
  
  delay(1000);
  reset_Password();   // FOR NEXT TRY 

}


void reset_Password(){
  digits = 0;
  lcd.clear();  // Clear LCD
  memset(entered_pass, 0, sizeof( entered_pass)); // Clear  PREVIOUS entered password 
  Reenter = true;  // Request LCD update
}


void buzz(int times){ // BUZZER FUNCTION TO RING BASED ON RIGHT OR WRONG PASSWORD 
   for (int i = 0; i < times; i++) {
    digitalWrite(buzzer_pin, HIGH);
    delay(100);
    digitalWrite(buzzer_pin, LOW);
    delay(100);
  }
}













