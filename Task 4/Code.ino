#define led1 8
#define led2 9
#define D1 10
#define D2 11
#define A1 0
#define A2 1

int var1 = 0;
int var2 = 0;

int key2[4] = {0, 1, 2, 3};
int key1[4] = {7, 6, 5, 4}; 

char chars[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

bool init_state = true;
bool get_code = false;
bool ex = false;

char my_code[512]; 
int curr_idx  = 0;
int pointer = 0;

void init_key1();
int is_pressed();
int get_key(int r);

void key1_func();
void key2_func();
void key3_func();
void key4_func();
void key5_func();
void key6_func();
void key7_func();
void key8_func();
void key9_func();
void keyA_func();
void keyB_func();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i < 4; i++)
  {
      pinMode(key1[i], OUTPUT);
      pinMode(key2[i], INPUT);
  }

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);

  init_key1();

}

void loop() {
  // put your main code here, to run repeatedly:
   
  if (init_state)
  {
      int p = is_pressed();
      if (p != -1) 
      {
        if (get_key(p) == 0)
        {
          Serial.println("Start coding");
          init_state = false;
          get_code = true;
          ex = false;
        }
      }
      delay(300);
   }

   if (get_code)
   {
      int p = is_pressed();
      if (p != -1) 
      {
        int k = get_key(p);

        Serial.println(k);
        switch(k){
          case 12:
            curr_idx--;
            break;
          case 13:
             curr_idx = 0;
             break;
          case 14:
            break;
          case 15:
            get_code = false;
            init_state = false;
            ex = true;
            Serial.println("End Coding");
            Serial.print("Code: ");
            for (int i = 0; i < curr_idx; i++) Serial.print(my_code[i]);
            Serial.println(" ");
            break;
           default:
           my_code[curr_idx++] = chars[k]; 
        }

      }
      delay(200);
   }

   if (ex)
   {
    char c = my_code[pointer];
    DO(c);
    
    pointer++;
    
    if (pointer >= curr_idx) 
    {
      pointer = 0;
    }
    else
    {
      Serial.print("next command is: ");
      Serial.println(my_code[pointer]);
    }
   }

  
}

void init_key1()
{
  for (int i = 0; i < 4; i++)
  {
     digitalWrite(key1[i], HIGH);
  }
}

int is_pressed()
{
  for (int i = 0; i < 4; i++)
  {
     if (digitalRead(key2[i]) == HIGH)
      return i;
  }

  return -1;
}

int get_key(int r)
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      if (j == i) digitalWrite(key1[j], HIGH);
      else  digitalWrite(key1[j], LOW);
    }

    if (digitalRead(r) == HIGH){
      init_key1();
      return (4 * r) + i;
    }
  }
  init_key1();
  return -1;
}

void DO(char c)
{
  switch(c)
    {
      case '1':
        key1_func();
        break;
      case '2':
        key2_func();
        break;
      case '3':
        key3_func();
        break;
      case '4':
        key4_func();
        break;
      case '5':
        key5_func();
        break;
      case '6':
        key6_func();
        break;
      case '7':
        key7_func();
        break;
      case '8':
        key8_func();
        break;
      case '9':
        key9_func();
        break;
      case 'A':
        keyA_func();
        break;
      case 'B':
        keyB_func();
        break;
        
    }
}

void key9_func()
{
    // HIGH
    if (my_code[pointer + 1] == '1')
    {
       if (my_code[pointer + 2] == '1') digitalWrite(led1, HIGH);
       else digitalWrite(led2, HIGH);
    }
    else
    {
      if (my_code[pointer + 2] == '1') digitalWrite(led1, LOW);
       else digitalWrite(led2, LOW);
    }

    pointer+=2;
}


void keyA_func()
{
    //var
    if(my_code[pointer + 1] == '1')
    {
        if (my_code[pointer + 2] == '1') var1 = digitalRead(D1);
        else var1 = digitalRead(D2);
    }
    else
    {
        if (my_code[pointer + 2] == '1') var2 = digitalRead(D1);
        else var2 = digitalRead(D2);
    }

    Serial.print(var1);
    Serial.print("  ");
    Serial.println(var2);
    pointer+=2;
}

