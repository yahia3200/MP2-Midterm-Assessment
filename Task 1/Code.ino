#define led 8
#define tswitch 10

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(tswitch, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(tswitch) == HIGH)
    digitalWrite(led, LOW);
   else
    digitalWrite(led, HIGH);
}
