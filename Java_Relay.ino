void setup() 
{
    Serial.begin(9600);
    pinMode(13, OUTPUT);

  while(!Serial);
}

void loop() 
{
  char input;
  
  input = Serial.read();
  
  if(input == '1')
  {
    digitalWrite(13, HIGH);
  }
  if(input == '2')
  {
     for(int i = 0; i < 10; i++)
     {
        digitalWrite(13, HIGH);
        delay(1000);
        digitalWrite(13, LOW);
        delay(100);
     }
  }
  if(input == '3')
  {
    digitalWrite(13, LOW);
  }
}