void keyB_func()
{
    //var analogRead(A1);
    if(my_code[pointer + 1] == '1')
    {
        if (my_code[pointer + 2] == '1') var1 = analogRead(A1);
        else var1 = analogRead(A1);
    }
    else
    {
        if (my_code[pointer + 2] == '1') var2 = analogRead(A1);
        else var2  = analogRead(A1);
    }

    Serial.print(var1);
    Serial.print("  ");
    Serial.println(var2);
    pointer+=2;
}


void key1_func()
{
    if(my_code[pointer + 1] == '1') var1 += int(my_code[pointer + 2] - '0');
    else var2 += int(my_code[pointer + 2] - '0');

    Serial.print(var1);
    Serial.print("  ");
    Serial.println(var2);
    pointer+=2;
}

void key2_func()
{
    if(my_code[pointer + 1] == '1') var1 = int(my_code[pointer + 2] - '0');
    else var2 = int(my_code[pointer + 2] - '0');

    Serial.print(var1);
    Serial.print("  ");
    Serial.println(var2);
    pointer+=2;
}

void key3_func()
{
  if(my_code[pointer + 1] == '1')
  {
    if (my_code[pointer + 2] == '1') var1 += var1;
    else var1 += var2;
  }
  else
  {
    if (my_code[pointer + 2] == '1') var2 += var1;
    else var2 += var2;
  }

  Serial.print(var1);
  Serial.print("  ");
  Serial.println(var2);
  pointer+=2;
}

void key4_func()
{
  if(my_code[pointer + 1] == '1')
  {
    if (my_code[pointer + 2] == '1') var1 = var1;
    else var1 = var2;
  }
  else
  {
    if (my_code[pointer + 2] == '1') var2 = var1;
    else var2 = var2;
  }

  Serial.print(var1);
  Serial.print("  ");
  Serial.println(var2);
  pointer+=2;
}
void key5_func()
{
  Serial.println(int(my_code[pointer + 2] - '0'));
  if (my_code[pointer + 1] == '1') // var1 > value
  {
    if (var1 > int(my_code[pointer + 2] - '0')) pointer += 2;
    else pointer += 5;
   
  }
  else if (my_code[pointer + 1] == '2')
  {
    if (var1 < int(my_code[pointer + 2] - '0')) pointer += 2;
    else pointer += 5;
  }
  else
  {
    if (var1 == int(my_code[pointer + 2] - '0')) pointer += 2;
    else pointer += 5;
  }
}

void key6_func()
{
  Serial.println(int(my_code[pointer + 2] - '0'));
  if (my_code[pointer + 1] == '1') // var2 > value
  {
    if (var2 > int(my_code[pointer + 2] - '0')) pointer += 2;
    else pointer += 5;
   
  }
  else if (my_code[pointer + 1] == '2')
  {
    if (var2 < int(my_code[pointer + 2] - '0')) pointer += 2;
    else pointer += 5;
  }
  else
  {
    if (var2 == int(my_code[pointer + 2] - '0')) pointer += 2;
    else pointer += 5;
  }
}

void key7_func()
{
  if (my_code[pointer + 1] == '1') // operation
  {
    if (my_code[pointer + 2] == '1') // var1 > var2
    {
        if (var1 > var2) pointer += 2;
        else pointer += 5;
    } 
    else // var2 > var1
    {
        if (var2 > var1) pointer += 2;
        else pointer += 5; 
    }
   
  }
  else if (my_code[pointer + 1] == '2')
  {
    if (my_code[pointer + 2] == '1') // var1 < var2
    {
        if (var1 < var2) pointer += 2;
        else pointer += 5;
    } 
    else // var2 < var1
    {
        if (var2 < var1) pointer += 2;
        else pointer += 5; 
    }
  }
  else
  {
      if (var1 == var2) pointer += 2;
      else pointer += 5;
  }
}

void key8_func()
{
    int n = int(my_code[pointer + 2] - '0');
    pointer += 3;

    char c = my_code[pointer];
  
    for (int i = 0; i < n; i++) 
    {
      DO(c);
      pointer -= 2;
    }

    pointer += 2;
}
