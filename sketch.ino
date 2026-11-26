#include <Keypad.h>
#include <LiquidCrystal.h>
#define BUZZER 7


LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);


const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(
  makeKeymap(keys),
  rowPins,
  colPins,
  ROWS,
  COLS
);


String password = "1234";
String enteredPassword = "";

void setup() {
   pinMode(BUZZER, OUTPUT);

  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("Digital Lock");

  lcd.setCursor(0, 1);
  lcd.print("Enter Password");

  delay(2000);
  showInputScreen();
}

void loop() {
  char key = keypad.getKey();

  if (key) {

    
    if (key == '*') {
      enteredPassword = "";
      showInputScreen();
    }

    
    else if (key == '#') {
      checkPassword();
    }

    
    else if (key >= '0' && key <= '9') {

      if (enteredPassword.length() < 8) {
        enteredPassword += key;

        lcd.setCursor(0, 1);
        lcd.print("                ");

        lcd.setCursor(0, 1);

        for (int i = 0; i < enteredPassword.length(); i++) {
          lcd.print('*');
        }
      }
    }
  }
}

void checkPassword() {
  lcd.clear();

  if (enteredPassword == password) {
    lcd.setCursor(0, 0);
    lcd.print("Access Granted");
    correctSound();

    lcd.setCursor(0, 1);
    lcd.print("Welcome!");

  } else {
    lcd.setCursor(0, 0);
    lcd.print("Wrong Password");
    wrongSound();

    lcd.setCursor(0, 1);
    lcd.print("Try Again!");
  }

  delay(2000);

  enteredPassword = "";
  showInputScreen();
}

void showInputScreen() {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");

  lcd.setCursor(0, 1);
  lcd.print("                ");
}
void correctSound() {
  tone(BUZZER, 1000);
  delay(150);
  tone(BUZZER, 1500);
  delay(200);
  noTone(BUZZER);
}

void wrongSound() {
  tone(BUZZER, 300);
  delay(400);
  noTone(BUZZER);
}