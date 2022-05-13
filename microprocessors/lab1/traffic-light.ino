/*
 * Author: CADE WILLIAMS & ARMANDO CASTILLO
 * Date: 02/07/2022
 */
int BASE = 2;               
int NUM = 6;
bool red_light[2] = {true, false};  
void setup()
{
  for (int i = BASE; i < BASE + NUM; i ++)
  {
    pinMode(i, OUTPUT); 
  }
}
void loop()
{
  for (int i = BASE; i < BASE + 3; i ++)
  {
    digitalWrite(i, HIGH);
    delay(1000);
    if (i != 4)
    {
      digitalWrite(i, LOW);    
    } 
    else
    {
      digitalWrite(7, LOW);  
    }      
  }

  for (int i = BASE + 3; i < BASE + NUM; i ++)
  {
    digitalWrite(i, HIGH);
    delay(1000);
    if (i != 7)
    {
      digitalWrite(i, LOW);
    }
    else
    {
      digitalWrite(4, LOW);  
    }       
  }
}
