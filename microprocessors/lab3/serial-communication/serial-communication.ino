#include <LiquidCrystal.h>
#include <EEPROM.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
String input;
bool first = true;
int addr = 0;

void setup()                                                                                     
{
  pinMode(6, OUTPUT); // backlight
  pinMode(9, OUTPUT); // pixel
  
  lcd.begin(16,2); // set up the LCD's number of columns and rows:
  lcd.print("Gx: Cade & Armando"); // Print a message to the LCD.
  lcd.setCursor(0,1);  //Display position
  lcd.print("EE 4750 Section 3");

  analogWrite(6, 255);
  analogWrite(9, 0); 
  Serial.begin(9600);
}

void loop()
{
  // Prompts user to input text
  if(first)
  {
    Serial.println("Please write your favorite line:");
    delay(1000);  
    first = false;
  }

  lcd.scrollDisplayLeft(); 
  delay(300);

  // If text is entered
  if(Serial.available())
  {
    input = Serial.readStringUntil('\n');
    Serial.println("Thanks for your input. You have typed: ");
    Serial.println(input);
    Serial.println(input.length());

    // Save input to EEPROM
    byte len = input.length();
    EEPROM.write(addr, len);
    for(int i = 0; i < len; i++)
    {
      EEPROM.write(addr + (i + 1), input[i]);  
    }

    // Print contents of each memory address
    for(int i = 0; i < len; i++)
    {
      Serial.print(addr + 1 + i);
      Serial.print(" is the location for my input to store: ");
      Serial.print((char)EEPROM.read(addr + 1 + i));
      Serial.print("\n");  
    }

    // Display input on lcd in reverse
    char output[len + 1];
    for(int i = 0; i < len; i++)
    {
      output[i] = EEPROM.read(addr + len - i);
    }
    output[len] = '\0';

    // Clear original line and display new line
    lcd.setCursor(0, 0);
    lcd.print("                        ");
    lcd.setCursor(0, 0);
    lcd.print(String(output));
  }
}
