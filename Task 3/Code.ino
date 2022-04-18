#include <LiquidCrystal.h>

#define temp 0
#define smoke 3
const int rs = 5, en = 4, d4 = 6, d5 = 2, d6 = 1, d7 = 0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


int curr = 10;
unsigned long previousMillis = 0;
unsigned long previousMillis_t = 0;
 
int fan_interval = 500;
int hood_interval = 250;
int rest_interval = 3000;

int prev_temp = 0;
bool is_smoke = false;
bool is_smoke_t = false;

void hoodStep();
void fanstep();
void changeMode();


void setup()
{

  lcd.begin(16, 2);
  lcd.print("Temperature is: ");

  for (int i = 10; i <= 13; i++) pinMode(i, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(smoke), changeMode, CHANGE);
 }
 
void loop() {
  int curr_temp = analogRead(temp);
  curr_temp = map(curr_temp, 0, 1023, -55, 150);

  if (curr_temp != prev_temp)
  {
    lcd.setCursor(0, 1);
    lcd.print("    ");
    lcd.setCursor(0, 1);
    lcd.print(curr_temp);
  }
  prev_temp = curr_temp;
  
  
  unsigned long currentMillis = millis(); 
  if ((unsigned long)(currentMillis - previousMillis) >= hood_interval && is_smoke) hoodStep();

  currentMillis = millis();
  if ((unsigned long)(currentMillis - previousMillis) >= hood_interval && is_smoke_t) hoodStep(); 

  currentMillis = millis();
  if ((unsigned long)(currentMillis - previousMillis_t) >= rest_interval && is_smoke_t)
  {
    is_smoke_t = false;
    previousMillis = millis();
  }
    
  currentMillis = millis(); 
  if ((unsigned long)(currentMillis - previousMillis) >= fan_interval  && !is_smoke_t && curr_temp > 25 && !is_smoke)
    fanstep();

}


void hoodStep()
{
  curr--;
  if (curr == 9) curr = 13;
  
  for (int i = 10; i <= 13; i++)
  {
    if (i == curr) digitalWrite(i, LOW);
    else digitalWrite(i, HIGH);
  }

  previousMillis = millis();
  
}

void fanstep()
{
  curr++;
  if (curr == 14) curr = 10;
  for (int i = 10; i <= 13; i++)
  {
    if (i == curr) digitalWrite(i, LOW);
    else digitalWrite(i, HIGH);
  }
  previousMillis = millis();
}

void changeMode()
{
  if (digitalRead(smoke) == HIGH)
  {
    is_smoke = true;
    is_smoke_t = false;
    previousMillis = millis();
  }
  else
  {
    is_smoke = false;
    is_smoke_t = true;
    previousMillis_t = millis();
  }
}
