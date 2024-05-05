#include <Keypad.h>
#include <LiquidCrystal.h>

// Define LCD and Keypad configuration
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); // LCD initialization
const byte ROWS = 4; // Number of rows in the keypad
const byte COLS = 4; // Number of columns in the keypad

// Keypad configuration
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {0, 1, 2, 3}; // Pin numbers for keypad rows
byte colPins[COLS] = {4, 5, 6, 7}; // Pin numbers for keypad columns

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); // Initialize the keypad

// Function to get a multi-digit number from the keypad
int getNumber() {
  int number = 0;
  char key;
  
  while (true) {
    key = customKeypad.getKey(); // Wait for a key to be pressed
    if (key >= '0' && key <= '9') { // Check if it's a number
      number = number * 10 + (key); // Accumulate the digits
      lcd.print(key); // Display the digit on LCD
    } else if (key == '#') { // '#' used to confirm input
      break;
    }
  }
  return number;
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // Initialize the LCD display
}

void loop() {
  lcd.clear(); // Clear the LCD
  char operationKey = customKeypad.getKey(); // Get the operation key (A, B, C, D)
  
  if (operationKey) {
    switch (operationKey) {
      case 'A': // Addition
        lcd.print("Add: ");
        lcd.setCursor(0, 1); // Move to the second row
        int num1 = getNumber(); // Get the first number
        lcd.print(" + "); // Display the operation
        int num2 = getNumber(); // Get the second number
        int result = (num1 + num2)-96; // Calculate the result
        lcd.clear(); // Clear the display
        lcd.print("Result: "); 
        lcd.print(result); // Show the result
        Serial.print(result); // show in serial monitor
        break;

      case 'B': // Subtraction
        lcd.print("Subtract: ");
        lcd.setCursor(0, 1);
        int s_num1 = getNumber(); // First number for subtraction
        lcd.print(" - ");
        int s_num2 = getNumber(); // Second number for subtraction
        int s_result = (s_num1 - s_num2)-96;
        lcd.clear();
        lcd.print("Result: ");
        lcd.print(s_result);
        Serial.print(s_result);
        break;

      case 'C': // Multiplication
        lcd.print("Multiply: ");
        lcd.setCursor(0, 1);
        int m_num1 = getNumber(); // First number for multiplication
        lcd.print(" * "); 
        int m_num2 = getNumber(); // Second number for multiplication
        int m_result = m_num1 * m_num2;
        lcd.clear();
        lcd.print("Result: ");
        lcd.print(m_result);
        Serial.print(m_result);
        break;

      case 'D': // Division
        lcd.print("Divide: ");
        lcd.setCursor(0, 1);
        int d_num1 = getNumber(); // First number for division
        lcd.print(" / ");
        int d_num2 = getNumber(); // Second number for division
        if (d_num2 != 0) { // Check for division by zero
          int d_result = d_num1 / d_num2;
          lcd.clear();
          lcd.print("Result: ");
          lcd.print(d_result);
          Serial.print(d_result);
        } else {
          lcd.clear();
          lcd.print("Error: Divide by 0");
        }
        break;

      default: // Handle invalid input
        lcd.clear();
        lcd.print("Invalid Key!");
        break;
    }

    delay(3000); // Display the result for 3 seconds before clearing
    lcd.clear(); // Clear the display
  }
}
