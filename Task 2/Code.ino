#define push 3
 
const int CW_interval = 3000;
const int CCW_interval = 1000;

// for leds
int leds[12];
short curr = 0;
bool dir = true;

// for synchronization
bool start = false;
bool skip = false;

// for delay
unsigned long interval = 3000; 
unsigned long previousMillis = 0; 

void writeLeds();
void changedir();


void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  for (short i = 0; i < 10; i++)
    leds[i] = 13 - i;

   for (short i = 10; i < 12; i++)
    leds[i] = 12 - i;

   for (short i = 0; i < 12; i++)
    pinMode(leds[i], OUTPUT);

   pinMode(push, INPUT);
   attachInterrupt(digitalPinToInterrupt(push), changedir, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
   unsigned long currentMillis = millis(); // grab current time
   if ((unsigned long)(currentMillis - previousMillis) >= interval && start) 
   {
    if (!skip) writeLeds();
    skip = false;  
   }
}

void writeLeds()
{
    for (short i = 0; i < 12; i++)
    {
      if (i == curr)
        digitalWrite(leds[i], HIGH);
       else
        digitalWrite(leds[i], LOW);
    }
  
    if (dir) curr++;
    else curr--;
      
    if (curr == 12) curr = 0;
    if (curr == -1) curr = 11;

    previousMillis = millis();
}

void changedir()
{
  dir = !dir;

  if (dir) interval = CCW_interval;
  else interval = CW_interval;
  curr = 0;
  start = true;
  writeLeds();
  skip = true;
}
