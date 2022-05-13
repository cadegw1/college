#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup()                                                                                     
{
  lcd.begin(16,2); // set up the LCD's number of columns and rows:
  lcd.print("Go Tigers!"); // Print a message to the LCD.
  lcd.setCursor(0,1);  //Display position
  lcd.print("Go LSU!");
  pinMode(6, OUTPUT); // backlight
  pinMode(9, OUTPUT); // pixel
}
void loop()
{
  analogWrite(6, 255);
  analogWrite(9, 0);
  for (int i = 0; i < 16; i++)
  {
    lcd.scrollDisplayRight();
    delay(300);
  }
  delay(1000);
  lcd.home();
  delay(1000);
  for (int i = 0; i < 16; i++)
  {
    lcd.scrollDisplayLeft();
    delay(300);  
  }
  delay(1000);
  lcd.home();
  delay(1000);
  for (int i = 255; i != 0; i--)
  {
    analogWrite(6, i);
    delay(30);  
  }
  delay(1000);
  analogWrite(6, 255);
  delay(1000);
  for (int i = 0; i != 150; i++)
  {
    analogWrite(9, i);
    delay(30);  
  }
  delay(1000);
}
